
#pragma once

#include <vector>
#include <stdint.h>

#include "primitives/Vertex.h"

enum class PRIMITIVE_TYPE { POINT, LINE, TRIANGLE };

struct Primitive {
        Vertex vertices[3];

        PRIMITIVE_TYPE type;  

        Primitive(PRIMITIVE_TYPE type, const Vertex& v1) : type(type) {
            vertices[0] = v1;
        }
};

