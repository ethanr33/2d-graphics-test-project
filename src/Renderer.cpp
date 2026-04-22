
#include "Renderer.h"


void Renderer::display() {

    front_buffer = back_buffer;

    transformation_manager.apply_transformations(command_stream.get_command_stream());
    rasterizer.make_fragments(command_stream.get_command_stream());
    rasterizer.update_frame_buffer(back_buffer);



    // for (int i = 0; i < this->display_height; i += 2) {
    //         for (int j = 0; j < this->display_width; j += 2) {
    //             uint8_t r = rand() % 256;
    //             uint8_t g = rand() % 256;
    //             uint8_t b = rand() % 256;

    //             front_buffer.update_pixel(j, i, Color(r % 256, g % 256, b % 256));
    //             front_buffer.update_pixel(j + 1, i, Color(r % 256, g % 256, b % 256));
    //             front_buffer.update_pixel(j, i + 1, Color(r % 256, g % 256, b % 256));
    //             front_buffer.update_pixel(j + 1, i + 1, Color(r % 256, g % 256, b % 256));
    //         }
    //     }

}


void Renderer::clear() {
    command_stream.add_clear_command(Color(0, 0, 0));
}

void Renderer::add_primitive(Vertex v1) {
    command_stream.add_primitive(v1);
}

const FrameBuffer* Renderer::get_front_buffer() const {
    return &this->front_buffer;
}
