#ifndef MATRIX_H
#define MATRIX_H

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

#include "fp_arithmetic.h"
#include "other.h"

/*
 * Representation of a linear matrix.
 * What does "linear" mean? Example:
 * A regular matrix would look like this and would typically be stored as a
 * two-dimensional array (FP_TYPE **). However, that can be an inefficient way
 * to store numbers like these:
 * |a b|
 * |c d|
 *
 * Linear matrix data is stored as a single array. This keeps the data
 * contiguous in memory, which can enable vector operations on the CPU with
 * minimal additional optimization.
 * |a b|c d|
 *
 * attribute data (FP_TYPE*) - array of matrix elements
 * n_rows         (uint32_t) - number of rows in the matrix
 * n_cols         (uint32_t) - number of columns in the matrix
 * is_init        (bool_t)   - flag indicating, whether matrix was initialized
 *
 * We still need to track the number of rows and columns to check whether
 * matrices can be added or multiplied.
 */
typedef struct linear_matrix {
    FP_TYPE* data;  // Data

    uint32_t n_rows;  // Number of rows
    uint32_t n_cols;  // Number of columns

    bool_t is_init;  // Initialization flag
} linear_matrix_t;

/*
 * Check if two matrices have the same dimensions.
 * This function checks whether the number of rows and columns in the two
 * matrices are the same.
 *
 * param m1 (const linear_matrix_t *) - pointer to the first matrix
 * param m2 (const linear_matrix_t *) - pointer to the second matrix
 *
 * return (bool_t) - TRUE if the matrices have the same dimensions, FALSE otherwise
 */
PUBLIC bool_t has_same_dims(const linear_matrix_t* m1, const linear_matrix_t* m2);

/*
 * Check if a matrix is square.
 * This function checks whether the number of rows and columns in the matrix are equal.
 *
 * param m (const linear_matrix_t *) - pointer to the matrix to check
 *
 * return (bool_t) - TRUE if the matrix is square, FALSE otherwise
 */
PUBLIC bool_t is_square_matrix(const linear_matrix_t* m);

/*
 * Check if first matrix is iteration of the second matrix.
 * This function checks whether the first matrix is an iteration of the second
 * matrix. In other words, this function checks whether the first matrix can be
 * obtained by multiplying the second matrix by itself some number of times.
 *
 * param m1 (const linear_matrix_t *) - pointer to the first matrix
 * param m2 (const linear_matrix_t *) - pointer to the second matrix
 *
 * return (bool_t) - TRUE if the first matrix is an iteration of the second matrix, FALSE otherwise
 */
PUBLIC bool_t is_iteration(const linear_matrix_t* m1, const linear_matrix_t* m2);

/*
 * Initialize a matrix.
 * Allocate enough memory for the matrix data using malloc, then assign the
 * row and column counts to the appropriate attributes.
 *
 * param m (linear_matrix_t *) - pointer to the matrix to initialize
 * param n_rows (const uint32_t) - number of rows in the initialized matrix
 * param n_cols (const uint32_t) - number of columns in the initialized matrix
 *
 * return (status_t) - operation status
 */
PUBLIC status_t init_matrix(linear_matrix_t* m, const uint32_t n_rows, const uint32_t n_cols);

/*
 * Initialize an identity matrix.
 * Allocate enough memory for the matrix data using malloc, assign the row and
 * column counts to the appropriate attributes, and fill the matrix with the
 * identity matrix contents (1 on the diagonal, 0 elsewhere).
 *
 * param m (linear_matrix_t *) - pointer to the matrix to initialize
 * param n_rows (const uint32_t) - number of rows in the initialized matrix
 * param n_cols (const uint32_t) - number of columns in the initialized matrix
 *
 * return (status_t) - operation status
 */
PUBLIC status_t init_identity_matrix(linear_matrix_t* m, const uint32_t dims);

/*
 * Initialize a matrix from a 1D array.
 * Allocate enough memory for the matrix data using malloc, assign the row and
 * column counts to the appropriate attributes, and fill the matrix with the
 * provided contents from a 1D array.
 *
 * param m (linear_matrix_t *) - pointer to the matrix to initialize
 * param array (const FP_TYPE *) - pointer to a 1D array whose contents will be used to fill the
 * matrix (64-bit/32-bit fixed-point format) param n_rows (const uint32_t) - number of rows in the
 * initialized matrix param n_cols (const uint32_t) - number of columns in the initialized matrix
 *
 * return (status_t) - operation status
 */
PUBLIC status_t init_matrix_from_array(linear_matrix_t* m, const FP_TYPE* array,
                                       const uint32_t n_rows, const uint32_t n_cols);

/*
 * Initialize a matrix from a 2D array.
 * Allocate enough memory for the matrix data using malloc, assign the row and
 * column counts to the appropriate attributes, and fill the matrix with the
 * provided contents from a 2D array.
 *
 * param m (linear_matrix_t *) - pointer to the matrix to initialize
 * param array (const FP_TYPE **) - pointer to a 2D array whose contents will be used to fill the
 * matrix (64-bit/32-bit fixed-point format) param n_rows	(const uint32_t) - number of rows in
 * the initialized matrix param n_cols	(const uint32_t) - number of columns in the initialized
 * matrix
 *
 * return (status_t) - operation status
 */
PUBLIC status_t init_matrix_from_2d_array(linear_matrix_t* m, const FP_TYPE** array,
                                          const uint32_t n_rows, const uint32_t n_cols);
/*
 * Copy a matrix.
 * Copy the contents of one matrix into another matrix.
 *
 * param dest (linear_matrix_t *) - pointer to the destination matrix
 * param src (const linear_matrix_t *) - pointer to the source matrix
 *
 * return (status_t) - operation status
 */
