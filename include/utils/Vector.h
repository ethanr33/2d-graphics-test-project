
#pragma once

#include "transformations/ViewportTransformation.h"

struct Vector {
    double x;
    double y;

    void apply_transformation(ViewportTransformation&);
};