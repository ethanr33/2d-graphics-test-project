
#include "Renderer.h"


void Renderer::display() {

    front_buffer = back_buffer;

    transformation_manager.apply_transformations(command_stream.get_command_stream());
    rasterizer.make_fragments(command_stream.get_command_stream());
    rasterizer.update_frame_buffer(back_buffer);

    rasterizer.reset();
    command_stream.reset();
}


void Renderer::clear() {
    command_stream.add_clear_command(Color(0, 0, 0));
}

void Renderer::add_primitive(Primitive p) {
    command_stream.add_primitive(p);
}

const FrameBuffer* Renderer::get_front_buffer() const {
    return &this->front_buffer;
}
