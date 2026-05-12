
#include <iostream>
#include <chrono>

#include "Engine.h"
#include "transformations/TransformationManager.h"

int main() {

    int width = 1920;
    int height = 1080;

    Engine e{width, height, true};
    
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            Primitive p = Primitive(PRIMITIVE_TYPE::POINT, Vertex(i + 500, j + 500));
            p.color = Color(0, 0, 255);
            p.apply_translation(-5000, -5000);

            e.draw(p);
        }
    }

    while (e.is_active()) {
        e.tick();
    }

}