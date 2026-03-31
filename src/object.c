#include "../include/object.h"

#include <stdint.h>
#include <stdlib.h>

#include "../include/log.h"
#include "../include/other.h"

PUBLIC status_t matrix_cast(const one_dim_state_t* struct_state, linear_matrix_t* m)
{
    if (!struct_state || !m)
        return ERR_NULL_DATA_POINTER;
    status_t init_res = init_matrix(m, STATE_INDICES, 1);
    if (init_res != SUCCESS) {
        return init_res;
    }

    matrix_put(m, struct_state->obj_pos, POSITION, 0);
    matrix_put(m, struct_state->obj_vel, VELOCITY, 0);
    matrix_put(m, struct_state->obj_acc, ACCELERATION, 0);

    return SUCCESS;
}

PUBLIC bool_t is_valid_matrix(const linear_matrix_t* m)
{
    if (!m || !m->data)
        return (bool_t)FALSE;
    if ((m->n_rows == STATE_INDICES) && (m->n_cols == 1))
        return (bool_t)TRUE;
    return (bool_t)FALSE;
}

PUBLIC status_t matrix_to_struct(const linear_matrix_t* m, one_dim_state_t* struct_state)
{
    if (!m || !m->data || !struct_state)
        return ERR_NULL_DATA_POINTER;
    if (is_valid_matrix(m) == (bool_t)FALSE) {
        LOG_ERR("matrix_to_struct: invalid matrix dimensions");
        return ERR_INVALID_MATRIX;
    }

    matrix_at(m, &struct_state->obj_pos, POSITION, 0);
    matrix_at(m, &struct_state->obj_vel, VELOCITY, 0);
    matrix_at(m, &struct_state->obj_acc, ACCELERATION, 0);

    return SUCCESS;
}

PUBLIC status_t matrix_multidim_cast(const multidim_object_state_t* struct_state,
                                     linear_matrix_t* m)
{
    if (!struct_state || !struct_state->states || !m)
        return ERR_NULL_DATA_POINTER;
    status_t init_res = init_matrix(m, STATE_INDICES, struct_state->n_dims);
    if (init_res != SUCCESS) {
        return init_res;
    }

    status_t res;
    for (uint32_t dim_i = 0; dim_i < struct_state->n_dims; ++dim_i) {
        if ((res = matrix_put(m, struct_state->states[dim_i].obj_pos, POSITION, dim_i)) != SUCCESS)
            return res;
        if ((res = matrix_put(m, struct_state->states[dim_i].obj_vel, VELOCITY, dim_i)) != SUCCESS)
            return res;
        if ((res = matrix_put(m, struct_state->states[dim_i].obj_acc, ACCELERATION, dim_i)) !=
            SUCCESS)
            return res;
    }

    return SUCCESS;
}

PUBLIC bool_t is_valid_multidim_matrix(const linear_matrix_t* m, uint32_t n_dims)
{
    if (!m || !m->data)
        return (bool_t)FALSE;
    if ((m->n_rows == STATE_INDICES) && (m->n_cols == n_dims))
        return (bool_t)TRUE;
    return (bool_t)FALSE;
}

PUBLIC status_t matrix_multidim_to_struct(const linear_matrix_t* m,
                                          multidim_object_state_t* struct_state)
{
    if (!m || !m->data || !struct_state || !struct_state->states)
        return ERR_NULL_DATA_POINTER;
    if (is_valid_multidim_matrix(m, struct_state->n_dims) == (bool_t)FALSE) {
        LOG_ERR("matrix_multidim_to_struct: invalid matrix dimensions");
        return ERR_INVALID_MATRIX;
    }

    for (uint32_t dim_i = 0; dim_i < struct_state->n_dims; ++dim_i) {
        matrix_at(m, &struct_state->states[dim_i].obj_pos, POSITION, dim_i);
        matrix_at(m, &struct_state->states[dim_i].obj_vel, VELOCITY, dim_i);
        matrix_at(m, &struct_state->states[dim_i].obj_acc, ACCELERATION, dim_i);
    }

    return SUCCESS;
}