
#include "FrameBuffer.h"

const std::vector<std::vector<Color>>& FrameBuffer::get_frame_buffer() const {
    return this->frame_buffer;
}

void FrameBuffer::update_pixel(int x_pos, int y_pos, Color c) {
    this->frame_buffer.at(y_pos).at(x_pos) = c;
}