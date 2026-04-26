
#include "Engine.h"

void Engine::tick() {
    this->renderer.display();
}

void Engine::draw(const Primitive& p) {
    renderer.add_primitive(p);
}

bool Engine::is_active() const {
    return this->app_window.dispatch() != -1;
}

void Engine::add_event_handler(EVENT_TYPE type, std::function<void(MouseState)> handler) {
    this->app_window.get_mouse_pressed_handler()->connect(handler);
}