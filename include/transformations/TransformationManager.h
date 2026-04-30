
#pragma once

#include <vector>

#include "command_processing/Command.h"
#include "transformations/ViewportTransformation.h"
#include "primitives/Primitive.h"

class TransformationManager {
    public:
        void add_translation(int dx, int dy);
        void apply_transformations(std::vector<Command>&) const;
};