
#pragma once

#include "transformations/ViewportTransformation.h"

struct Vector {
    int x;
    int y;

    void apply_transformation(ViewportTransformation&);
};