
#include <iostream>

#include "Engine.h"
#include "primitives/Point.h"

int main() {

    int width = 100;
    int height = 100;

    Engine e{width, height};

    e.add_event_handler(EVENT_TYPE::MOUSE_PRESSED_EVENT, [](MouseState state){
        std::cout << state.x << " " << state.y << std::endl;
    });

    while (e.is_active()) {

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                e.draw(Point(Vertex(j, i)));
            }
        }

        e.tick();
    }

    return 0;

}