
#include <iostream>
#include <chrono>

#include "Engine.h"
#include "transformations/TransformationManager.h"

int main() {

    int width = 1920;
    int height = 1080;

    Engine e{width, height};
    Primitive p1 = Primitive(PRIMITIVE_TYPE::TRIANGLE, Vertex(100, 100), Vertex(1000, 600), Vertex(200, 700));
    p1.color = Color(255, 0, 0);

    e.draw_line(Vertex(0, 0), Vertex(0, 1000), Color(0, 255, 0));

    while (e.is_active()) {
        e.tick();
    }

}