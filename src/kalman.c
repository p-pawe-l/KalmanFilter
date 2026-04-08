#include "../include/kalman.h"

#include "../include/log.h"
#include "../include/matrix.h"
#include "../include/other.h"

PUBLIC status_t init_system(system_t* sys, linear_matrix_t* initial_state)
{
    if (!sys || !initial_state) {
        LOG_ERR("Null pointer provided!");
        return ERR_NULL_DATA_POINTER;
    }

    sys->state_vector = initial_state;
    return SUCCESS;
}

PUBLIC status_t predict_next_state(system_t* sys, linear_matrix_t* next_state)
{
    if (!sys || !sys->state_vector || !sys->transition_matrix || !next_state) {
        LOG_ERR("Null pointer provided!");
        return ERR_NULL_DATA_POINTER;
    }

    status_t r = matrix_dot_product(sys->transition_matrix, sys->state_vector, next_state);
    return r;
}

PUBLIC status_t update_state(system_t* sys, linear_matrix_t* measurement)
{
    // TODO

    return SUCCESS;
}
