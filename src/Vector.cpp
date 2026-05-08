
#include "utils/Vector.h"
#include "utils/Exceptions.h"

Vector::Vector(const Matrix& m) {
    if (m.get_cols() != 1) {
        // Cannot convert a matrix to a column vector when cols != 1
        throw MatrixToVectorConversionException(m);
    }

    this->x = m.get_element(0, 0);
    this->y = m.get_element(1, 0);
}