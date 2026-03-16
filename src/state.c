// #include "../include/matrix.h"

// matrix_t calc_new_state(const matrix_t old_state,
//                         const matrix_t state_transition_matrix) {
//         matrix_t new_state = dot_product(state_transition_matrix, old_state);
//         return new_state;
// }

// matrix_t calc_new_uncertainty(const matrix_t covariance_matrix,
//                               const matrix_t state_transition_matrix,
//                               const matrix_t process_noise_matrix) {
//         matrix_t new_uncertainty = dot_product(state_transition_matrix, covariance_matrix);
//         new_uncertainty = dot_product(new_uncertainty, transpose(state_transition_matrix));

//         new_uncertainty = add_matrices(new_uncertainty, process_noise_matrix);
//         return new_uncertainty;
// }

// matrix_t calc_kalman_factor(const matrix_t covariance_matrix,
//                             const matrix_t measurement_matrix,
//                             const matrix_t measurement_noise_matrix) {
//         matrix_t kalman_factor = dot_product(covariance_matrix, transpose(measurement_matrix));

//         matrix_t other = dot_product(measurement_matrix, covariance_matrix);
//         other = dot_product(other, transpose(measurement_matrix));
//         other = add_matrices(other, measurement_noise_matrix);

//         kalman_factor = dot_product(kalman_factor, inverse(other));
//         free_matrix(other);

//         return kalman_factor;
// }

// matrix_t update_uncertainty(const matrix_t covariance_matrix,
//                             const matrix_t identity_matrix,
//                             const matrix_t kalman_factor,
//                             const matrix_t measurement_matrix) {
//         matrix_t other = dot_product(kalman_factor, measurement_matrix);
//         other = add_matrices(identity_matrix, negate(other));

//         matrix_t new_uncertainty = dot_product(other, covariance_matrix);
//         free_matrix(other);

//         return new_uncertainty;
// }
