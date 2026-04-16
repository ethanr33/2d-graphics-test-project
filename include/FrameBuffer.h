
#include <vector>

#include "utils/Color.h"

class FrameBuffer {
    private:
        int width;
        int height;

        std::vector<std::vector<Color>> frame_buffer;
    public:
        FrameBuffer(int width, int height): width(width), height(height), frame_buffer(height, std::vector<Color>(width)) {}

        void update_pixel(int, int, Color);

        const std::vector<std::vector<Color>>& get_frame_buffer() const;
};