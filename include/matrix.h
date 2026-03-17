#ifndef MATRIX_H
#define MATRIX_H

#include "other.h"
#include <stdint.h>

#define BIT_MASK_2b 0xB000000000000000
#define BIT_MASK_4b 0xF000000000000000
#define BIT_MASK_8b 0xFF00000000000000
#define BIT_MASK_16b 0xFFFF000000000000
#define BIT_MASK_32b 0xFFFFFFFF00000000

typedef union {
        int8_t __ds8_0;
        int8_t __ds8_1;

        int16_t __ds16_0;
} union_s16_t;

typedef union {
        union_s16_t __uni_D_s16_0;
        union_s16_t __uni_D_s16_1;

        int32_t __ds32_0;
} union_s32_t;

typedef union {
        union_s32_t __uni_D_s32_0;
        union_s32_t __uni_D_s32_1;

        int64_t __ds64_0;
} union_s64_t;

void init_union64(const int64_t __d64);

union_s64_t add_uni_64b(const union_s64_t *uni1, const union_s64_t *uni2);

int8_t at_uni_64b_8d(const union_s64_t *uni, const uint8_t index);
int16_t at_uni_64b_16d(const union_s64_t *uni, const uint8_t index);
int32_t at_uni_64b_32d(const union_s64_t *uni, const uint8_t index);

void init_union32(const int32_t __d32);
void init_union16(const int16_t __d16);

typedef struct {
        int64_t *data;

        uint8_t n_rows;
        uint8_t n_cols;
} matrix_t;

#define HAS_SAME_DIMS(m1, m2) ( ( m1->n_rows == m2->n_rows ) && ( m1->n_cols == m2->n_cols ) )
#define CAN_MULTUIPLY(m1, m2) ( m1->n_cols == m2->n_rows ) 

PUBLIC void init_matrix(matrix_t *m, const uint8_t n_rows, const uint8_t n_cols);
void destroy_matrix(matrix_t *m);

int64_t at(const matrix_t *m, const uint8_t row, const uint8_t col);

matrix_t negate(const matrix_t *m);
matrix_t add_matrices(const matrix_t * __restrict m1, const matrix_t * __restrict m2);
matrix_t dot_product(const matrix_t * __restrict m1, const matrix_t * __restrict m2);
matrix_t transpose(const matrix_t *m);
int64_t det(const matrix_t* m);
matrix_t inverse(const matrix_t *m);

#endif
