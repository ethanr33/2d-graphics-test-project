
#include "Renderer.h"


void Renderer::display() {
    front_buffer = back_buffer;

    if (this->state_updated) {
        transformation_manager.apply_transformations(command_stream.get_command_stream());
        rasterizer.make_and_render_fragments(command_stream.get_command_stream(), this->back_buffer);

        this->state_updated = false;
    }
}


void Renderer::clear() {
    rasterizer.reset();
    command_stream.reset();
    transformation_manager.reset();
    this->state_updated = true;
}

void Renderer::add_primitive(const Primitive& p) {
    command_stream.add_primitive(p);
    this->state_updated = true;
}

void Renderer::translate_absolute(double dx, double dy) {
    this->transformation_manager.add_translation(dx, dy);
    this->state_updated = true;
}

const FrameBuffer* Renderer::get_front_buffer() const {
    return &this->front_buffer;
}
