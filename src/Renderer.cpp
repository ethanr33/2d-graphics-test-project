
#include "Renderer.h"


void Renderer::display() {
    // 1. Process primitives from command stream
    for (int i = 0; i < this->display_width; i++) {
            for (int j = 0; j < this->display_height; j++) {
                if ((i) % 30 < 10) {
                    front_buffer.update_pixel(j, i, Color(0, 255, 0));
                } else if ((i) % 30 < 20) {
                    front_buffer.update_pixel(j, i, Color(0, 0, 255));
                } else {
                    front_buffer.update_pixel(j, i, Color(255, 0, 0));
                }
            }
        }
}


void Renderer::clear() {

}

void Renderer::add(Vertex v1) {
    command_stream.add_primitive(v1);
}

