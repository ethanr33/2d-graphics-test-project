
#include "utils/Matrix.h"
#include "utils/Exceptions.h"
#include "doctest.h"

TEST_CASE("Check constructor") {
    SUBCASE("Construct from rows, cols") {
        SUBCASE("Valid construction") {
            Matrix m1(2, 7);

            CHECK(m1.get_rows() == 2);
            CHECK(m1.get_cols() == 7);
        }

        SUBCASE("Construction with rows or cols = 0") {
            CHECK_THROWS_AS(Matrix(0, 8), InvalidMatrixConstructionException);
            CHECK_THROWS_AS(Matrix(8, 0), InvalidMatrixConstructionException);
            CHECK_THROWS_AS(Matrix(0, 0), InvalidMatrixConstructionException);
        }

    }
}

TEST_CASE("Check setting identity matrix") {
    const int NUM_SIZES = 5;
    int sizes[NUM_SIZES] = {1, 2, 5, 10, 100};

    for (int i = 0; i < NUM_SIZES; i++) {
        Matrix m(sizes[i], sizes[i]);
        m.set_identity();
        for (int j = 0; j < sizes[i]; j++) {
            for (int k = 0; k < sizes[i]; k++) {
                if (j != k) {
                    CHECK(m.get_element(j, k) == 0);
                } else {
                    CHECK(m.get_element(j, k) == 1);
                }
            }
        }
    }

}

TEST_CASE("Check + operator") {

    SUBCASE("Adding 1x1 matrices") {
        Matrix m1(1, 1);
        m1.set_element(0, 0, 2);

        Matrix m2(1, 1);
        m2.set_element(0, 0, 3);

        Matrix m3 = m1 + m2;

        CHECK(m3.get_rows() == 1);
        CHECK(m3.get_cols() == 1);
        CHECK(m3.get_element(0, 0) == 5);
    }

    SUBCASE("Adding 3x3 matrices") {
        Matrix m1(3, 3);
        m1.set_element(0, 0, 2);
        m1.set_element(0, 1, 3);
        m1.set_element(0, 2, 4);
        m1.set_element(1, 0, 5);
        m1.set_element(1, 1, 6);
        m1.set_element(1, 2, 7);
        m1.set_element(2, 0, 8);
        m1.set_element(2, 1, 9);
        m1.set_element(2, 2, 10);

        Matrix m2(3, 3);
        m2.set_element(0, 0, 12);
        m2.set_element(0, 1, 7);
        m2.set_element(0, 2, 25);
        m2.set_element(1, 0, 3);
        m2.set_element(1, 1, 18);
        m2.set_element(1, 2, 42);
        m2.set_element(2, 0, 50);
        m2.set_element(2, 1, 1);
        m2.set_element(2, 2, 14);

        Matrix m3 = m1 + m2;

        CHECK(m3.get_rows() == 3);
        CHECK(m3.get_cols() == 3);

        CHECK(m3.get_element(0, 0) == 14);
        CHECK(m3.get_element(0, 1) == 10);
        CHECK(m3.get_element(0, 2) == 29);
        CHECK(m3.get_element(1, 0) == 8);
        CHECK(m3.get_element(1, 1) == 24);
        CHECK(m3.get_element(1, 2) == 49);
        CHECK(m3.get_element(2, 0) == 58);
        CHECK(m3.get_element(2, 1) == 10);
        CHECK(m3.get_element(2, 2) == 24);
    }

    SUBCASE("Adding matrices of different size") {
        Matrix m1(2, 3);
        Matrix m2(1, 4);

        CHECK_THROWS_AS(m1 + m2, MatrixSizeMismatchException);

        Matrix m3(3, 3);

        CHECK_THROWS_AS(m1 + m3, MatrixSizeMismatchException);
    }

    SUBCASE("Mul;tiplying matrices of different size") {
        Matrix m1(2, 3);
        Matrix m2(1, 4);

        CHECK_THROWS_AS(m1 * m2, MatrixSizeMismatchException);

        Matrix m3(2, 4);

        CHECK_THROWS_AS(m1 * m3, MatrixSizeMismatchException);
    }
}

TEST_CASE("Check += operator") {
    SUBCASE("Adding 1x1 matrices") {
        Matrix m1(1, 1);
        m1.set_element(0, 0, 2);

        Matrix m2(1, 1);
        m2.set_element(0, 0, 3);

        m1 += m2;

        CHECK(m1.get_rows() == 1);
        CHECK(m1.get_cols() == 1);
        CHECK(m1.get_element(0, 0) == 5);
    }

}

TEST_CASE("Check * operator") {
    
    SUBCASE("Multiplying 1x1 matrices") {
        Matrix m1(1, 1);
        m1.set_element(0, 0, 2);

        Matrix m2(1, 1);
        m2.set_element(0, 0, 3);

        Matrix m3 = m1 * m2;

        CHECK(m3.get_rows() == 1);
        CHECK(m3.get_cols() == 1);
        CHECK(m3.get_element(0, 0) == 6);
    }

    SUBCASE("Multiplying 2x2 matrices") {
        Matrix m1(2, 2);
        m1.set_element(0, 0, 2);
        m1.set_element(0, 1, 0);
        m1.set_element(1, 0, 4);
        m1.set_element(1, 1, 5);

        Matrix m2(2, 2);
        m2.set_element(0, 0, 3);
        m2.set_element(1, 1, -1);

        Matrix m3 = m1 * m2;

        CHECK(m3.get_rows() == 2);
        CHECK(m3.get_cols() == 2);
        CHECK(m3.get_element(0, 0) == 6);
        CHECK(m3.get_element(0, 1) == 0);
        CHECK(m3.get_element(1, 0) == 12);
        CHECK(m3.get_element(1, 1) == -5);
    }

    SUBCASE("Multiplying 2x2 and 2x1 matrices") {
        Matrix m1(2, 2);
        m1.set_element(0, 0, 2);
        m1.set_element(0, 1, 0);
        m1.set_element(1, 0, 4);
        m1.set_element(1, 1, 5);

        Matrix m2(2, 1);
        m2.set_element(0, 0, 3);
        m2.set_element(1, 0, -1);

        Matrix m3 = m1 * m2;

        CHECK(m3.get_rows() == 2);
        CHECK(m3.get_cols() == 1);
        CHECK(m3.get_element(0, 0) == 6);
        CHECK(m3.get_element(1, 0) == 7);
    }

}