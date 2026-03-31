#include "../include/matrix.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/fp_arithmetic.h"
#include "../include/log.h"
#include "../include/other.h"

PUBLIC bool_t has_same_dims(const linear_matrix_t* m1, const linear_matrix_t* m2)
{
    if (!m1 || !m1->data || !m2 || !m2->data)
        return (bool_t)FALSE;
    if ((m1->n_rows == m2->n_rows) && (m1->n_cols == m2->n_cols))
        return (bool_t)TRUE;
    return (bool_t)FALSE;
}

PUBLIC bool_t is_square_matrix(const linear_matrix_t* m)
{
    if (!m || !m->data)
        return (bool_t)FALSE;
    if (m->n_rows == m->n_cols)
        return (bool_t)TRUE;
    return (bool_t)FALSE;
}

PUBLIC bool_t is_iteration(const linear_matrix_t* m1, const linear_matrix_t* m2)
{
    if (!m1 || !m1->data || !m2 || !m2->data)
        return (bool_t)FALSE;
    if (m1 == m2)
        return (bool_t)TRUE;

    const FP_TYPE* restrict md1 = m1->data;
    const FP_TYPE* restrict md2 = m2->data;
    /* Maybe can be optimalized from double loop into single or something like that) */
    if (m1->data && m2->data && has_same_dims(m1, m2)) {
        FP_TYPE factor = fp_divide(md1[0], md2[0]);

        // row -> col loop order to take advantage of L1 Cache
        // and quicker access to data
        for (uint32_t row_i = 0; row_i < m1->n_rows; ++row_i) {
            for (uint32_t col_i = 0; col_i < m1->n_cols; ++col_i) {
                FP_TYPE v1, v2;
                matrix_at(m1, &v1, row_i, col_i);
                matrix_at(m2, &v2, row_i, col_i);
                FP_TYPE temp_factor = fp_divide(v1, v2);
                if (temp_factor != factor)
                    return (bool_t)FALSE;
            }
        }
        return (bool_t)TRUE;
    }
    return (bool_t)FALSE;
}

PUBLIC status_t init_matrix(linear_matrix_t* m, const uint32_t n_rows, const uint32_t n_cols)
{
    if (!m)
        return ERR_NULL_DATA_POINTER;
    if (n_rows == 0 || n_cols == 0) {
        LOG_ERR("Invalid matrix dimensions");
        return ERR_INVALID_PARAMS;
    }
    m->data = (FP_TYPE*)calloc(n_rows * n_cols, sizeof(FP_TYPE));
    if (!m->data) {
        LOG_ERR("Failed to allocate memory for matrix during initialization");
        return ERR_MALLOC_FAILED;
    }
    m->n_rows = n_rows;
    m->n_cols = n_cols;
    m->is_init = (bool_t)TRUE;
    return SUCCESS;
}

PUBLIC status_t init_identity_matrix(linear_matrix_t* m, const uint32_t dim)
{
    status_t init_stat = init_matrix(m, dim, dim);
    if (init_stat != SUCCESS)
        return init_stat;

    // Instead of going into two loops and checking if row_i == col_i,
    // we can observe that index of 'one' in each row is just incrementing
    // by one in every itteration.
    // O(n^2) -> O(n)
    for (uint32_t row_i = 0; row_i < dim; ++row_i)
        m->data[row_i * (dim + 1)] = AS_FP(1);

    return SUCCESS;
}

PUBLIC status_t init_matrix_with(linear_matrix_t* m, const FP_TYPE content, const uint32_t n_rows,
                                 const uint32_t n_cols)
{
    status_t init_stat = init_matrix(m, n_rows, n_cols);
    if (init_stat != SUCCESS)
        return init_stat;
    for (uint32_t i = 0; i < n_rows * n_cols; ++i)
        m->data[i] = content;
    return SUCCESS;
}

PUBLIC status_t init_matrix_from_array(linear_matrix_t* m, const FP_TYPE* array,
                                       const uint32_t n_rows, const uint32_t n_cols)
{
    status_t init_stat = init_matrix(m, n_rows, n_cols);
    if (init_stat != SUCCESS)
        return init_stat;
    memcpy((FP_TYPE*)m->data, (FP_TYPE*)array, sizeof(FP_TYPE) * n_rows * n_cols);
    return SUCCESS;
}

