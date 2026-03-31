#ifndef OBJECT_H
#define OBJECT_H

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
#include "matrix.h"
#include "other.h"

typedef enum state_idx { POSITION = 0, VELOCITY = 1, ACCELERATION = 2 } state_idx_t;

/*
 * Struct representing object state in single dimension
 * FP_TYPE obj_pos - object position     FORMAT: 64-bit/32-bit fixed-point
 * FP_TYPE obj_vel - object velocity     FORMAT: 64-bit/32-bit fixed-point
 * FP_TYPE obj_acc - object acceleration FORMAT: 64-bit/32-bit fixed-point
 *
 * Representation as matrix
 * 	***           ***
 *	*    position   *
 *	*    velocity   *
 *	*  acceleration *
 *	***           ***
 *
 * */
typedef struct one_dim_state {
    FP_TYPE obj_pos;  // position of the object in one dimension
    FP_TYPE obj_vel;  // velocity of the object in one dimension
    FP_TYPE obj_acc;  // acceleration of the object in one dimension
} one_dim_state_t;

typedef struct multidim_object_state {
    uint32_t n_dims;          // number of dimensions in which the object is moving
    one_dim_state_t* states;  // array of states for each dimension, size of the array is n_dims
} multidim_object_state_t;

/*
 * Cast a struct representing object state in single dimension to a matrix.
 * The resulting matrix will have 3 rows and 1 column, with the position, velocity, and
 * acceleration values from the struct.
 *
 * param struct_state (const one_dim_state_t *) - pointer to the struct representing object state in
 * single dimension
 * param m (linear_matrix_t *) - pointer to the matrix to store the casted values
 *
 * return (status_t) - operation status
 */
PUBLIC status_t matrix_cast(const one_dim_state_t* struct_state, linear_matrix_t* m);

/*
 * Function for checking if provided matrix can be casted to the struct representing object state in
 * single dimension. The matrix must have 3 rows and 1 column, with the position, velocity, and
 * acceleration values in the correct order.
 *
 * param m (const linear_matrix_t *) - pointer to the matrix to check
 *
 * return (bool_t) - TRUE if the matrix can be casted to the struct, FALSE otherwise
 */
PUBLIC bool_t is_valid_matrix(const linear_matrix_t* m);

/*
 * Function for converting a matrix to a struct representing object state in single dimension.
 * The matrix must have 3 rows and 1 column, with the position, velocity, and acceleration values
 * in the correct order.
 *
 * param m (const linear_matrix_t *) - pointer to the matrix to convert
 * param struct_state (one_dim_state_t *) - pointer to the struct to store the converted values
 *
 * return (status_t) - operation status
 */
PUBLIC status_t matrix_to_struct(const linear_matrix_t* m, one_dim_state_t* struct_state);

/*
 * Function for casting a struct representing object state in multiple dimensions to a matrix.
 * The resulting matrix will have 3 rows and n_dims columns, with the position, velocity, and
 * acceleration values from each dimension in the correct order.
 *
 * param struct_state (const multidim_object_state_t *) - pointer to the struct representing object
 * state in multiple dimensions
 * param m (linear_matrix_t *) - pointer to the matrix to store the
 * casted values
 *
 * return (status_t) - operation status
 */
PUBLIC status_t matrix_multidim_cast(const multidim_object_state_t* struct_state,
                                     linear_matrix_t* m);

/*
 * Function for checking if provided matrix can be casted to the struct representing object state in
 * multiple dimensions. The matrix must have 3 rows and n_dims columns, with the position,
 * velocity, and acceleration values for each dimension in the correct order.
 *
 * param m (const linear_matrix_t *) - pointer to the matrix to check
 *
 * return (bool_t) - TRUE if the matrix can be casted to the struct, FALSE otherwise
 */
PUBLIC bool_t is_valid_multidim_matrix(const linear_matrix_t* m, uint32_t n_dims);

/*
 * Function for converting a matrix to a struct representing object state in multiple dimensions.
 * The matrix must have 3 rows and n_dims columns, with the position, velocity, and acceleration
 * values for each dimension in the correct order.
 *
 * param m (const linear_matrix_t *) - pointer to the matrix to convert
 * param struct_state (multidim_object_state_t *) - pointer to the struct to store the converted
 * values
 *
 * return (status_t) - operation status
 */
PUBLIC status_t matrix_multidim_to_struct(const linear_matrix_t* m,
                                          multidim_object_state_t* struct_state);

#endif
