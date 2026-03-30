#include "../include/matrix.h"

#include <stdint.h>

#include "../include/assert_test.h"
#include "../include/other.h"

PRIVATE TEST void test_init_matrix(void)
{
    linear_matrix_t matrix;
    mo_status_t r = init_matrix(&matrix, 10, 10);

    ASSERT_IS_EQUAL(r, SUCCESS);

    ASSERT_IS_EQUAL(matrix.n_rows, 10);
    ASSERT_IS_EQUAL(matrix.n_cols, 10);
    ASSERT_IS_NOT_EQUAL(matrix.data, NULL);
    ASSERT_IS_EQUAL(matrix.is_init, TRUE);

    destroy_matrix(&matrix);
}

PRIVATE TEST void test_init_identity_matrix(void)
{
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

    destroy_matrix(&matrix);
}

PRIVATE TEST void test_init_matrix_with(void)
{
    linear_matrix_t matrix;
    mo_status_t r = init_matrix_with(&matrix, AS_FP(3), 5, 5);

    ASSERT_IS_EQUAL(r, SUCCESS);

    ASSERT_IS_EQUAL(matrix.n_rows, 5);
    ASSERT_IS_EQUAL(matrix.n_cols, 5);
    ASSERT_IS_NOT_EQUAL(matrix.data, NULL);
    ASSERT_IS_EQUAL(matrix.is_init, TRUE);

    for (uint32_t i = 0; i < matrix.n_rows * matrix.n_cols; ++i) {
        ASSERT_IS_EQUAL(matrix.data[i], AS_FP(3));
    }

    destroy_matrix(&matrix);
}

PRIVATE TEST void test_init_matrix_from_array(void)
{
    linear_matrix_t matrix;
    FP_TYPE arr[4] = {1, 2, 3, 4};
    mo_status_t r = init_matrix_from_array(&matrix, arr, 2, 2);

    ASSERT_IS_EQUAL(r, SUCCESS);

    ASSERT_IS_EQUAL(matrix.n_rows, 2);
    ASSERT_IS_EQUAL(matrix.n_cols, 2);
    ASSERT_IS_NOT_EQUAL(matrix.data, NULL);
    ASSERT_IS_EQUAL(matrix.is_init, TRUE);

    for (uint32_t i = 0; i < matrix.n_rows * matrix.n_cols; ++i) {
        ASSERT_IS_EQUAL(matrix.data[i], arr[i]);
    }

    destroy_matrix(&matrix);
}

int main(void)
{
    test_init_matrix();
    test_init_identity_matrix();
    test_init_matrix_with();
    test_init_matrix_from_array();

    return 0;
}
