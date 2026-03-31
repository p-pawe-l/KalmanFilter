#ifndef KALMAN_H
#define KALMAN_H

/*
 * Copyright (c) 2026 Paweł Kozikowski
 *
 * This file contains the declaration of the Kalman filter implementation.
 * This file is part of a Kalman filter implementation in C.
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for full license information.
 */

#include <stdint.h>

#include "matrix.h"
#include "object.h"
#include "other.h"

/*
 * Kalman filter structure.
 * state_vector        (linear_matrix_t) - state vector (X)
 * transition_matrix   (linear_matrix_t) - transition matrix (F)
 * measurement_matrix  (linear_matrix_t) - measurement matrix (H)
 * process_noise_matrix (linear_matrix_t) - process noise matrix (Q)
 * measurement_noise_matrix (linear_matrix_t) - measurement noise matrix (R)
 *
 * Kalman filter is a recursive filter that estimates the state of a system from a series of
 * measurements. It is a optimal estimator in the sense that it minimizes the estimated error
 * covariance, which is a measure of the uncertainty of the estimate.
 */
typedef struct kalman_filter {
    linear_matrix_t state_vector;
    linear_matrix_t transition_matrix;
    linear_matrix_t measurement_matrix;
    linear_matrix_t process_noise_matrix;
    linear_matrix_t measurement_noise_matrix;
} kalman_filter_t;

/*
 * Macros for accessing the state vector, transition matrix, measurement matrix,
 * process noise matrix, and measurement noise matrix.
 */
#ifndef X
#define X state_vector
#endif /* X matrix */

#ifndef F
#define F transition_matrix
#endif /* F matrix */

#ifndef H
#define H measurement_matrix
#endif /* H matrix */

#ifndef Q
#define Q process_noise_matrix
#endif /* Q matrix */

#ifndef R
#define R measurement_noise_matrix
#endif /* R matrix */

/*
 * This function predicts the next state of the system.
 * param kf (kalman_filter_t*) - pointer to the Kalman filter
 * return (linear_matrix_t) - predicted next state
 */
PUBLIC linear_matrix_t predict_next_state(kalman_filter_t* kf);

/*
 * This function updates the state of the system.
 * param kf (kalman_filter_t*) - pointer to the Kalman filter
 * param measurement (linear_matrix_t*) - measurement
 * return (linear_matrix_t) - updated state
 */
PUBLIC linear_matrix_t update_state(kalman_filter_t* kf, linear_matrix_t* measurement);

#endif