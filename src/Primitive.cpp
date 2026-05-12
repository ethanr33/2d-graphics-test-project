
#include "primitives/Primitive.h"

void Primitive::apply_translation(double dx, double dy) {
    for (int i = 0; i < 3; i++) {
        this->vertices[i].pos.x += dx;
        this->vertices[i].pos.y += dy;
    }
}