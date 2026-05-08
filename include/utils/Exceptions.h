
#include <stdexcept>

#include "utils/Matrix.h"

class MatrixSizeMismatchException : public std::logic_error {
    public:
        MatrixSizeMismatchException(const Matrix& a, const Matrix& b) : std::logic_error(
            "Operation cannot be performed for matrices of size " + std::to_string(a.get_rows()) + "x" + std::to_string(a.get_cols()) + " and size " + std::to_string(b.get_rows()) + "x" + std::to_string(b.get_cols())
        ) {}
};

class MatrixToVectorConversionException : public std::logic_error {
    public:
        MatrixToVectorConversionException(const Matrix& m) : std::logic_error(
            "Cannot convert " + std::to_string(m.get_rows()) + "x" + std::to_string(m.get_cols()) + " matrix to column vector"
        ) {}
};