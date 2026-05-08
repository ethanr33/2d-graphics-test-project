
#include "transformations/TransformationManager.h"

void TransformationManager::add_translation(double dx, double dy) {
        Matrix translation_matrix(3, 3);
        translation_matrix.set_identity();
        translation_matrix.set_element(0, 2, dx);
        translation_matrix.set_element(1, 2, dy);

        transformation_matrix = translation_matrix * transformation_matrix;
}

void TransformationManager::apply_transformations(std::vector<Command>& commands) const {
    for (Command& c : commands) {
        PRIMITIVE_TYPE type = c.primitive.type;

        c.primitive.vertices[0].pos.x = transformation_matrix.get_element(0, 0) * c.primitive.vertices[0].pos.x + transformation_matrix.get_element(0, 1) * c.primitive.vertices[0].pos.y + transformation_matrix.get_element(0, 2);
        c.primitive.vertices[0].pos.y = transformation_matrix.get_element(1, 0) * c.primitive.vertices[0].pos.x + transformation_matrix.get_element(1, 1) * c.primitive.vertices[0].pos.y + transformation_matrix.get_element(1, 2);  
    }

    
}

void TransformationManager::reset() {
    this->transformation_matrix.set_identity();
}