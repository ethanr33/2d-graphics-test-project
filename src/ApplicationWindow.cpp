
#include <time.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>

#include "window/ApplicationWindow.h"

std::string generate_shm_file_name() {
	struct timespec ts;

    std::string name;

	clock_gettime(CLOCK_REALTIME, &ts);
	long r = ts.tv_nsec;

	for (int i = 0; i < 6; ++i) {
		name = 'A'+(r&15)+(r&16)*2;
		r >>= 5;
	}

    return name;
}

int create_shm_file() {
	int retries = 100;
	do {
		char name[] = "/wl_shm-XXXXXX";
		generate_shm_file_name();
		--retries;
		int fd = shm_open(name, O_RDWR | O_CREAT | O_EXCL, 0600);
		if (fd >= 0) {
			shm_unlink(name);
			return fd;
		}
	} while (retries > 0 && errno == EEXIST);
	return -1;
}

int allocate_shm_file(size_t size) {
	int fd = create_shm_file();
	if (fd < 0)
		return -1;
	int ret;
	do {
		ret = ftruncate(fd, size);
	} while (ret < 0 && errno == EINTR);
	if (ret < 0) {
		close(fd);
		return -1;
	}
	return fd;
}

void registry_handle_global(void* data, struct wl_registry *registry, uint32_t name, const char *interface, uint32_t version) {
	printf("interface: '%s', version: %d, name: %d\n", interface, version, name);

    ApplicationWindow* app = (ApplicationWindow*) data;
    if (strcmp(interface, wl_compositor_interface.name) == 0) {
        app->compositor = (wl_compositor*) wl_registry_bind(registry, name, &wl_compositor_interface, 4);
    } else if (strcmp(interface, wl_shm_interface.name) == 0) {
        app->shm = (wl_shm*) wl_registry_bind(registry, name, &wl_shm_interface, 1);
    } else if (strcmp(interface,  xdg_wm_base_interface.name) == 0) {
        app->wm_base = (xdg_wm_base*) wl_registry_bind(registry, name, &xdg_wm_base_interface, 1);

        xdg_wm_base_add_listener(app->wm_base, &app->base_listener, app);
    } else if (strcmp(interface, wl_seat_interface.name) == 0) {
        app->seat = (wl_seat*) wl_registry_bind(registry, name, &wl_seat_interface, 7);
        wl_seat_add_listener(app->seat, &app->seat_listener, app);
    }
}

void registry_handle_global_remove(void* data, struct wl_registry *registry, uint32_t name) {
	
}

void xdg_wm_base_ping(void* data, xdg_wm_base* xdg_wm_base, uint32_t serial) {
    xdg_wm_base_pong(xdg_wm_base, serial);
}

void xdg_surface_configure(void* data, struct xdg_surface* xdg_surface, uint32_t serial) {
    xdg_surface_ack_configure(xdg_surface, serial);

    ApplicationWindow* app = (ApplicationWindow*) data;

    struct wl_buffer *buffer = app->draw_frame();
    wl_surface_attach(app->wl_surface, buffer, app->width, app->height);
    wl_surface_commit(app->wl_surface);
}

void wl_buffer_release(void* data, wl_buffer* buffer) {
    /* Sent by the compositor when it's no longer using this buffer */
    wl_buffer_destroy(buffer);
}

void wl_surface_frame_done(void* data, struct wl_callback* callback, uint32_t time) {
    wl_callback_destroy(callback);

    ApplicationWindow* app = (ApplicationWindow*) data;

    callback = wl_surface_frame(app->wl_surface);
    wl_callback_add_listener(callback, &app->callback_listener, app);

    struct wl_buffer* buffer = app->draw_frame();
    wl_surface_attach(app->wl_surface, buffer, 0, 0);
    wl_surface_damage_buffer(app->wl_surface, 0, 0, INT32_MAX, INT32_MAX);
    wl_surface_commit(app->wl_surface);
}

void wl_seat_capabilities(void* data, wl_seat* seat, uint32_t capabilities) {
    bool has_pointer = capabilities & WL_SEAT_CAPABILITY_POINTER;

    ApplicationWindow* app = (ApplicationWindow*) data;

    if (has_pointer && app->pointer == nullptr) {
        // If a pointer is available on the seat and the pointer has not been added yet
        app->pointer = wl_seat_get_pointer(seat);
        wl_pointer_add_listener(app->pointer, &app->pointer_listener, app);
    } else if (!has_pointer && app->pointer != nullptr) {
        // If a pointer available is no longer available
        wl_pointer_release(app->pointer);
        app->pointer = nullptr;
    }
}

void wl_seat_name(void* data, wl_seat* seat, const char* name) {
    // Deliberately left empty
}

