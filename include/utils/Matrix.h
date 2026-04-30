#pragma once

#include <vector>

class Matrix {
    private:
        int rows;
        int cols;

        std::vector<double> matrix;

        // Handle case where matrix is not square
        /**
         * @brief Sets the matrix to the identity matrix
         */
        void set_identity();
    public:
        Matrix(int rows, int cols, bool identity=false) : rows(rows), cols(cols), matrix(rows * cols, 0) {
            if (identity) {
                set_identity();
            }
        }

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
            this->matrix.at(row * rows + col) = val;
        }

        /**
         * @brief Gets element at (row, col) position
         */
        inline double get_element(int row, int col) const {
            return this->matrix.at(rows * row + col);
        }

        Matrix& operator+=(const Matrix& rhs) {
            for (int i = 0; i < rhs.rows; i++) {
                for (int j = 0; j < rhs.cols; j++) {
                    this->set_element(i, j, rhs.get_element(i, j) + this->get_element(i, j));
                }
            }

            return *this;
        }

        const Matrix operator+(const Matrix& rhs) const {
            return Matrix(*this) += rhs;
        }

};
