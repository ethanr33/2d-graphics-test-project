
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

void Rasterizer::fill_bottom_flat_triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, Color color) {
    // Assumes v2.y == v3.y

    float invslope1 = (v2.pos.x - v1.pos.x) / (v2.pos.y - v1.pos.y);
    float invslope2 = (v3.pos.x - v1.pos.x) / (v3.pos.y - v1.pos.y);

    float curx1 = v1.pos.x;
    float curx2 = v1.pos.x;

    for (int scanlineY = v1.pos.y; scanlineY <= v2.pos.y; scanlineY++) {
        Primitive p(PRIMITIVE_TYPE::LINE, Vertex(curx1, scanlineY), Vertex(curx2, scanlineY));
        p.color = color;
        
        this->make_line_fragments(p);
        
        curx1 += invslope1;
        curx2 += invslope2;
    }
}

void Rasterizer::fill_top_flat_triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, Color color) {
    // Assumes v1.y == v2.y

    float invslope1 = (v3.pos.x - v1.pos.x) / (v3.pos.y - v1.pos.y);
    float invslope2 = (v3.pos.x - v2.pos.x) / (v3.pos.y - v2.pos.y);

    float curx1 = v3.pos.x;
    float curx2 = v3.pos.x;

    for (int scanlineY = v3.pos.y; scanlineY > v1.pos.y; scanlineY--) {
        Primitive p(PRIMITIVE_TYPE::LINE, Vertex(curx1, scanlineY), Vertex(curx2, scanlineY));
        p.color = color;
        this->make_line_fragments(p);
        curx1 -= invslope1;
        curx2 -= invslope2;
    }
}

void Rasterizer::make_triangle_fragments(const Primitive& triangle) {
    Vertex v1, v2, v3;

    // Make sure v1.y <= v2.y <= v3.y
    if (triangle.vertices[0].pos.y <= triangle.vertices[1].pos.y && triangle.vertices[0].pos.y <= triangle.vertices[2].pos.y) {
        v1 = triangle.vertices[0];

        if (triangle.vertices[1].pos.y <= triangle.vertices[2].pos.y) {
            v2 = triangle.vertices[1];
            v3 = triangle.vertices[2];
        } else {
            v2 = triangle.vertices[2];
            v3 = triangle.vertices[1];
        }
    } else if (triangle.vertices[1].pos.y <= triangle.vertices[0].pos.y && triangle.vertices[1].pos.y <= triangle.vertices[2].pos.y) {
        v1 = triangle.vertices[1];

        if (triangle.vertices[0].pos.y <= triangle.vertices[2].pos.y) {
            v2 = triangle.vertices[0];
            v3 = triangle.vertices[2];
        } else {
            v2 = triangle.vertices[2];
            v3 = triangle.vertices[0];
        }
    } else {
        v1 = triangle.vertices[2];

        if (triangle.vertices[0].pos.y <= triangle.vertices[1].pos.y) {
            v2 = triangle.vertices[0];
            v3 = triangle.vertices[1];
        } else {
            v2 = triangle.vertices[1];
            v3 = triangle.vertices[0];
        }
    }


    if (v2.pos.y == v3.pos.y) {
        this->fill_bottom_flat_triangle(v1, v2, v3, triangle.color);
    } else if (v1.pos.y == v2.pos.y) {
        this->fill_top_flat_triangle(v1, v2, v3, triangle.color);
    } else {
        Vertex v4 = Vertex((int)(v1.pos.x + ((float)(v2.pos.y - v1.pos.y) / (float)(v3.pos.y - v1.pos.y)) * (v3.pos.x - v1.pos.x)), v2.pos.y);
        this->fill_bottom_flat_triangle(v1, v2, v4, triangle.color);
        this->fill_top_flat_triangle(v2, v4, v3, triangle.color);
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
            case PRIMITIVE_TYPE::TRIANGLE:
                this->make_triangle_fragments(c.primitive);
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