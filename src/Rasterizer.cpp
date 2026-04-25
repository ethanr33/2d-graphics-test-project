
#include <cstdlib>
#include <omp.h>

#include "rasterizer/Rasterizer.h"
#include "utils/Visitor.h"
#include "FrameBuffer.h"

void Rasterizer::make_fragments(const std::vector<Command>& commands) {
    for (const Command& c : commands) {
        std::visit(overloaded {
            [this](const AddPrimitiveCommand& command) {
                PRIMITIVE_TYPE ptype = command.get_primitive().get_type();

                switch (ptype) {
                    case PRIMITIVE_TYPE::POINT:
                        this->fragments.push_back(Fragment(
                            command.get_primitive().get_vertices().at(0).pos.x,
                            command.get_primitive().get_vertices().at(0).pos.y,
                            Color(255, 0, 255)
                        ));
                        break;
                    default:
                        break;
                }
            },
            [](const ClearCommand& command) {
                // TODO
            }
        }, c);
    }
}

void Rasterizer::update_frame_buffer(FrameBuffer& buffer) {
    for (int i = 0; i < this->fragments.size(); i++) {
        Fragment fragment = this->fragments.at(i);
        buffer.update_pixel(fragment.x, fragment.y, fragment.color);
    }
}

void Rasterizer::reset() {
    this->fragments.clear();
}