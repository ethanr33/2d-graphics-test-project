
#pragma once

#include <vector>

#include "primitives/Vertex.h"

enum class PRIMITIVE_TYPE { POINT, LINE, TRIANGLE };

class Primitive {
    private:
        std::vector<Vertex> vertices;
        PRIMITIVE_TYPE type;
    public:
        PRIMITIVE_TYPE get_type() const;
        const std::vector<Vertex>& get_vertices() const;
        virtual void transform_vertices() = 0;
};