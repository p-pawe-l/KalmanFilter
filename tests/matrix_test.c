#include "../include/matrix.h"
#include "../include/other.h"
#include "../include/assert_test.h"

PUBLIC TEST void test_init_matrix(void) {
        linear_matrix_t matrix;
        mo_status_t r = init_matrix(&matrix, 10, 10);
        
        ASSERT_IS_EQUAL(r, SUCCESS);

        ASSERT_IS_EQUAL(matrix.n_rows, 10);
        ASSERT_IS_EQUAL(matrix.n_cols, 10);
        ASSERT_IS_NOT_EQUAL(matrix.data, NULL);
        ASSERT_IS_EQUAL(matrix.is_init, TRUE);
}

PUBLIC TEST void test_init_identity_matrix(void) {
        linear_matrix_t matrix;
        mo_status_t r = init_identity_matrix(&matrix, 5);

        ASSERT_IS_EQUAL(r, SUCCESS);
        
        ASSERT_IS_EQUAL(matrix.n_rows, 5);
        ASSERT_IS_EQUAL(matrix.n_cols, 5);
        ASSERT_IS_NOT_EQUAL(matrix.data, NULL);
        ASSERT_IS_EQUAL(matrix.is_init, TRUE);

        for (uint32_t i = 0; i < matrix.n_rows; ++i) {
                ASSERT_IS_EQUAL(matrix.data[i * (matrix.n_rows + 1)], AS_FP(1));
        }
}

PUBLIC TEST void test_init_matrix_with(void) {
        
}







