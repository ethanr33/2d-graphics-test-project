
#include "transformations/TransformationManager.h"
#include "utils/Visitor.h"

void TransformationManager::apply_transformations(std::vector<Command>& commands) const {
    for (Command& c : commands) {
        for (const ViewportTransformation& transformation : transformation_list) {
            std::visit(overloaded {
                [](const AddPrimitiveCommand& command) {
                    
                },
                [](const ClearCommand& command) {

                }
            }, c);
        }
    }
}