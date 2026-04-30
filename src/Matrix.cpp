
#include "utils/Matrix.h"

void Matrix::set_identity() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == j) {
                this->set_element(i, j, 1);
            } else {
                this->set_element(i, j, 0);
            }
        }
    }
}