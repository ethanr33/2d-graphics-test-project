
#include <iostream>

#include "Engine.h"

int main() {

    int width = 600;
    int height = 600;

    Engine e{width, height};

    e.add_event_handler(EVENT_TYPE::MOUSE_PRESSED_EVENT, [](MouseState state){
        std::cout << state.x << " " << state.y << std::endl;
    });

    while (e.is_active()) {
        e.tick();
    }

    return 0;

}