void wl_pointer_enter(void* data, struct wl_pointer* pointer, uint32_t serial, struct wl_surface* surface, wl_fixed_t surface_x, wl_fixed_t surface_y) {
    ApplicationWindow* app = (ApplicationWindow*) data;

    app->mouse_state.x = wl_fixed_to_int(surface_x);
    app->mouse_state.y = wl_fixed_from_int(surface_y);
}

void wl_pointer_leave(void* data, struct wl_pointer* pointer, uint32_t serial, struct wl_surface *surface) {

}

void wl_pointer_motion(void* data, struct wl_pointer* pointer, uint32_t time, wl_fixed_t surface_x, wl_fixed_t surface_y) {
    ApplicationWindow* app = (ApplicationWindow*) data;

    app->mouse_state.x = wl_fixed_to_int(surface_x);
    app->mouse_state.y = wl_fixed_to_int(surface_y);
}

void wl_pointer_button(void* data, wl_pointer* pointer, uint32_t serial, uint32_t time, uint32_t button, uint32_t state) {
    ApplicationWindow* app = (ApplicationWindow*) data;

    if (state == WL_POINTER_BUTTON_STATE_PRESSED) {
        app->mouse_pressed_handler.invoke(app->mouse_state);
    }
}

void wl_pointer_frame(void* data, struct wl_pointer* pointer) {

}


wl_buffer* ApplicationWindow::draw_frame() {
    int stride = this->width * 4;
    int size = stride * this->height;

    int fd = allocate_shm_file(size);
    if (fd == -1) {
        return NULL;
    }

    uint32_t* data = (uint32_t*) mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
        close(fd);
        return NULL;
    }

    struct wl_shm_pool *pool = wl_shm_create_pool(shm, fd, size);
    struct wl_buffer *buffer = wl_shm_pool_create_buffer(pool, 0, width, height, stride, WL_SHM_FORMAT_XRGB8888);
    wl_shm_pool_destroy(pool);
    close(fd);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            data[this->width * y + x] = frame_buffer->get_frame_buffer().at(y).at(x).to_hex();
        }
    }

    munmap(data, size);
    wl_buffer_add_listener(buffer, &buffer_listener, NULL);
    return buffer;
}

SignalHandler<MouseState>* ApplicationWindow::get_mouse_pressed_handler() {
    return &this->mouse_pressed_handler;
}

ApplicationWindow::ApplicationWindow(int width, int height, const std::string& window_title, const FrameBuffer* fb) {
    this->width = width;
    this->height = height;
    this->window_title = window_title;

    this->display = nullptr;
    this->registry = nullptr;
    this->compositor = nullptr;

    this->frame_buffer = fb;

    this->registry_listener = {
        .global = registry_handle_global,
        .global_remove = registry_handle_global_remove
    };

    this->surface_listener = {
        .configure = xdg_surface_configure
    };

    this->base_listener = {
        .ping = xdg_wm_base_ping
    };

    this->buffer_listener = {
        .release = wl_buffer_release
    };

    this->callback_listener = {
        .done = wl_surface_frame_done
    };

    this->seat_listener = {
        .capabilities = wl_seat_capabilities,
        .name = wl_seat_name
    };

    this->pointer_listener = {
        .enter = wl_pointer_enter,
        .leave = wl_pointer_leave,
        .motion = wl_pointer_motion,
        .button = wl_pointer_button,
        .frame = wl_pointer_frame
    };

}

bool ApplicationWindow::init() {
    this->display = wl_display_connect(NULL);

    if (!this->display) {
        return false;
    }

    this->registry = wl_display_get_registry(this->display);
    wl_registry_add_listener(this->registry, &this->registry_listener, this);

    wl_display_roundtrip(this->display);

    this->wl_surface = wl_compositor_create_surface(this->compositor);
    this->xdg_surface = xdg_wm_base_get_xdg_surface(this->wm_base, this->wl_surface);

    // data parameter is not used since handler is a member function
    xdg_surface_add_listener(this->xdg_surface, &surface_listener, this);

    this->toplevel = xdg_surface_get_toplevel(this->xdg_surface);
    xdg_toplevel_set_title(this->toplevel, this->window_title.c_str());

    wl_surface_commit(this->wl_surface);

    struct wl_callback* cb = wl_surface_frame(this->wl_surface);
    wl_callback_add_listener(cb, &callback_listener, this);

    return true;
}

bool ApplicationWindow::dispatch() const {
    return wl_display_dispatch(this->display);
}

void ApplicationWindow::disconnect() {
    if (this->display) {
        wl_display_disconnect(this->display);
    }
}

void ApplicationWindow::attach_frame_buffer(FrameBuffer* fb) {
    this->frame_buffer = fb;
}

ApplicationWindow::~ApplicationWindow() {
    this->disconnect();
}