
#pragma once

#include "utils/Vector.h"

struct Vertex {
    Vector pos;

    Vertex(int x, int y) : pos{x, y} {}
};