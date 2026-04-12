
#include <time.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>

#include "window/ApplicationWindow.h"

std::string ApplicationWindow::generate_shm_file_name() {
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

int ApplicationWindow::create_shm_file() {
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

int ApplicationWindow::allocate_shm_file(size_t size) {
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

void ApplicationWindow::registry_handle_global(void *data, struct wl_registry *registry, uint32_t name, const char *interface, uint32_t version) {
	printf("interface: '%s', version: %d, name: %d\n", interface, version, name);

    if (strcmp(interface, wl_compositor_interface.name) == 0) {
        compositor = (wl_compositor*) wl_registry_bind(registry, name, &wl_compositor_interface, 4);
    } else if (strcmp(interface, wl_shm_interface.name) == 0) {
        shm = (wl_shm*) wl_registry_bind(registry, name, &wl_shm_interface, 1);
    } else if (strcmp(interface,  xdg_wm_base_interface.name) == 0) {
        wm_base = (xdg_wm_base*) wl_registry_bind(registry, name, &xdg_wm_base_interface, 1);

        xdg_wm_base_add_listener(wm_base, &base_listener, data);
    }
}

void ApplicationWindow::registry_handle_global_remove(void *data, struct wl_registry *registry, uint32_t name) {
	
}

void ApplicationWindow::xdg_wm_base_ping(void* data, xdg_wm_base* xdg_wm_base, uint32_t serial) {
    xdg_wm_base_pong(xdg_wm_base, serial);
}

void ApplicationWindow::xdg_surface_configure(void* data, struct xdg_surface* xdg_surface, uint32_t serial) {
    xdg_surface_ack_configure(xdg_surface, serial);

    struct wl_buffer *buffer = draw_frame();
    wl_surface_attach(wl_surface, buffer, 0, 0);
    wl_surface_commit(wl_surface);
}

void ApplicationWindow::wl_buffer_release(void* data, wl_buffer* buffer) {
    /* Sent by the compositor when it's no longer using this buffer */
    wl_buffer_destroy(buffer);
}

wl_buffer* ApplicationWindow::draw_frame() {
    int stride = width * 4;
    int size = stride * height;

    int fd = allocate_shm_file(size);
    if (fd == -1) {
        return NULL;
    }

    uint32_t *data = (uint32_t*) mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
        close(fd);
        return NULL;
    }

    struct wl_shm_pool *pool = wl_shm_create_pool(shm, fd, size);
    struct wl_buffer *buffer = wl_shm_pool_create_buffer(pool, 0, width, height, stride, WL_SHM_FORMAT_XRGB8888);
    wl_shm_pool_destroy(pool);
    close(fd);

    /* Draw checkerboxed background */
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if ((x + y / 8 * 8) % 16 < 8)
                data[y * width + x] = 0xFF666666;
            else
                data[y * width + x] = 0xFFEEEEEE;
        }
    }

    munmap(data, size);
    wl_buffer_add_listener(buffer, &buffer_listener, NULL);
    return buffer;
}

ApplicationWindow::ApplicationWindow(int width, int height, const std::string& window_title) {
    this->width = width;
    this->height = height;
    this->window_title = window_title;

    this->display = nullptr;
    this->registry = nullptr;
    this->compositor = nullptr;
}

bool ApplicationWindow::init() {
    this->display = wl_display_connect(NULL);

    if (!this->display) {
        return false;
    }

    this->registry = wl_display_get_registry(this->display);
    wl_registry_add_listener(this->registry, &this->registry_listener, NULL);

    wl_display_roundtrip(this->display);

    this->wl_surface = wl_compositor_create_surface(this->compositor);
    this->xdg_surface = xdg_wm_base_get_xdg_surface(this->wm_base, this->wl_surface);

    // data parameter is not used since handler is a member function
    xdg_surface_add_listener(this->xdg_surface, &surface_listener, this);

    this->toplevel = xdg_surface_get_toplevel(this->xdg_surface);
    xdg_toplevel_set_title(this->toplevel, this->window_title.c_str());
    wl_surface_commit(this->wl_surface);

    while (wl_display_dispatch(this->display)) {
        /* This space deliberately left blank */
    }

    return true;
}

void ApplicationWindow::disconnect() {
    if (this->display) {
        wl_display_disconnect(this->display);
    }
}

ApplicationWindow::~ApplicationWindow() {
    this->disconnect();
}