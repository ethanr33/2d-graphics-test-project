#include <wayland-client.h>
#include <string>

#include "../external/xdg-shell/xdg-shell-client-protocol.h"

class ApplicationWindow {
    private:
        int width;
        int height;

        wl_display* display;
        wl_registry* registry;
        wl_compositor* compositor;
        wl_shm* shm;
        struct wl_surface* wl_surface;
        struct xdg_surface* xdg_surface;
        xdg_wm_base* wm_base;
        xdg_toplevel* toplevel;

        std::string window_title;

        wl_registry_listener registry_listener;
        xdg_surface_listener surface_listener;
        xdg_wm_base_listener base_listener;
        wl_buffer_listener buffer_listener;

        friend void registry_handle_global(void*, wl_registry*, uint32_t, const char*, uint32_t);
        friend void registry_handle_global_remove(void*, wl_registry*, uint32_t);

        friend void xdg_wm_base_ping(void*, xdg_wm_base*, uint32_t);
        friend void xdg_surface_configure(void*, struct xdg_surface*, uint32_t);

        friend void wl_buffer_release(void*, wl_buffer*);

        wl_buffer* draw_frame();

    public:
        ApplicationWindow(int, int, const std::string&);

        ApplicationWindow(const ApplicationWindow&) = delete;

        bool init();

        void draw();
        bool dispatch();

        void disconnect();

        ~ApplicationWindow();
};