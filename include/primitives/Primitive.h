
#pragma once

#include <vector>

#include "primitives/Vertex.h"

enum class PRIMITIVE_TYPE { POINT, LINE, TRIANGLE };

class Primitive {
    private:
        std::vector<Vertex> vertices;
        PRIMITIVE_TYPE type;
        
    public:
        Primitive(const std::vector<Vertex>& vertices, PRIMITIVE_TYPE type) : vertices(vertices), type(type) {}

        PRIMITIVE_TYPE get_type() const {
            return type;
        }
        const std::vector<Vertex>& get_vertices() const {
            return vertices;
        }

        void transform_vertices(const ViewportTransformation& transformation) {
            for (Vertex& v : this->vertices) {
                v.pos.x = transformation.transform_x(v.pos.x);
                v.pos.y = transformation.transform_y(v.pos.y);
            }
        }
};