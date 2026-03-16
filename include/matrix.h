#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

typedef struct {
        int64_t **data;

        uint8_t n_rows;
        uint8_t n_cols;
} matrix_t;

typedef int64_t *row_t;
typedef int64_t *col_t;

void init_matrix(matrix_t *m, const uint8_t n_rows, const uint8_t n_cols);
void destroy_matrix(matrix_t *m);

matrix_t negate(const matrix_t *m);
matrix_t add_matrices(const matrix_t *m1, const matrix_t *m2);
matrix_t dot_product(const matrix_t *m1, const matrix_t *m2);
matrix_t transpose(const matrix_t *m);
matrix_t inverse(const matrix_t *m);

#endif
