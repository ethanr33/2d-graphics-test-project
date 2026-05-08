#pragma once

#include <vector>
#include <iostream>

struct Vector;

#include "utils/Vector.h"

class Matrix {
    private:
        int rows;
        int cols;

        std::vector<std::vector<double>> matrix;

        // Handle case where matrix is not square
    public:
        Matrix(int rows, int cols, bool identity=false) : rows(rows), cols(cols), matrix(rows, std::vector<double>(cols, 0)) {
            if (identity) {
                set_identity();
            }
        }

        Matrix(const Vector&, bool);

        inline int get_rows() const {
            return rows;
        }

        inline int get_cols() const {
            return cols;
        }

        /**
         * @brief Sets element at position (row, col) to val
         */
        inline void set_element(int row, int col, double val) {
            this->matrix.at(row).at(col) = val;
        }

        /**
         * @brief Gets element at (row, col) position
         */
        inline double get_element(int row, int col) const {
            return this->matrix.at(row).at(col);
        }

        /**
         * @brief Sets the matrix to the identity matrix
         */
        void set_identity();

        Matrix& operator+=(const Matrix&);

        const Matrix operator+(const Matrix&) const;

        const Matrix& operator*(const Matrix&) const;

        // Matrix * column vector = column vector
        // const Vector& operator*(const Vector&);

};
