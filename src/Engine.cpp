
#include "Engine.h"

void Engine::tick() {
    this->renderer.display();
}

bool Engine::is_active() const {
    return this->app_window.dispatch() != -1;
}