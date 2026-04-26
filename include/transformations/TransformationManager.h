
#pragma once

#include <vector>

#include "command_processing/Command.h"
#include "transformations/ViewportTransformation.h"
#include "primitives/Primitive.h"

class TransformationManager {
    private:
        std::vector<ViewportTransformation> transformation_list;
    public:
        void add_translation(int dx, int dy);
        void apply_transformations(std::vector<Command>&) const;
};