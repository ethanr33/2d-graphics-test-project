
#pragma once

#include <vector>

#include "command_processing/Command.h"
#include "primitives/Primitive.h"
#include "utils/Matrix.h"

class TransformationManager {
    private:
        Matrix transformation_matrix;
    public:
        TransformationManager() : transformation_matrix(3, 3) {
            this->transformation_matrix.set_identity();
        }

        void add_translation(double, double);

        void apply_transformations(std::vector<Command>&) const;

        /**
         * Resets transformation_matrix
         */
        void reset();
};