#ifndef MATRIX_H
#define MATRIX_H

/* 
 * Copyright (c) 2026 Paweł Kozikowski
 * 
 * File contains declaration of matrix structure and functions that operate on it.
 * This file is part of Kalman filter implementation in C.
 * 
 * License under the MIT License. 
 * See LICENSE file in the project root for full license information.
 */

#include "other.h"
#include "fixed_point/fp_arithmetic.h"

#include <stdint.h>

typedef enum matrix_operation_status {
	SUCCESS = 0,
	ERR_MALLOC_FAILED,
	ERR_MATRIX_DESTROY,
	ERR_INVALID_PARAMS,
	ERR_DIMENSION_MISMATCH,
	ERR_SINGULAR_MATRIX,
	ERR_NON_SQUARE_MATRIX,
	ERR_INDEX_OUT_OF_RANGE,
	ERR_NULL_DATA_POINTER,
	ERR_UNSUPPORTED_TYPE
} mo_status_t;

/*
 * Representation of linear matrix
 * What does it mean, linear ? Example:
 * Normal matrix would look like this and would be normally stored as two 
 * dimensional array (FP_TYPE **). But this could be inefficient way of 
 * storing numbers like this
 * |a b|
 * |c d|
 *
 * Linear matrix data is stored as single array. Thanks to that are data is
 * placed in contigous way. This potenital enables vector operations on our
 * CPU with a little optimization needed.
 * |a b|c d|
 * 
 * attribute data (FP_TYPE*) - array with numbers
 * n_rows         (uint32_t ) - number of rows of our matrix
 * n_cols         (uint32_t ) - number of columns in our matrix
 * 
 * We still need to track number of columns and rows to check whether
 * matrices can be added or multiplied etc.
 */
typedef struct linear_matrix {
        FP_TYPE *data;

        uint32_t n_rows;
        uint32_t n_cols;
} linear_matrix_t;


#define HAS_SAME_DIMS(m1, m2) 	( ( m1->n_rows == m2->n_rows ) && ( m1->n_cols == m2->n_cols ) )
#define IS_SQUARE_MATRIX(m1)	( m1->n_rows == m1->n_cols )
#define CAN_MULTIPLY(m1, m2) 	( m1->n_cols == m2->n_rows ) 

/*
 * Initializing matrix
 * Initialize matrix data attribute with sufficient memory (malloc used), assign rows and cols
 * to proper attributes
 * 
 * param m 	(linear_matrix_t *) - pointer to the matrix that will be initialized
 * param n_rows (const uint32_t) - number of rows that initialized matrix will have
 * param n_cols (const uint32_t) - number of columns that initialized matrix will have
 * 
 * return (mo_status_t) - status of the operation
 */
PUBLIC mo_status_t init_matrix(linear_matrix_t *m, const uint32_t n_rows, const uint32_t n_cols);

/*
 * Initializing identity matrix 
 * Initialize matrix data attribute with sufficient memory (malloc used), assign rows and cols
 * to proper attributes, and fill the matrix with identity matrix content (1 on the diagonal, 0 everywhere else).
 * 
 * param m (linear_matrix_t *) - pointer to the matrix that will be initialized
 * param n_rows (const uint32_t) - number of rows that initialized matrix will have
 * param n_cols (const uint32_t) - number of columns that initialized matrix will have
 * 
 * return (mo_status_t) - status of the operation
 */
PUBLIC mo_status_t init_identity_matrix(linear_matrix_t *m, const uint32_t n_rows, const uint32_t n_cols);

/*
 * Initializing zero matrix
 * Initialize matrix data attribute with sufficient memory (malloc used), assign rows and cols
 * to proper attributes, and fill the matrix with zeros (0 everywhere).
 * 
 * param m (linear_matrix_t *) - pointer to the matrix that will be initialized
 * param n_rows (const uint32_t) - number of rows that initialized matrix will have
 * param n_cols (const uint32_t) - number of columns that initialized matrix will have
 * 
 * return (mo_status_t) - status of the operation
 */
PUBLIC mo_status_t init_zero_matrix(linear_matrix_t *m, const uint32_t n_rows, const uint32_t n_cols);

/*
 * Initializing matrix with only ones
 * Initialize matrix data attribute with sufficient memory (malloc used), assign rows and cols
 * to proper attributes, and fill the matrix with ones (1 everywhere).
 * 
 * param m (linear_matrix_t *) - pointer to the matrix that will be initialized
 * param n_rows (const uint32_t) - number of rows that initialized matrix will have
 * param n_cols (const uint32_t) - number of columns that initialized matrix will have
 * 
 * return (mo_status_t) - status of the operation
 */
PUBLIC mo_status_t init_one_matrix(linear_matrix_t *m, const uint32_t n_rows, const uint32_t n_cols);

PUBLIC mo_status_t init_matrix_from_array(linear_matrix_t *m, const FP_TYPE *array, const uint32_t n_rows, const uint32_t n_cols);

PUBLIC mo_status_t init_matrix_from_2d_array(linear_matrix_t *m, const FP_TYPE **array, const uint32_t n_rows, const uint32_t n_cols);

PUBLIC mo_status_t matrix_copy(linear_matrix_t * __restrict dest, const linear_matrix_t * __restrict src);

