#pragma once

#include <wayland-client.h>
#include <string>
#include <vector>
#include <unordered_map>

#include "FrameBuffer.h"
#include "utils/SignalHandler.h"
#include "window/MouseEvent.h"

#include "../external/xdg-shell/xdg-shell-client-protocol.h"

enum class MOUSE_EVENT_TYPE {
    MOUSE_LEFT_CLICK,
    MOUSE_LEFT_RELEASE,
    MOUSE_RIGHT_CLICK,
    MOUSE_RIGHT_RELEASE,
    MOUSE_MIDDLE_CLICK,
    MOUSE_MIDDLE_RELEASE
};

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

        wl_seat* seat;
        wl_pointer* pointer = nullptr;

        std::string window_title;

        wl_registry_listener registry_listener;
        xdg_surface_listener surface_listener;
        xdg_wm_base_listener base_listener;
        wl_buffer_listener buffer_listener;
        wl_callback_listener callback_listener;
        wl_seat_listener seat_listener;
        wl_pointer_listener pointer_listener;

        const FrameBuffer* frame_buffer; // Not owned by this object

        MouseState mouse_state;

        std::unordered_map<MOUSE_EVENT_TYPE, SignalHandler<MouseState>> mouse_event_handlers;

        friend void registry_handle_global(void*, wl_registry*, uint32_t, const char*, uint32_t);
        friend void registry_handle_global_remove(void*, wl_registry*, uint32_t);

        friend void xdg_wm_base_ping(void*, xdg_wm_base*, uint32_t);
        friend void xdg_surface_configure(void*, struct xdg_surface*, uint32_t);

        friend void wl_buffer_release(void*, wl_buffer*);

        friend void wl_surface_frame_done(void*, struct wl_callback*, uint32_t);

        friend void wl_seat_capabilities(void*, struct wl_seat*, uint32_t);

        friend void wl_pointer_enter(void*, struct wl_pointer*, uint32_t, struct wl_surface*, wl_fixed_t, wl_fixed_t);
        friend void wl_pointer_leave(void*, struct wl_pointer*, uint32_t, struct wl_surface*);
        friend void wl_pointer_motion(void*, struct wl_pointer*, uint32_t, wl_fixed_t, wl_fixed_t);
        friend void wl_pointer_button(void*, struct wl_pointer*, uint32_t, uint32_t, uint32_t, uint32_t);
        friend void wl_pointer_frame(void*, struct wl_pointer*);

        wl_buffer* draw_frame();

    public:
        ApplicationWindow(int, int, const std::string&, const FrameBuffer*);

        ApplicationWindow(const ApplicationWindow&) = delete;

        bool init();
        bool dispatch() const;
        void disconnect();

        void attach_frame_buffer(FrameBuffer*);

        SignalHandler<MouseState>& get_mouse_event_handler(MOUSE_EVENT_TYPE);

        void add_mouse_event_handler(MOUSE_EVENT_TYPE, std::function<void(MouseState)>);

        ~ApplicationWindow();
};