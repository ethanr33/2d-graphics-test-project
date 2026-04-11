
#include <vector>

#include "transformations/ViewportTransformation.h"
#include "primitives/Vertex.h"

class TransformationManager {
    private:
        std::vector<ViewportTransformation> transformation_list;
    public:
        void add_translation(int dx, int dy);
        void apply_transformations(std::vector<Vertex>&) const;
};