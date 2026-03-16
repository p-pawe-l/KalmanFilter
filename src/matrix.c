#include "../include/matrix.h"
#include "../include/other.h"
#include <stdlib.h>

PUBLIC void init_matrix(matrix_t *m, const uint8_t n_rows,
                        const uint8_t n_cols) {
        m->n_rows = n_rows;
        m->n_cols = n_cols;

        m->data = (int64_t **)malloc(sizeof(int64_t *) * n_rows);
        for (int i = 0; i < n_rows; i++) {
                m->data[i] = (int64_t *)malloc(sizeof(int64_t) * n_cols);
        }
}

PUBLIC void destroy_matrix(matrix_t *m) {
        for (uint8_t i = 0; i < m->n_rows; i++) {
                free(m->data[i]);
        }
        free(m->data);
}

PUBLIC matrix_t negate(const matrix_t *m) {
        matrix_t new_matrix;
        init_matrix(&new_matrix, m->n_rows, m->n_cols);
        for (uint8_t i = 0; i < m->n_rows; i++) {
                for (uint8_t ii = 0; ii < m->n_cols; i++) {
                        new_matrix.data[i][ii] = -m->data[i][ii];
                }
        }

        return new_matrix;
}

PUBLIC matrix_t add_matrices(const matrix_t *m1, const matrix_t *m2) {
        /* Check if same dims */
        matrix_t new_matrix;
        init_matrix(&new_matrix, m1->n_rows, m1->n_cols);
        for (uint8_t i = 0; i < m1->n_rows; i++) {
                for (uint8_t ii = 0; ii < m1->n_cols; ii++) {
                        new_matrix.data[i][ii] =
                            m1->data[i][ii] + m2->data[i][ii];
                }
        }

        return new_matrix;
}

PUBLIC matrix_t dot_product(const matrix_t *m1, const matrix_t *m2) {
        matrix_t new_matrix;
        init_matrix(&new_matrix, m2->n_rows, m1->n_cols);
        for (uint8_t i = 0; i < m2->n_cols; i++) {
                for (uint8_t ii = 0; ii < m1-> n_rows; ii++) {
                        int128_t result = m1->data[i][ii] * m2->data[ii][i];
                        result = result >> 32;
                        new_matrix.data[i][ii] = (int64_t)result;
                }
        }

        return new_matrix;
}

PUBLIC matrix_t transpose(const matrix_t *m) {
        matrix_t new_matrix;
        init_matrix(&new_matrix, m->n_cols, m->n_rows);
        for (uint8_t i = 0; i < m->n_cols; i++) {
                for (uint8_t ii = 0; ii < m->n_rows; i++) {
                        new_matrix.data[i][ii] = m->data[ii][i];
                }
        }

        return new_matrix;
}

PUBLIC matrix_t inverse(const matrix_t *m) {
        matrix_t new_matrix;
        init_matrix(&new_matrix, m->n_rows, m->n_cols);

        // TODO

        return new_matrix;
}
