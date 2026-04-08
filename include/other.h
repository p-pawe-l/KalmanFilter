#ifndef OTHER_H
#define OTHER_H

/*
 * Copyright (c) 2026 Paweł Kozikowski
 *
 * This file contains the declaration of the matrix structure and the functions
 * that operate on it.
 * This file is part of a Kalman filter implementation in C.
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for full license information.
 */

#include <stdint.h>

#define PUBLIC
#define PRIVATE static
#define EXTERN extern
#define INLINE inline

typedef enum status {
    SUCCESS = 0,
    ERR_NON_INIT_MATRIX,
    ERR_MALLOC_FAILED,
    ERR_MATRIX_DESTROY,
    ERR_EMPTY_DATA_PTR,
    ERR_INVALID_PARAMS,
    ERR_DIMENSION_MISMATCH,
    ERR_SINGULAR_MATRIX,
    ERR_NON_SQUARE_MATRIX,
    ERR_INDEX_OUT_OF_RANGE,
    ERR_NULL_DATA_POINTER,
    ERR_UNSUPPORTED_TYPE,
    ERR_NOT_SQUARE_MATRIX,
    ERR_MATRIX_ACCESS,
    ERR_INVALID_MATRIX,
    ERR_CAST,
} status_t;

typedef uint8_t bool_t;

#define TRUE 0x01
#define FALSE 0x00

#endif
