
#pragma once

#include <variant>

#include "primitives/Primitive.h"
#include "utils/Color.h"

class AddPrimitiveCommand {
    private:
        Primitive primitive;
    public:
        AddPrimitiveCommand(PRIMITIVE_TYPE type, Vertex v1) : primitive(type, v1) {}

        Primitive& get_primitive() {
            return primitive;
        }

        const Primitive& get_primitive() const {
            return primitive;
        }

        void apply_transformation(const ViewportTransformation&);
};

class ClearCommand {
    private:
        Color clear_color;
    public:
        ClearCommand(Color color) : clear_color(color) {}
};

using Command = std::variant<AddPrimitiveCommand, ClearCommand>;
