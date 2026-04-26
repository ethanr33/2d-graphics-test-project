
#pragma once

#include "utils/Vector.h"

struct Vertex {
    Vector pos;

    Vertex(double x, double y) : pos{x, y} {}
    Vertex(const Vertex& v) : pos(v.pos) {} 
};