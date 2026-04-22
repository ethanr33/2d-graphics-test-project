
#include "primitives/Primitive.h"

class Point : public Primitive {
    public:
        Point(Vertex v1) : Primitive({v1}, PRIMITIVE_TYPE::POINT) {}
};