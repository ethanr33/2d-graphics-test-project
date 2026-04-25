
#include <iostream>
#include <chrono>

#include "Engine.h"
#include "primitives/Point.h"

int main() {

    int width = 1000;
    int height = 1000;

    Engine e{width, height};

    e.add_event_handler(EVENT_TYPE::MOUSE_PRESSED_EVENT, [](MouseState state){
        std::cout << state.x << " " << state.y << std::endl;
    });

    int frame_count = 0;

    std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();

    while (e.is_active()) {

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                e.draw(Point(Vertex(j, i)));
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