#include <wayland-client.h>
#include <string>

#include "../external/xdg-shell/xdg-shell-client-protocol.h"

class ApplicationWindow {
    private:
        inline static int width;
        inline static int height;

        inline static wl_display* display;
        inline static wl_registry* registry;
        inline static wl_compositor* compositor;
        inline static wl_shm* shm;
        inline static struct wl_surface* wl_surface;
        inline static struct xdg_surface* xdg_surface;
        inline static xdg_wm_base* wm_base;
        inline static xdg_toplevel* toplevel;

        inline static std::string window_title;

        static void registry_handle_global(void*, wl_registry*, uint32_t, const char*, uint32_t);
        static void registry_handle_global_remove(void*, wl_registry*, uint32_t);

        static std::string generate_shm_file_name();
        static int create_shm_file();
        static int allocate_shm_file(size_t);

        static void xdg_wm_base_ping(void*, xdg_wm_base*, uint32_t);
        static void xdg_surface_configure(void*, struct xdg_surface*, uint32_t);

        static void wl_buffer_release(void*, wl_buffer*);

        static wl_buffer* draw_frame();

        inline static wl_registry_listener registry_listener = {
            .global = registry_handle_global,
            .global_remove = registry_handle_global_remove
        };

        inline static xdg_surface_listener surface_listener = {
            .configure = xdg_surface_configure
        };

        inline static xdg_wm_base_listener base_listener = {
            .ping = xdg_wm_base_ping
        };

        inline static wl_buffer_listener buffer_listener = {
            .release = wl_buffer_release
        };

    public:
        ApplicationWindow(int, int, const std::string&);

        ApplicationWindow(const ApplicationWindow&) = delete;

        bool init();
        void disconnect();

        ~ApplicationWindow();
};