PUBLIC status_t init_matrix_from_2d_array(linear_matrix_t* m, const FP_TYPE** array,
                                          const uint32_t n_rows, const uint32_t n_cols)
{
    status_t init_stat = init_matrix(m, n_rows, n_cols);
    if (init_stat != SUCCESS)
        return init_stat;

    for (uint32_t row_i = 0; row_i < n_rows; ++row_i)
        for (uint32_t col_i = 0; col_i < n_cols; ++col_i)
            matrix_put(m, array[row_i][col_i], row_i, col_i);

    return SUCCESS;
}

PUBLIC status_t matrix_copy(linear_matrix_t* restrict dest, const linear_matrix_t* restrict src)
{
    if (!dest || !src || !src->data)
        return ERR_NULL_DATA_POINTER;
    status_t init_res = init_matrix(dest, src->n_rows, src->n_cols);
    if (init_res != SUCCESS) {
        return init_res;
    }
    memcpy(dest->data, src->data, sizeof(FP_TYPE) * dest->n_rows * dest->n_cols);
    return SUCCESS;
}

PUBLIC status_t init_matrix_rand(linear_matrix_t* m, const uint32_t n_rows, const uint32_t n_cols,
                                 const unsigned int seed, const FP_TYPE min, const FP_TYPE max)
{
    if (min > max) {
        LOG_ERR("init_matrix_rand: min > max");
        return ERR_INVALID_PARAMS;
    }

    status_t init_stat = init_matrix(m, n_rows, n_cols);
    if (init_stat != SUCCESS)
        return init_stat;

    srand(seed);
    FP_TYPE delta = fp_substract(max, min);
    for (uint32_t i = 0; i < n_rows * n_cols; ++i) {
        FP_TYPE rand_val = fp_divide((FP_TYPE)rand(), (FP_TYPE)RAND_MAX);
        rand_val = fp_multiply(rand_val, delta);
        rand_val = fp_add(rand_val, min);

        m->data[i] = rand_val;
    }

    return SUCCESS;
}

PUBLIC status_t destroy_matrix(linear_matrix_t* m)
{
    if (!m)
        return ERR_NULL_DATA_POINTER;
    if (!m->data) {
        LOG_ERR("Cannot destroy matrix with NULL data");
        return ERR_MATRIX_DESTROY;
    }
    free(m->data);
    memset(m, 0, sizeof(linear_matrix_t));
    return SUCCESS;
}

PUBLIC status_t matrix_at(const linear_matrix_t* m, FP_TYPE* result, const uint32_t row,
                          const uint32_t col)
{
    if (!m || !m->data)
        return ERR_NULL_DATA_POINTER;
    if ((row >= m->n_rows) || (col >= m->n_cols)) {
        LOG_ERR("matrix_at: index out of range");
        return ERR_INDEX_OUT_OF_RANGE;
    }
    *result = m->data[row * m->n_cols + col];
    return SUCCESS;
}

PUBLIC status_t matrix_put(linear_matrix_t* m, const FP_TYPE value, const uint32_t row,
                           const uint32_t col)
{
    if (!m || !m->data)
        return ERR_NULL_DATA_POINTER;
    if ((row >= m->n_rows) || (col >= m->n_cols)) {
        LOG_ERR("matrix_put: index out of range");
        return ERR_INDEX_OUT_OF_RANGE;
    }
    m->data[row * m->n_cols + col] = value;
    return SUCCESS;
}

PUBLIC status_t matrix_negate(linear_matrix_t* m)
{
    if (!m || !m->data)
        return ERR_NULL_DATA_POINTER;
    FP_TYPE* restrict md = m->data;
    for (uint32_t i = 0; i < (m->n_rows * m->n_cols); ++i)
        md[i] = -md[i];
    return SUCCESS;
}

