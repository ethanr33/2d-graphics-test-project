
#pragma once

#include <vector>

#include "command_processing/Command.h"
#include "primitives/Primitive.h"
#include "utils/Matrix.h"

class TransformationManager {
    private:
        Matrix transformation_matrix;

        std::vector<Command> transformed_commands;
    public:
        TransformationManager() : transformation_matrix(3, 3, true) {}

        void add_translation(double, double);

        void apply_transformations(const std::vector<Command>&);

        const std::vector<Command> get_transformed_commands() const noexcept {
            return transformed_commands;
        }

        void clear_transformed_commands() {
            this->transformed_commands.clear();
        }

        /**
         * Resets transformations and clears transformed commands
         */
        void reset();
};