
#include <cstdlib>
#include <vector>

#include "rasterizer/Rasterizer.h"
#include "utils/Visitor.h"
#include "FrameBuffer.h"
#include "primitives/Vertex.h"

void Rasterizer::plot_line_low(int x0, int y0, int x1, int y1, Color color) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;

    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }
    
    int D = 2 * dy - dx;
    int y = y0;

    for (int x = x0; x <= x1; x++) {
        fragments.push_back(Fragment(x, y, color));

        if (D > 0) {
            y += yi;
            D = D + (2 * (dy - dx));
        } else {
            D = D + 2 * dy;
        }
    }
}

void Rasterizer::plot_line_high(int x0, int y0, int x1, int y1, Color color) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int xi = 1;

    if (dx < 0) {
        xi = -1;
        dx = -dx;
    }
    
    int D = 2 * dx - dy;
    int x = x0;

    for (int y = y0; y <= y1; y++) {
        fragments.push_back(Fragment(x, y, color));

        if (D > 0) {
            x += xi;
            D = D + (2 * (dx - dy));
        } else {
            D = D + 2 * dx;
        }
    }
}

void Rasterizer::make_line_fragments(const Primitive& line) {
    int x0 = line.vertices[0].pos.x;
    int y0 = line.vertices[0].pos.y;
    int x1 = line.vertices[1].pos.x;
    int y1 = line.vertices[1].pos.y;

    if (std::abs(y1 - y0) < std::abs(x1 - x0)) {
        if (x0 > x1) {
            this->plot_line_low(x1, y1, x0, y0, line.color);
        } else {
            this->plot_line_low(x0, y0, x1, y1, line.color);
        }
    } else {
        if (y0 > y1) {
            this->plot_line_high(x1, y1, x0, y0, line.color);
        } else {
            this->plot_line_high(x0, y0, x1, y1, line.color);
        }
    }
}

void Rasterizer::make_fragments(const std::vector<Command>& commands) {
    for (const Command& c : commands) {
        PRIMITIVE_TYPE ptype = c.primitive.type;
        Vertex v1 = c.primitive.vertices[0];

        switch (ptype) {
            case PRIMITIVE_TYPE::POINT:
                fragments.push_back(Fragment(v1.pos.x, v1.pos.y, c.primitive.color));
                break;
            case PRIMITIVE_TYPE::LINE:
                this->make_line_fragments(c.primitive);
                break;
            default:
                break;
        }
    }
}

void Rasterizer::render_fragments(FrameBuffer& buffer) const {
    for (const Fragment& f : this->fragments) {
        if (buffer.is_in_bounds(f.x, f.y)) {
            buffer.update_pixel(f.x, f.y, f.color);
        }
    }
}

void Rasterizer::reset() {
    this->fragments.clear();
}