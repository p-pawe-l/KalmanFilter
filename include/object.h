#ifndef OBJECT_H
#define OBJECT_H

#include <stdint.h>

#include "fp_arithmetic.h"
#include "matrix.h"

#define STATE_INDICIES 3

#define STATE_POS_IDX 0
#define STATE_VEL_IDX 1
#define STATE_ACC_IDX 2

/*
 * Struct representing object state in single dimension
 * int64_t obj_pos - object position     FORMAT: 64 bit fixed-point
 * int64_t obj_vel - object velocity     FORMAT: 64 bit fixed-point
 * int64_t obj_acc - object acceleration FORMAT: 64 bit fixed-point
 *
 * Representation as matrix
 * 	***           ***
 *	*    position   *
 *	*    velocity   *
 *	*  acceleration *
 *	***           ***
 *
 * */
typedef struct {
        FP_TYPE obj_pos;
        FP_TYPE obj_vel;
        FP_TYPE obj_acc;
} __one_dim_object_state;

linear_matrix_t matrix_cast(const __one_dim_object_state *struct_state);

#endif
