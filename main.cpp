
#include <iostream>
#include <chrono>

#include "Engine.h"
#include "transformations/TransformationManager.h"

int main() {

    int width = 1920;
    int height = 1080;

    Engine e{width, height};

    Primitive p1 = Primitive(PRIMITIVE_TYPE::LINE, Vertex(0, 0), Vertex(1000, 700));
    p1.color = Color(255, 0, 0);

    e.draw(p1);

    while (e.is_active()) {
        e.tick();
    }

}