PUBLIC status_t matrix_scale(linear_matrix_t* m, const FP_TYPE factor)
{
    if (!m || !m->data)
        return ERR_NULL_DATA_POINTER;
    for (uint32_t row = 0; row < m->n_rows; ++row)
        for (uint32_t col = 0; col < m->n_cols; ++col) {
            FP_TYPE val;
            matrix_at(m, &val, row, col);
            matrix_put(m, fp_multiply(val, factor), row, col);
        }
    return SUCCESS;
}

PUBLIC status_t matrix_add(linear_matrix_t* m1, const linear_matrix_t* m2)
{
    if (!m1 || !m1->data || !m2 || !m2->data)
        return ERR_NULL_DATA_POINTER;
    if (m1 == m2)
        return matrix_scale(m1, AS_FP(2));

    if (!has_same_dims(m1, m2)) {
        LOG_ERR("matrix_add: dimension mismatch");
        return ERR_DIMENSION_MISMATCH;
    }

    for (uint32_t row = 0; row < m1->n_rows; ++row)
        for (uint32_t col = 0; col < m1->n_cols; ++col) {
            FP_TYPE v1, v2;
            matrix_at(m1, &v1, row, col);
            matrix_at(m2, &v2, row, col);
            matrix_put(m1, fp_add(v1, v2), row, col);
        }

    return SUCCESS;
}

PUBLIC status_t matrix_dot_product(const linear_matrix_t* m1, const linear_matrix_t* m2,
                                   linear_matrix_t* result)
{
    if (!m1 || !m1->data || !m2 || !m2->data || !result || !result->data)
        return ERR_NULL_DATA_POINTER;
    if (m1->n_cols != m2->n_rows) {
        LOG_ERR("matrix_dot_product: dimension mismatch");
        return ERR_DIMENSION_MISMATCH;
    }

    for (uint32_t row_m1 = 0; row_m1 < m1->n_rows; ++row_m1) {
        for (uint32_t col_m2 = 0; col_m2 < m2->n_cols; ++col_m2) {
            FP_TYPE temp_res = 0;
            for (uint32_t col_m1 = 0; col_m1 < m1->n_cols; ++col_m1) {
                FP_TYPE v1, v2;
                matrix_at(m1, &v1, row_m1, col_m1);
                matrix_at(m2, &v2, col_m1, col_m2);
                temp_res += fp_multiply(v1, v2);
            }
            matrix_put(result, temp_res, row_m1, col_m2);
        }
    }
    return SUCCESS;
}

PUBLIC status_t matrix_transpose(linear_matrix_t* m)
{
    if (!m || !m->data)
        return ERR_NULL_DATA_POINTER;
    FP_TYPE* buf = (FP_TYPE*)calloc(m->n_rows * m->n_cols, sizeof(FP_TYPE));
    if (!buf) {
        LOG_ERR("matrix_transpose: failed to allocate buffer");
        return ERR_MALLOC_FAILED;
    }

    for (uint32_t row = 0; row < m->n_rows; ++row)
        for (uint32_t col = 0; col < m->n_cols; ++col)
            buf[col * m->n_rows + row] = m->data[row * m->n_cols + col];

    free(m->data);
    m->data = buf;

    uint32_t temp = m->n_rows;
    m->n_rows = m->n_cols;
    m->n_cols = temp;

    return SUCCESS;
}

PRIVATE INLINE FP_TYPE for_det_calc_help(const FP_TYPE x1, const FP_TYPE x2, const FP_TYPE x3)
{
    return fp_multiply(fp_multiply(x1, x2), x3);
}

