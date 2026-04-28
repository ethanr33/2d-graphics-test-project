
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
         * @brief Turn a list of primitives into fragments, which which are then rendered onto the frame buffer.
         */
        void make_and_render_fragments(const std::vector<Command>&, FrameBuffer& buffer);

        /**
         * @brief Resets rasterizer state for next frame
         */
        void reset();
};