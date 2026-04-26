
#pragma once

#include <vector>

#include "primitives/Vertex.h"

enum class PRIMITIVE_TYPE { POINT, LINE, TRIANGLE };

class Primitive {
    private:
        Vertex v1;
        Vertex v2;
        Vertex v3;

        PRIMITIVE_TYPE type;        
    public:
        Primitive(PRIMITIVE_TYPE type, const Vertex& v1) : v1(v1), v2(v1), v3(v1), type(type) {}

        PRIMITIVE_TYPE get_type() const {
            return type;
        }
        const Vertex& get_vertices() const {
            return v1;
        }

        void transform_vertices(const ViewportTransformation& transformation) {
                v1.pos.x = transformation.transform_x(v1.pos.x);
                v1.pos.y = transformation.transform_y(v1.pos.y);
        }
};