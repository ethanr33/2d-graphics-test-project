
#include "transformations/TransformationManager.h"

void TransformationManager::add_translation(double dx, double dy) {
        Matrix translation_matrix(3, 3);
        translation_matrix.set_identity();
        translation_matrix.set_element(0, 2, dx);
        translation_matrix.set_element(1, 2, dy);

        transformation_matrix = translation_matrix * transformation_matrix;
}

void TransformationManager::apply_transformations(const std::vector<Command>& commands) {
    for (const Command& c : commands) {
        PRIMITIVE_TYPE type = c.primitive.type;

        Command new_command{c};
        

        new_command.primitive.vertices[0].pos.x = transformation_matrix.get_element(0, 0) * c.primitive.vertices[0].pos.x + transformation_matrix.get_element(0, 1) * c.primitive.vertices[0].pos.y + transformation_matrix.get_element(0, 2);
        new_command.primitive.vertices[0].pos.y = transformation_matrix.get_element(1, 0) * c.primitive.vertices[0].pos.x + transformation_matrix.get_element(1, 1) * c.primitive.vertices[0].pos.y + transformation_matrix.get_element(1, 2);  
    
        this->transformed_commands.push_back(new_command);
    }

    
}

void TransformationManager::reset() {
    this->transformed_commands.clear();
    this->transformation_matrix.set_identity();
}