PUBLIC status_t matrix_copy(linear_matrix_t* __restrict dest,
                            const linear_matrix_t* __restrict src);

/*
 * Initialize a matrix with random numbers.
 * Allocate enough memory for the matrix data using malloc, assign the row and
 * column counts to the appropriate attributes, and fill the matrix with random values.
 *
 * param m (linear_matrix_t *) - pointer to the matrix to initialize
 * param n_rows (const uint32_t) - number of rows in the initialized matrix
 * param n_cols (const uint32_t) - number of columns in the initialized matrix
 *
 * return (status_t) - operation status
 */
PUBLIC status_t init_matrix_rand(linear_matrix_t* m, const uint32_t n_rows, const uint32_t n_cols,
                                 const unsigned int seed, const FP_TYPE min, const FP_TYPE max);

/*
 * Initialize a matrix with a provided value.
 * Allocate enough memory for the matrix data using malloc, assign the row and
 * column counts to the appropriate attributes, and fill the matrix with the
 * provided value.
 *
 * param m (linear_matrix_t *) - pointer to the matrix to initialize
 * param content (const FP_TYPE) - value used to fill the matrix (64-bit/32-bit fixed-point format)
 * param n_rows (const uint32_t) - number of rows in the initialized matrix
 * param n_cols (const uint32_t) - number of columns in the initialized matrix
 *
 * return (status_t) - operation status
 */
PUBLIC status_t init_matrix_with(linear_matrix_t* m, const FP_TYPE content, const uint32_t n_rows,
                                 const uint32_t n_cols);

/*
 * Destroy a matrix's resources.
 * Release the memory used by the array owned by the matrix.
 *
 * param m (linear_matrix_t *) - pointer to the matrix whose resources will be released
 *
 * return (status_t) - operation status
 */
PUBLIC status_t destroy_matrix(linear_matrix_t* m);

/*
 * Fetch a value from a given index.
 * The caller provides a row and column index, and this function calculates
 * the corresponding position and stores the value in the provided pointer.
 *
 * param m (const linear_matrix_t *) - pointer to the matrix to read from
 * param res (FP_TYPE *) - pointer to store the fetched value (64-bit/32-bit fixed-point format)
 * param row (const uint32_t) - row index to read from
 * param col (const uint32_t) - column index to read from
 *
 * return (status_t) - operation status
 */
PUBLIC status_t matrix_at(const linear_matrix_t* m, FP_TYPE* res, const uint32_t row,
                          const uint32_t col);

/*
 * Put a value at a given index.
 * The caller provides a row and column index, and this function calculates
 * the corresponding position and stores the provided value there.
 *
 * param m (linear_matrix_t *) - pointer to the matrix to write to
 * param value (const FP_TYPE) - value to be stored at the specified index (64-bit/32-bit
 * fixed-point format) param row (const uint32_t) - row index to write to param col (const uint32_t)
 * - column index to write to
 *
 * return (status_t) - operation status
 */
PUBLIC status_t matrix_put(linear_matrix_t* m, const FP_TYPE value, const uint32_t row,
                           const uint32_t col);

/*
 * Negate all values in the matrix.
 * This function negates every value stored in the matrix.
 *
 * param m (const linear_matrix_t *) - pointer to the matrix that will be negated
 *
 * return (status_t) - operation status
 */
PUBLIC status_t matrix_negate(linear_matrix_t* m);

/*
 * Scale a matrix.
 * Multiply every value in the matrix by the provided factor.
 *
 * param m (const linear_matrix_t *) - pointer to the matrix that will be scaled
 * param factor (const FP_TYPE) - value used to scale the matrix (64-bit/32-bit fixed-point format)
 *
 * return (status_t) - operation status
 */
PUBLIC status_t matrix_scale(linear_matrix_t* m, const FP_TYPE factor);

/*
 * Add two matrices.
 * Add the values from the two matrices element by element at matching indexes.
 *
 * param m1	(const linear_matrix_t * __restrict) - pointer to the first matrix  (__restrict for
 * vectorized operations on CPU) param m2	(const linear_matrix_t * __restrict) - pointer to
 * the second matrix (__restrict for vectorized operations on CPU)
 *
 * return (status_t) - operation status
 */
PUBLIC status_t matrix_add(linear_matrix_t* m1, const linear_matrix_t* m2);

/*
 * Compute the dot product of two matrices.
 * In other words, this function multiplies two matrices together.
 *
 * param m1	(const linear_matrix_t * __restrict) - pointer to the first matrix  (__restrict for
 * vectorized operations on CPU) param m2	(const linear_matrix_t * __restrict) - pointer to
 * the second matrix (__restrict for vectorized operations on CPU)
 *
 * return (status_t) - operation status
 */
PUBLIC status_t matrix_dot_product(const linear_matrix_t* m1, const linear_matrix_t* m2,
                                   linear_matrix_t* result);

/*
 * Transpose a matrix.
 * This function swaps rows with columns in the matrix.
 *
 * param m (linear_matrix_t *) - pointer to the matrix that will be transposed
 *
 * return (status_t) - operation status
 */
PUBLIC status_t matrix_transpose(linear_matrix_t* m);

/*
 * Calculate the determinant of a matrix.
 * This function calculates the determinant of a square matrix.
 *
 * param m (const linear_matrix_t *) - pointer to the matrix whose determinant will be calculated
 *
 * return (status_t) - operation status
 */
PUBLIC status_t matrix_det(const linear_matrix_t* m, FP_TYPE* result);

/*
 * Invert a matrix.
 * This function calculates the inverse of a square matrix.
 *
 * param m (const linear_matrix_t *) - pointer to the matrix that will be inverted
 *
 * return (status_t) - operation status
 */
PUBLIC status_t matrix_inverse(linear_matrix_t* m);

#endif
