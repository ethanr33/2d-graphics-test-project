
#pragma once

#include <vector>
#include <stdint.h>

#include "primitives/Vertex.h"

enum class PRIMITIVE_TYPE { POINT, LINE, TRIANGLE };

struct Primitive {
        Vertex v1; // In use for point, line, triangle
        Vertex v2; // In use for line, triangle
        Vertex v3; // In use for triangle

        PRIMITIVE_TYPE type;  

        Primitive(PRIMITIVE_TYPE type, const Vertex& v1) : v1(v1), v2(v1), v3(v1), type(type) {}

        void transform_vertices(const ViewportTransformation& transformation) {
                v1.pos.x = transformation.transform_x(v1.pos.x);
                v1.pos.y = transformation.transform_y(v1.pos.y);
        }
};

