
#include <iostream>
#include <chrono>

#include "Engine.h"
#include "transformations/TransformationManager.h"

int main() {

    int width = 1920;
    int height = 1080;

    Engine e{width, height};

    e.add_mouse_event_handler(MOUSE_EVENT_TYPE::MOUSE_LEFT_CLICK, [&e, width, height](MouseState state) {
        e.draw_triangle(Vertex(rand() % width, rand() % height), Vertex(rand() % width, rand() % height), Vertex(rand() % width, rand() % height), Color(rand() % 256, rand() % 256, rand() % 256));
    });


    while (e.is_active()) {
        e.tick();
    }

}