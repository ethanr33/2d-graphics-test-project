
#include <cstdlib>
#include <vector>

#include "rasterizer/Rasterizer.h"
#include "utils/Visitor.h"
#include "FrameBuffer.h"
#include "primitives/Vertex.h"

void Rasterizer::make_and_render_fragments(const std::vector<Command>& commands, FrameBuffer& buffer) {
    for (const Command& c : commands) {
        PRIMITIVE_TYPE ptype = c.primitive.type;
        Vertex v1 = c.primitive.vertices[0];

        if (!buffer.is_in_bounds(v1.pos.x, v1.pos.y)) {
            continue;
        }

        switch (ptype) {
            case PRIMITIVE_TYPE::POINT:
                buffer.update_pixel(v1.pos.x, v1.pos.y, c.primitive.color);
                break;
            default:
                break;
        }
    }
}

void Rasterizer::reset() {
    this->fragments.clear();
}