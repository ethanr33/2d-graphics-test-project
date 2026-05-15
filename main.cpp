
#include <iostream>
#include <chrono>

#include "Engine.h"
#include "transformations/TransformationManager.h"

int main() {

    int width = 1920;
    int height = 1080;

    Engine e{width, height, true};
    
    Primitive p = Primitive(PRIMITIVE_TYPE::LINE, Vertex(-100, -100), Vertex(200, 100));
    Primitive p2 = Primitive(PRIMITIVE_TYPE::LINE, Vertex(200, 100), Vertex(200, 600));
    Primitive p3 = Primitive(PRIMITIVE_TYPE::LINE, Vertex(200, 600), Vertex(-100, 800));


    p.color = Color(255, 0, 0);
    p2.color = Color(0, 255, 0);
    p3.color = Color(0, 0, 255);


    e.translate_viewport(-100, -100);

    e.draw(p);
    e.draw(p2);
    e.draw(p3);

    while (e.is_active()) {
        e.tick();
    }

}