PUBLIC status_t matrix_det(const linear_matrix_t* m, FP_TYPE* result)
{
    if (!m || !m->data)
        return ERR_NULL_DATA_POINTER;
    const FP_TYPE* __restrict md = m->data;

    if (is_square_matrix(m)) {
        // TODO - in the future we need to implement real algorithm for
        // calculating determinant of all of the matrices
        switch (m->n_rows) {
            case 2: {
                FP_TYPE ad = fp_multiply(md[0], md[3]);
                FP_TYPE bc = fp_multiply(md[1], md[2]);

                *result = fp_substract(ad, bc);
                break;
            }
            case 3: {
                FP_TYPE aei = for_det_calc_help(md[0], md[4], md[8]);
                FP_TYPE bgf = for_det_calc_help(md[0], md[4], md[6]);
                FP_TYPE cdh = for_det_calc_help(md[2], md[3], md[7]);

                FP_TYPE ceg = for_det_calc_help(md[2], md[4], md[6]);
                FP_TYPE bdi = for_det_calc_help(md[1], md[3], md[8]);
                FP_TYPE afh = for_det_calc_help(md[0], md[5], md[7]);

                *result =
                    fp_substract(fp_add(fp_add(aei, bgf), cdh), fp_add(fp_add(ceg, bdi), afh));
                break;
            }
            default:
                LOG_ERR("matrix_det: unsupported matrix size");
                return ERR_UNSUPPORTED_TYPE;
        }
        return SUCCESS;
    }
    LOG_ERR("matrix_det: matrix is not square");
    return ERR_NOT_SQUARE_MATRIX;
}

PRIVATE INLINE FP_TYPE cofactor_calc_help(const FP_TYPE x1, const FP_TYPE x2, const FP_TYPE x3,
                                          const FP_TYPE x4)
{
    return fp_substract(fp_multiply(x1, x2), fp_multiply(x3, x4));
}

PUBLIC status_t matrix_inverse(linear_matrix_t* m)
{
    if (!m || !m->data)
        return ERR_NULL_DATA_POINTER;
    const FP_TYPE* __restrict md = m->data;

    FP_TYPE determinant;
    status_t determinant_res = matrix_det(m, &determinant);

    if (is_square_matrix(m) && determinant != AS_FP(0LL)) {
        FP_TYPE div_factor = fp_divide(AS_FP(1LL), determinant);
        switch (m->n_rows) {
            case 2: {
                FP_TYPE a = md[0], b = md[1], c = md[2], d = md[3];
                m->data[0] = fp_multiply(d, div_factor);
                m->data[1] = fp_multiply(-b, div_factor);
                m->data[2] = fp_multiply(-c, div_factor);
                m->data[3] = fp_multiply(a, div_factor);
                break;
            }
            case 3: {
                FP_TYPE c00 = cofactor_calc_help(md[4], md[8], md[5], md[7]);
                FP_TYPE c10 = -cofactor_calc_help(md[1], md[8], md[2], md[7]);
                FP_TYPE c20 = cofactor_calc_help(md[1], md[5], md[2], md[4]);

                FP_TYPE c01 = -cofactor_calc_help(md[3], md[8], md[5], md[6]);
                FP_TYPE c11 = cofactor_calc_help(md[0], md[8], md[2], md[6]);
                FP_TYPE c21 = -cofactor_calc_help(md[0], md[5], md[2], md[3]);

                FP_TYPE c02 = cofactor_calc_help(md[3], md[7], md[4], md[6]);
                FP_TYPE c12 = -cofactor_calc_help(md[0], md[7], md[1], md[6]);
                FP_TYPE c22 = cofactor_calc_help(md[0], md[4], md[1], md[3]);

                m->data[0] = fp_multiply(c00, div_factor);
                m->data[1] = fp_multiply(c10, div_factor);
                m->data[2] = fp_multiply(c20, div_factor);
                m->data[3] = fp_multiply(c01, div_factor);
                m->data[4] = fp_multiply(c11, div_factor);
                m->data[5] = fp_multiply(c21, div_factor);
                m->data[6] = fp_multiply(c02, div_factor);
                m->data[7] = fp_multiply(c12, div_factor);
                m->data[8] = fp_multiply(c22, div_factor);
                break;
            }
            default:
                LOG_ERR("matrix_inverse: unsupported matrix size");
                return ERR_UNSUPPORTED_TYPE;
        }
        return SUCCESS;
    } else {
        LOG_ERR("matrix_inverse: singular or non-square matrix");
        return determinant_res != SUCCESS ? determinant_res : ERR_SINGULAR_MATRIX;
    }
    return SUCCESS;
}
