
#pragma once

#include <variant>

#include "primitives/Primitive.h"
#include "utils/Color.h"

struct AddPrimitiveCommand {
        Primitive primitive;
        AddPrimitiveCommand(const Primitive& p) : primitive(p) {}
};

using Command = AddPrimitiveCommand;
