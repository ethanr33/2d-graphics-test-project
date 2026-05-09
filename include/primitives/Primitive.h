
#pragma once

#include <vector>
#include <stdint.h>

#include "primitives/Vertex.h"
#include "utils/Color.h"

enum class PRIMITIVE_TYPE { POINT, LINE, TRIANGLE };

struct Primitive {
        Vertex vertices[3];

        Color color;

        PRIMITIVE_TYPE type;  

        Primitive(PRIMITIVE_TYPE type, const Vertex& v1) : type(type), color(0, 0, 0) {
            vertices[0] = v1;
        }
};

