
#pragma once

#include <variant>

#include "primitives/Primitive.h"
#include "utils/Color.h"

class AddPrimitiveCommand {
    private:
        Primitive primitive;
    public:
        AddPrimitiveCommand(const Primitive& p) : primitive(p) {}

        Primitive& get_primitive() {
            return primitive;
        }

        const Primitive& get_primitive() const {
            return primitive;
        }

        void apply_transformation(const ViewportTransformation&);
};

using Command = AddPrimitiveCommand;
