#include "../include/matrix.h"

#include <stdint.h>

#include "../include/assert_test.h"
#include "../include/other.h"

PRIVATE TEST void test_init_matrix(void)
{
    linear_matrix_t matrix;
    status_t r = init_matrix(&matrix, 10, 10);

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
    status_t r = init_identity_matrix(&matrix, 5);

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
    status_t r = init_matrix_with(&matrix, AS_FP(3), 5, 5);

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
    status_t r = init_matrix_from_array(&matrix, arr, 2, 2);

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

PRIVATE TEST void test_matrix_copy(void)
{
    FP_TYPE arr[4] = {AS_FP(1), AS_FP(2), AS_FP(3), AS_FP(4)};
    linear_matrix_t src, dest;
    init_matrix_from_array(&src, arr, 2, 2);
    status_t r = matrix_copy(&dest, &src);

    ASSERT_IS_EQUAL(r, SUCCESS);
    ASSERT_IS_EQUAL(dest.n_rows, src.n_rows);
    ASSERT_IS_EQUAL(dest.n_cols, src.n_cols);

    for (uint32_t i = 0; i < src.n_rows * src.n_cols; ++i)
        ASSERT_IS_EQUAL(dest.data[i], src.data[i]);

    destroy_matrix(&src);
    destroy_matrix(&dest);
}

PRIVATE TEST void test_matrix_negate(void)
{
    FP_TYPE arr[4] = {AS_FP(1), AS_FP(2), AS_FP(3), AS_FP(4)};
    linear_matrix_t m;
    init_matrix_from_array(&m, arr, 2, 2);
    status_t r = matrix_negate(&m);

    ASSERT_IS_EQUAL(r, SUCCESS);
    ASSERT_IS_EQUAL(m.data[0], -AS_FP(1));
    ASSERT_IS_EQUAL(m.data[1], -AS_FP(2));
    ASSERT_IS_EQUAL(m.data[2], -AS_FP(3));
    ASSERT_IS_EQUAL(m.data[3], -AS_FP(4));

    destroy_matrix(&m);
}

PRIVATE TEST void test_matrix_scale(void)
{
    FP_TYPE arr[4] = {AS_FP(1), AS_FP(2), AS_FP(3), AS_FP(4)};
    linear_matrix_t m;
    init_matrix_from_array(&m, arr, 2, 2);
    status_t r = matrix_scale(&m, AS_FP(2));

    ASSERT_IS_EQUAL(r, SUCCESS);
    ASSERT_IS_EQUAL(m.data[0], AS_FP(2));
    ASSERT_IS_EQUAL(m.data[1], AS_FP(4));
    ASSERT_IS_EQUAL(m.data[2], AS_FP(6));
    ASSERT_IS_EQUAL(m.data[3], AS_FP(8));

    destroy_matrix(&m);
}

PRIVATE TEST void test_matrix_add(void)
{
    /* |1 2| + |5 6| = |6  8 | */
    /* |3 4|   |7 8|   |10 12| */
    FP_TYPE arr1[4] = {AS_FP(1), AS_FP(2), AS_FP(3), AS_FP(4)};
    FP_TYPE arr2[4] = {AS_FP(5), AS_FP(6), AS_FP(7), AS_FP(8)};
    linear_matrix_t m1, m2;
    init_matrix_from_array(&m1, arr1, 2, 2);
    init_matrix_from_array(&m2, arr2, 2, 2);
    status_t r = matrix_add(&m1, &m2);

    ASSERT_IS_EQUAL(r, SUCCESS);
    ASSERT_IS_EQUAL(m1.data[0], AS_FP(6));
    ASSERT_IS_EQUAL(m1.data[1], AS_FP(8));
    ASSERT_IS_EQUAL(m1.data[2], AS_FP(10));
    ASSERT_IS_EQUAL(m1.data[3], AS_FP(12));

    destroy_matrix(&m1);
    destroy_matrix(&m2);
}

PRIVATE TEST void test_matrix_transpose(void)
{
    /* |1 2 3|T = |1 4| */
    /* |4 5 6|    |2 5| */
    /*            |3 6| */
    FP_TYPE arr[6] = {AS_FP(1), AS_FP(2), AS_FP(3), AS_FP(4), AS_FP(5), AS_FP(6)};
    linear_matrix_t m;
    init_matrix_from_array(&m, arr, 2, 3);
    status_t r = matrix_transpose(&m);

    ASSERT_IS_EQUAL(r, SUCCESS);
    ASSERT_IS_EQUAL(m.n_rows, 3);
    ASSERT_IS_EQUAL(m.n_cols, 2);
    ASSERT_IS_EQUAL(m.data[0], AS_FP(1));
    ASSERT_IS_EQUAL(m.data[1], AS_FP(4));
    ASSERT_IS_EQUAL(m.data[2], AS_FP(2));
    ASSERT_IS_EQUAL(m.data[3], AS_FP(5));
    ASSERT_IS_EQUAL(m.data[4], AS_FP(3));
    ASSERT_IS_EQUAL(m.data[5], AS_FP(6));

    destroy_matrix(&m);
}

PRIVATE TEST void test_matrix_dot_product(void)
{
    /* |1 2| x |5 6| = |19 22| */
    /* |3 4|   |7 8|   |43 50| */
    FP_TYPE arr1[4] = {AS_FP(1), AS_FP(2), AS_FP(3), AS_FP(4)};
    FP_TYPE arr2[4] = {AS_FP(5), AS_FP(6), AS_FP(7), AS_FP(8)};
    linear_matrix_t m1, m2, result;
    init_matrix_from_array(&m1, arr1, 2, 2);
    init_matrix_from_array(&m2, arr2, 2, 2);
    init_matrix(&result, 2, 2);
    status_t r = matrix_dot_product(&m1, &m2, &result);

    ASSERT_IS_EQUAL(r, SUCCESS);
    ASSERT_IS_EQUAL(result.data[0], AS_FP(19));
    ASSERT_IS_EQUAL(result.data[1], AS_FP(22));
    ASSERT_IS_EQUAL(result.data[2], AS_FP(43));
    ASSERT_IS_EQUAL(result.data[3], AS_FP(50));

    destroy_matrix(&m1);
    destroy_matrix(&m2);
    destroy_matrix(&result);
}

PRIVATE TEST void test_matrix_det_2x2(void)
{
    /* det(|1 2|) = 1*4 - 2*3 = -2 */
    /*     |3 4|                    */
    FP_TYPE arr[4] = {AS_FP(1), AS_FP(2), AS_FP(3), AS_FP(4)};
    linear_matrix_t m;
    FP_TYPE det;
    init_matrix_from_array(&m, arr, 2, 2);
    status_t r = matrix_det(&m, &det);

    ASSERT_IS_EQUAL(r, SUCCESS);
    ASSERT_IS_EQUAL(det, -AS_FP(2));

    destroy_matrix(&m);
}

PRIVATE TEST void test_matrix_det_3x3(void)
{
    /* det(|1 0 0|) = 6 */
    /*     |0 2 0|      */
    /*     |0 0 3|      */
    FP_TYPE arr[9] = {AS_FP(1), AS_FP(0), AS_FP(0), AS_FP(0), AS_FP(2),
                      AS_FP(0), AS_FP(0), AS_FP(0), AS_FP(3)};
    linear_matrix_t m;
    FP_TYPE det;
    init_matrix_from_array(&m, arr, 3, 3);
    status_t r = matrix_det(&m, &det);

    ASSERT_IS_EQUAL(r, SUCCESS);
    ASSERT_IS_EQUAL(det, AS_FP(6));

    destroy_matrix(&m);
}

PRIVATE TEST void test_matrix_inverse_2x2(void)
{
    /* |1 2|^-1 = 1/-2 * | 4 -2| = |-2   1  | */
    /* |3 4|              |-3  1|   | 1.5 -0.5| */
    FP_TYPE arr[4] = {AS_FP(1), AS_FP(2), AS_FP(3), AS_FP(4)};
    linear_matrix_t m;
    init_matrix_from_array(&m, arr, 2, 2);
    status_t r = matrix_inverse(&m);

    ASSERT_IS_EQUAL(r, SUCCESS);
    ASSERT_IS_EQUAL(m.data[0], -AS_FP(2));
    ASSERT_IS_EQUAL(m.data[1], AS_FP(1));
    ASSERT_IS_EQUAL(m.data[2], AS_FP(3) / 2);
    ASSERT_IS_EQUAL(m.data[3], -AS_FP(1) / 2);

    destroy_matrix(&m);
}

PRIVATE TEST void test_matrix_inverse_identity(void)
{
    /* inverse of identity is identity */
    linear_matrix_t m;
    init_identity_matrix(&m, 3);
    status_t r = matrix_inverse(&m);

    ASSERT_IS_EQUAL(r, SUCCESS);

    for (uint32_t i = 0; i < 3; ++i)
        for (uint32_t j = 0; j < 3; ++j) {
            FP_TYPE val;
            matrix_at(&m, &val, i, j);
            ASSERT_IS_EQUAL(val, i == j ? AS_FP(1) : AS_FP(0));
        }

    destroy_matrix(&m);
}

int main(void)
{
    test_init_matrix();
    test_init_identity_matrix();
    test_init_matrix_with();
    test_init_matrix_from_array();
    test_matrix_copy();
    test_matrix_negate();
    test_matrix_scale();
    test_matrix_add();
    test_matrix_transpose();
    test_matrix_dot_product();
    test_matrix_det_2x2();
    test_matrix_det_3x3();
    test_matrix_inverse_2x2();
    test_matrix_inverse_identity();
}
