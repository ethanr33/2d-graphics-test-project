
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

        void transform_vertices(const ViewportTransformation& transformation) {
                vertices[0].pos.x = transformation.transform_x(vertices[0].pos.x);
                vertices[0].pos.y = transformation.transform_y(vertices[0].pos.y);
        }
};

