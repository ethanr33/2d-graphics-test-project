
#include <iostream>
#include <chrono>

#include "Engine.h"
#include "transformations/TransformationManager.h"

int main() {

    int width = 500;
    int height = 500;

    Engine e{width, height};
    Primitive p1 = Primitive(PRIMITIVE_TYPE::TRIANGLE, Vertex(100, 100), Vertex(1000, 600), Vertex(200, 700));
    p1.color = Color(255, 0, 0);

    e.draw_line(Vertex(0, 0), Vertex(0, 1000), Color(0, 255, 0));

    e.add_mouse_event_handler(MOUSE_EVENT_TYPE::MOUSE_RIGHT_CLICK, [](MouseState state) {
        std::cout << state.x << " " << state.y << std::endl;
    });

    e.add_mouse_event_handler(MOUSE_EVENT_TYPE::MOUSE_RIGHT_RELEASE, [](MouseState state) {
        std::cout << "Released mouse" << std::endl;
    });

    while (e.is_active()) {
        e.tick();
    }

}