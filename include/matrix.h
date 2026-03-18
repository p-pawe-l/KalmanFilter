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
 * n_rows         (uint8_t ) - number of rows of our matrix
 * n_cols         (uint8_t ) - number of columns in our matrix
 * 
 * We still need to track number of columns and rows to check whether
 * matrices can be added or multiplied etc.
 * */
typedef struct linear_matrix {
        FP_TYPE *data;

        uint32_t n_rows;
        uint32_t n_cols;
} linear_matrix_t;

typedef struct fp_type_result {
        FP_TYPE result;
        
        mo_status_t status_code;
} FP_TYPE_RESULT;

typedef struct linear_matrix_result {
        linear_matrix_t result;
      
        mo_status_t status_code;
} LINEAR_MATRIX_RESULT;


#define HAS_SAME_DIMS(m1, m2) 	( ( m1->n_rows == m2->n_rows ) && ( m1->n_cols == m2->n_cols ) )
#define IS_SQUARE_MATRIX(m1)	( m1->n_rows == m1->n_cols )
#define CAN_MULTIPLY(m1, m2) 	( m1->n_cols == m2->n_rows ) 

/*
 * Initializing matrix function
 * Initialize matrix data attribute with sufficient memory (malloc used), assign rows and cols
 * to proper attributes
 * 
 * param m 	(struct linear_matrix *) - pointer to the matrix that will be initialized
 * param n_rows (const uint8_t         ) - number of rows that initialized matrix will have
 * param n_cols (const uint8_t	       ) - number of columns that initialized matrix will have
 * 
 * return void
 * */
PUBLIC mo_status_t init_matrix(linear_matrix_t *m, const uint32_t n_rows, const uint32_t n_cols);

/*
 * Destroying matrix`s resources function
 * Just release memory of array that each matrix is holding (free)
 * 
 * param m	(struct linear_matrix *) - pointer to matrix that resources will be desotryed
 *
 * return void
 * */
PUBLIC mo_status_t destroy_matrix(linear_matrix_t *m);

/*
 * Fetching number from provided index function
 * User provides number of row and column that he is willing to get a number from
 * and this function just calculates position and fetch the number
 *
 * param m	(const struct linear_matrix *) - pointer to the matrix that we will be fetching from
 * param row	(const uint8_t 		     ) - number of the row to fetch from
 * param col    (const uint8_t		     ) - number of the column to fetch from 
 *
 * return	(FP_TYPE		     ) - fetched number in 64-bit/32-bit fixed-point format
 * */
PUBLIC FP_TYPE_RESULT at(const linear_matrix_t *m, const uint32_t row, const uint32_t col);


/*
 * Negating all of the numbers in the matrix function 
 * Takes all of our numbers in matrix and negate them
 *
 * param	(const struct linear_matrix *) - pointer to the matrix that will be negate
 *
 * return	(struct linear_matrix        ) - new matrix with negated values
 * */
PUBLIC LINEAR_MATRIX_RESULT negate(const linear_matrix_t *m);

PUBLIC LINEAR_MATRIX_RESULT scale(const linear_matrix_t *m, const FP_TYPE factor);

/*
 * Adding two matrices function
 * Take all of the numbers from matrix-1 array and matrix-2 array, add them together on
 * matching indexes and BOOM, addition performed.
 *
 * param m1	(const struct linear_matrix * __restrict) - pointer to the first matrix  (__restrict for vectorized operations on CPU)
 * parma m2	(const struct_linear_matrix * __restrict) - pointer to the second matrix (__restrict for vectorized operations on CPU) 
 * 
 * return 	(struct linear_matrix			) - new matrix that results from adding two matrices to each other
 * */
PUBLIC LINEAR_MATRIX_RESULT add_matrices(const linear_matrix_t *__restrict m1, const linear_matrix_t *__restrict m2);

/*
* Dot product of two matrices function
* In other words just multiplying two matrices by itself
*
* param m1	(const struct linear_matrix * __restrict) - pointer to the first matrix  (__restrict for vectorized operations on CPU)
* parma m2	(const struct_linear_matrix * __restrict) - pointer to the second matrix (__restrict for vectorized operations on CPU) 
* 
* return 	(struct linear_matrix			) - new matrix that results from multiplying two matrices to each other
*
*/
PUBLIC LINEAR_MATRIX_RESULT dot_product(const linear_matrix_t *__restrict m1, const linear_matrix_t *__restrict m2);

/*
 * Transposing matrix function
 * This function swaps rows with columns in the matrix.
 *
 * param m	(const struct linear_matrix *) - pointer to the matrix that will be transposed
 *
 * return 	(struct linear_matrix) - new matrix that is the transpose of the input matrix
 * */
PUBLIC LINEAR_MATRIX_RESULT transpose(const linear_matrix_t *m);

/*
 * Calculating determinant of a matrix function
 * This function calculates the determinant of a square matrix.
 *
 * param m	(const struct linear_matrix *) - pointer to the matrix whose determinant will be calculated
 *
 * return 	(FP_TYPE) - determinant of the matrix
 * */
PUBLIC FP_TYPE_RESULT det(const linear_matrix_t *m);

/*
 * Inverting matrix function
 * This function calculates the inverse of a square matrix.
 *
 * param m	(const struct linear_matrix *) - pointer to the matrix that will be inverted
 *
 * return 	(struct linear_matrix) - new matrix that is the inverse of the input matrix
 * */
PUBLIC LINEAR_MATRIX_RESULT inverse(const linear_matrix_t *m);

#endif
