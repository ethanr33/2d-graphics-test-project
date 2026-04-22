
#include "transformations/TransformationManager.h"


// Visitor pattern without inheritance!
// See https://en.cppreference.com/cpp/utility/variant/visit2

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

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