
#pragma once

#include "utils/Vector.h"

struct Vertex {
    Vector pos;

    Vertex() : pos{0, 0} {};
    Vertex(double x, double y) : pos{x, y} {}
    Vertex(const Vertex& v) : pos(v.pos) {} 
};