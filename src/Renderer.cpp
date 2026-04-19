
#include "Renderer.h"


void Renderer::display() {
    // 1. Process primitives from command stream
    for (int i = 0; i < this->display_height; i += 2) {
            for (int j = 0; j < this->display_width; j += 2) {
                uint8_t r = rand() % 256;
                uint8_t g = rand() % 256;
                uint8_t b = rand() % 256;

                front_buffer.update_pixel(j, i, Color(r % 256, g % 256, b % 256));
                front_buffer.update_pixel(j + 1, i, Color(r % 256, g % 256, b % 256));
                front_buffer.update_pixel(j, i + 1, Color(r % 256, g % 256, b % 256));
                front_buffer.update_pixel(j + 1, i + 1, Color(r % 256, g % 256, b % 256));
            }
        }

}


void Renderer::clear() {

}

void Renderer::add(Vertex v1) {
    
}

const FrameBuffer* Renderer::get_front_buffer() const {
    return &this->front_buffer;
}
