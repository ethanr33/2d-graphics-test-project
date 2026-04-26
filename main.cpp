
#include <iostream>
#include <chrono>

#include "Engine.h"
#include "transformations/TransformationManager.h"

int main() {

    int width = 1920;
    int height = 1080;

    Engine e{width, height};

    int frame_count = 0;

    std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();

    while (e.is_active()) {

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                e.draw(Primitive(PRIMITIVE_TYPE::POINT, Vertex(j, i)));
            }
        }

        e.tick();

        auto micros = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - begin).count();

        if (micros >= 1000000) {
            std::cout << "FPS: " << frame_count << std::endl;
            frame_count = 0;
            begin = std::chrono::high_resolution_clock::now();
        }

        frame_count++;


    }

    return 0;

}