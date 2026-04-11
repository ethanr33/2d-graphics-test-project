
#pragma once

#include <vector>

#include "primitives/Primitive.h"
#include "rasterizer/Fragment.h"

class Rasterizer {
    public:
        /**
         * @brief Turn a list of primitives into a list of fragments, which specify which pixels are colored what.
         */
        void make_fragments(const std::vector<Primitive>&, std::vector<Fragment>&);
};