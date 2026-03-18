#ifndef MATRIX_H
#define MATRIX_H

#include "other.h"
#include "fixed_point/fp_arithmetic.h"

#include <stdint.h>

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
struct linear_matrix {
        FP_TYPE *data;

        uint8_t n_rows;
        uint8_t n_cols;
};

#define HAS_SAME_DIMS(m1, m2) 	( ( m1->n_rows == m2->n_rows ) && ( m1->n_cols == m2->n_cols ) )
#define IS_SQUARE_MATRIX(m1)	( m1->n_rows == m1->n_cols )
#define CAN_MULTUIPLY(m1, m2) 	( m1->n_cols == m2->n_rows ) 

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
PUBLIC void init_matrix(struct linear_matrix *m, const uint8_t n_rows, const uint8_t n_cols);

/*
 * Destroying matrix`s resources function
 * Just release memory of array that each matrix is holding (free)
 * 
 * param m	(struct linear_matrix *) - pointer to matrix that resources will be desotryed
 *
 * return void
 * */
PUBLIC void destroy_matrix(struct linear_matrix *m);

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
PUBLIC FP_TYPE at(const struct linear_matrix *m, const uint8_t row, const uint8_t col);


/*
 * Negating all of the numbers in the matrix function 
 * Takes all of our numbers in matrix and negate them
 *
 * param	(const struct linear_matrix *) - pointer to the matrix that will be negate
 *
 * return	(struct linear_matrix        ) - new matrix with negated values
 * */
PUBLIC struct linear_matrix negate(const struct linear_matrix *m);

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
PUBLIC struct linear_matrix add_matrices(const matrix_t * __restrict m1, const matrix_t * __restrict m2);

PUBLIC struct linear_matrix dot_product(const matrix_t * __restrict m1, const matrix_t * __restrict m2);

PUBLIC struct linear_matrix transpose(const matrix_t *m);

PUBLIC FP_TYPE det(const matrix_t* m);

PUBLIC struct linear_matrix inverse(const matrix_t *m);

#endif
