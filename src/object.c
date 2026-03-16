#include <stdint.h>
#include <stdlib.h>

#include "../include/object.h"
#include "../include/matrix.h"


matrix_t matrix_cast(const __one_dim_object_state *struct_state) {
	matrix_t state_matrix = (matrix_t)malloc(sizeof(int64_t*) * STATE_INDICIES);
    	for (int i = 0; i < STATE_INDICIES; i++) {
        	state_matrix[i] = (int64_t*)malloc(sizeof(int64_t));
    	}
    
    	state_matrix[STATE_POS_IDX][0] = struct_state->obj_pos;
    	state_matrix[STATE_VEL_IDX][0] = struct_state->obj_vel;
    	state_matrix[STATE_ACC_IDX][0] = struct_state->obj_acc;

    	return state_matrix;
}
