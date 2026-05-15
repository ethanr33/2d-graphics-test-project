
#pragma once

#include <vector>

#include "FrameBuffer.h"
#include "command_processing/Command.h"
#include "rasterizer/Fragment.h"

class Rasterizer {
    private:
        std::vector<Fragment> fragments;

        void plot_line_low(int, int, int, int, Color);
        void plot_line_high(int, int, int, int, Color);

        /**
         * @brief Adds fragments needed to render a line
         * Uses Bresenham's line drawing algorithm: https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#All_cases
         */
        void make_line_fragments(const Primitive&);
    public:
        /**
         * @brief Turn a list of primitives into fragments, which which are then rendered onto the frame buffer.
         */
        void make_fragments(const std::vector<Command>&);

        /**
         * @brief Renders current fragments onto a frame buffer
         * 
         */
        void render_fragments(FrameBuffer&) const;

        /**
         * @brief Resets rasterizer state for next frame
         */
        void reset();
};