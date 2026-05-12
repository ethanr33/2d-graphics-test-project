#pragma once

#include <vector>

#include "utils/Color.h"

class FrameBuffer {
    private:
        int width;
        int height;

        std::vector<Color> frame_buffer;
    public:
        FrameBuffer(int width, int height): width(width), height(height), frame_buffer(height * width) {}
        FrameBuffer(const FrameBuffer& buffer) : width(buffer.width), height(buffer.height), frame_buffer(buffer.frame_buffer) {}

        inline void update_pixel(int x_pos, int y_pos, Color c) {
            this->frame_buffer.at(width * y_pos + x_pos) = c;
        }

        inline const std::vector<Color>& get_frame_buffer() const {
            return this->frame_buffer;
        }

        bool is_in_bounds(int x, int y) const noexcept {
            return x >= 0 && x < width && y >= 0 && y < height;
        }

        void reset_buffer(const Color& fill_color) {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    this->update_pixel(j, i, fill_color);
                }
            }
        }
};