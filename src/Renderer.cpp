
#include "Renderer.h"


void Renderer::display() {

    front_buffer = back_buffer;

    transformation_manager.apply_transformations(command_stream.get_command_stream());
    rasterizer.make_and_render_fragments(command_stream.get_command_stream(), this->back_buffer);
}


void Renderer::clear() {
    rasterizer.reset();
    command_stream.reset();
}

void Renderer::add_primitive(const Primitive& p) {
    command_stream.add_primitive(p);
}

const FrameBuffer* Renderer::get_front_buffer() const {
    return &this->front_buffer;
}
