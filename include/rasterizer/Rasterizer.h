
#pragma once

#include <vector>

#include "FrameBuffer.h"
#include "command_processing/Command.h"
#include "rasterizer/Fragment.h"

class Rasterizer {
    private:
        std::vector<Fragment> fragments;
    public:
        /**
         * @brief Turn a list of primitives into a list of fragments, which specify which pixels are colored what.
         */
        void make_fragments(const std::vector<Command>&);

        /**
         * @brief Updates a frame buffer with rasterized fragments
         * Only modifies pixels specified in the fragments vector, other pixels will remain untouched
         */
        void update_frame_buffer(FrameBuffer& buffer);
};