/*
 * Initializing matrix with random numbers
 * Initialize matrix data attribute with sufficient memory (malloc used), assign rows and cols
 * to proper attributes, and fill the matrix with random numbers.
 * 
 * param m (linear_matrix_t *) - pointer to the matrix that will be initialized
 * param n_rows (const uint32_t) - number of rows that initialized matrix will have
 * param n_cols (const uint32_t) - number of columns that initialized matrix will have
 *	
 * return (mo_status_t) - status of the operation
 */
PUBLIC mo_status_t init_matrix_rand(linear_matrix_t *m, const uint32_t n_rows, const uint32_t n_cols);

/*
 * Initializing matrix with provided content
 * Initialize matrix data attribute with sufficient memory (malloc used), assign rows and cols
 * to proper attributes, and fill the matrix with provided content.
 * 
 * param m (linear_matrix_t *) - pointer to the matrix that will be initialized
 * param content (const FP_TYPE) - number that will be used to fill our matrix (64-bit/32-bit fixed-point format)
 * param n_rows (const uint32_t) - number of rows that initialized matrix will have
 * param n_cols (const uint32_t) - number of columns that initialized matrix will have
 *
 * return (mo_status_t) - status of the operation
 */
PUBLIC mo_status_t init_matrix_with(linear_matrix_t *m, const FP_TYPE content, const uint32_t n_rows, const uint32_t n_cols);

/*
 * Destroying matrix`s resources function
 * Just release memory of array that each matrix is holding (free)
 * 
 * param m (linear_matrix_t *) - pointer to matrix that resources will be destroyed
 *
 * return (mo_status_t) - status of the operation
 */
PUBLIC mo_status_t destroy_matrix(linear_matrix_t *m);

/*
 * Fetching number from provided index function
 * User provides number of row and column that he is willing to get a number from
 * and this function just calculates position and fetch the number
 *
 * param m (const linear_matrix_t *) - pointer to the matrix that we will be fetching from
 * param row (const uint32_t) - number of the row to fetch from
 * param col (const uint32_t) - number of the column to fetch from 
 *
 * return (mo_status_t) - status of the operation
 */
PUBLIC mo_status_t matrix_at(const linear_matrix_t *m, const uint32_t row, const uint32_t col);

/*
 * Negating all of the numbers in the matrix function 
 * Takes all of our numbers in matrix and negate them
 *
 * param m (const linear_matrix_t *) - pointer to the matrix that will be negated
 *
 * return (mo_status_t) - status of the operation
 */
PUBLIC mo_status_t matrix_negate(const linear_matrix_t *m);

/*
 * Scaling matrix function
 * Takes all of our numbers in matrix and multiply them by provided factor
 *
 * param m (const linear_matrix_t *) - pointer to the matrix that will be scaled
 * param factor (const FP_TYPE) - number that will be used to scale our matrix (64-bit/32-bit fixed-point format)
 *
 * return (mo_status_t) - status of the operation
 */
PUBLIC mo_status_t matrix_scale(const linear_matrix_t *m, const FP_TYPE factor);

/*
 * Adding two matrices function
 * Take all of the numbers from matrix-1 array and matrix-2 array, add them together on
 * matching indexes and BOOM, addition performed.
 *
 * param m1	(const linear_matrix_t * __restrict) - pointer to the first matrix  (__restrict for vectorized operations on CPU)
 * param m2	(const linear_matrix_t * __restrict) - pointer to the second matrix (__restrict for vectorized operations on CPU) 
 * 
 * return (mo_status_t) - status of the operation
 * */
PUBLIC mo_status_t matrix_add(const linear_matrix_t *__restrict m1, const linear_matrix_t *__restrict m2);

/*
* Dot product of two matrices function
* In other words just multiplying two matrices by itself
*
* param m1	(const linear_matrix_t * __restrict) - pointer to the first matrix  (__restrict for vectorized operations on CPU)
* param m2	(const linear_matrix_t * __restrict) - pointer to the second matrix (__restrict for vectorized operations on CPU) 
* 
* return (mo_status_t) - status of the operation
*/
PUBLIC mo_status_t matrix_dot_product(const linear_matrix_t *__restrict m1, const linear_matrix_t *__restrict m2);

/*
 * Transposing matrix function
 * This function swaps rows with columns in the matrix.
 *
 * param m (const linear_matrix_t *) - pointer to the matrix that will be transposed
 *
 * return (mo_status_t) - status of the operation
 */
PUBLIC mo_status_t matrix_transpose(const linear_matrix_t *m);

/*
 * Calculating determinant of a matrix function
 * This function calculates the determinant of a square matrix.
 *
 * param m (const linear_matrix_t *) - pointer to the matrix whose determinant will be calculated
 *
 * return (mo_status_t) - status of the operation
 */
PUBLIC mo_status_t matrix_det(const linear_matrix_t *m);

/*
 * Inverting matrix function
 * This function calculates the inverse of a square matrix.
 *
 * param m (const linear_matrix_t *) - pointer to the matrix that will be inverted
 *
 * return (mo_status_t) - status of the operation
 */
PUBLIC mo_status_t matrix_inverse(const linear_matrix_t *m);

#endif
