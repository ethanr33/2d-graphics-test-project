
#pragma once

#include <vector>

#include "FrameBuffer.h"
#include "command_processing/Command.h"
#include "rasterizer/Fragment.h"

class Rasterizer {
    private:
        std::vector<Fragment> fragments;

        // Helper functions for standard triangle rasterization algorithm
        void fill_bottom_flat_triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, Color);
        void fill_top_flat_triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, Color);

        /**
         * @brief Adds fragments needed to rasterize a triangle
         * Uses standard triangle rasterization algorithm: https://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html#algo1
         */
        void make_triangle_fragments(const Primitive&);

        // Bresenham's line drawing algorithm helper functions
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