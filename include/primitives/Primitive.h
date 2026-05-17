
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

        // The higher the z index, the higher priority the primitive has
        uint32_t z_index;

        // Point constructor
        Primitive(PRIMITIVE_TYPE type, const Vertex& v1) : type(type), color(0, 0, 0), z_index(0) {
            vertices[0] = v1;
        }

        // Line constructor
        Primitive(PRIMITIVE_TYPE type, const Vertex& start, const Vertex& end) : type(type), color(0, 0, 0), z_index(0) {
            vertices[0] = start;
            vertices[1] = end;
        }

        // Triangle constructor
        Primitive(PRIMITIVE_TYPE type, const Vertex& v1, const Vertex& v2, const Vertex& v3) : type(type), color(0, 0, 0), z_index(0) {
            vertices[0] = v1;
            vertices[1] = v2;
            vertices[2] = v3;
        }

        /**
         * @brief Applies translation transformation to all vertices of object
         */
        void apply_translation(double dx, double dy);
};

