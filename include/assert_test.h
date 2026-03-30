#ifndef ASSERT_H
#define ASSERT_H

/*
 * Copyright (c) 2026 Paweł Kozikowski
 *
 * This file contains the declarations of macros for asserting
 * and testing given inputs.
 * This file is part of a Kalman filter implementation in C.
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for full license information.
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef TEST
#define TEST
#endif /* TEST */

typedef enum test_result { TEST_SUCCESS = 0, TEST_FAILURE } test_result_t;

/*
 * ASSERT_IS_EQUAL - checks if a and b are the same
 *
 * param a: First comparable variable
 * param b: Second compatable variable
 * Informs user if assertion is finished with success or with failure.
 * In case of success it returns TEST_SUCCESS variable
 * In case of failure it returns TEST_FAILURE variable.
 */
#ifndef ASSERT_IS_EQUAL
#define ASSERT_IS_EQUAL(a, b)                               \
    do {                                                    \
        if ((a) != (b)) {                                   \
            printf("Assertion failed: %s != %s\n", #a, #b); \
            return TEST_FAILURE;                            \
        }                                                   \
        return TEST_SUCCESS;                                \
    } while (0)
#endif /* ASSERT_IS_EQUAL */

/*
 * ASSERT_IS_APPROX_EQUAL - checks if a and b are approximately the same
 *
 * param a: First comparable variable
 * param b: Second comparable variable
 * param epsilon: Maximum allowed difference between a and b
 * Informs user if assertion is finished with success or with failure.
 * In case of success it returns TEST_SUCCESS variable
 * In case of failure it returns TEST_FAILURE variable.
 */
#ifndef ASSERT_IS_APPROX_EQUAL
#define ASSERT_IS_APPROX_EQUAL(a, b, epsilon)               \
    do {                                                    \
        if (fabs((a) - (b)) > (epsilon)) {                  \
            printf("Assertion failed: %s != %s\n", #a, #b); \
            return TEST_FAILURE;                            \
        }                                                   \
        return TEST_SUCCESS;                                \
    } while (0)
#endif /* ASSERT_IS_APPROX_EQUAL */

/*
 * ASSERT_IS_NOT_EQUAL - checks if a and b are not the same
 *
 * param a: First comparable variable
 * param b: Second comparable variable
 * Informs user if assertion is finished with success or with failure.
 * In case of success it returns TEST_SUCCESS variable
 * In case of failure it returns TEST_FAILURE variable.
 */
#ifndef ASSERT_IS_NOT_EQUAL
#define ASSERT_IS_NOT_EQUAL(a, b)                           \
    do {                                                    \
        if ((a) == (b)) {                                   \
            printf("Assertion failed: %s == %s\n", #a, #b); \
            return TEST_FAILURE;                            \
        }                                                   \
        return TEST_SUCCESS;                                \
    } while (0)
#endif /* ASSERT_IS_NOT_EQUAL */

/*
 * ASSERT_IS_APPROX_NOT_EQUAL - checks if a and b are not approximately the same
 *
 * param a: First comparable variable
 * param b: Second comparable variable
 * param epsilon: Maximum allowed difference between a and b
 * Informs user if assertion is finished with success or with failure.
 * In case of success it returns TEST_SUCCESS variable
 * In case of failure it returns TEST_FAILURE variable.
 */
#ifndef ASSERT_IS_APPROX_NOT_EQUAL
#define ASSERT_IS_APPROX_NOT_EQUAL(a, b, epsilon)           \
    do {                                                    \
        if (fabs((a) - (b)) <= (epsilon)) {                 \
            printf("Assertion failed: %s == %s\n", #a, #b); \
            return TEST_FAILURE;                            \
        }                                                   \
        return TEST_SUCCESS;                                \
    } while (0)
#endif /* ASSERT_IS_APPROX_NOT_EQUAL */

/*
 * ASSERT_IS_GREATER_THAN - checks if a is greater than b
 *
 * param a: First comparable variable
 * param b: Second comparable variable
 * Informs user if assertion is finished with success or with failure.
 * In case of success it returns TEST_SUCCESS variable
 * In case of failure it returns TEST_FAILURE variable.
 */
#ifndef ASSERT_IS_GREATER_THAN
#define ASSERT_IS_GREATER_THAN(a, b)                        \
    do {                                                    \
        if ((a) <= (b)) {                                   \
            printf("Assertion failed: %s <= %s\n", #a, #b); \
            return TEST_FAILURE;                            \
        }                                                   \
        return TEST_SUCCESS;                                \
    } while (0)
#endif /* ASSERT_IS_GREATER_THAN */

/*
 * ASSERT_IS_LESS_THAN - checks if a is less than b
 *
 * param a: First comparable variable
 * param b: Second comparable variable
 * Informs user if assertion is finished with success or with failure.
 * In case of success it returns TEST_SUCCESS variable
 * In case of failure it returns TEST_FAILURE variable.
 */
#ifndef ASSERT_IS_LESS_THAN
#define ASSERT_IS_LESS_THAN(a, b)                           \
    do {                                                    \
        if ((a) >= (b)) {                                   \
            printf("Assertion failed: %s >= %s\n", #a, #b); \
            return TEST_FAILURE;                            \
        }                                                   \
        return TEST_SUCCESS;                                \
    } while (0)
#endif /* ASSERT_IS_LESS_THAN */

/*
 * ASSERT_IS_APPROX_GREATER_THAN - checks if a is approximately greater than b
 *
 * param a: First comparable variable
 * param b: Second comparable variable
 * param epsilon: Tolerance added to b for the comparison
 * Informs user if assertion is finished with success or with failure.
 * In case of success it returns TEST_SUCCESS variable
 * In case of failure it returns TEST_FAILURE variable.
 */
#ifndef ASSERT_IS_APPROX_GREATER_THAN
#define ASSERT_IS_APPROX_GREATER_THAN(a, b, epsilon)        \
    do {                                                    \
        if ((a) <= (b) + (epsilon)) {                       \
            printf("Assertion failed: %s <= %s\n", #a, #b); \
            return TEST_FAILURE;                            \
        }                                                   \
        return TEST_SUCCESS;                                \
    } while (0)
#endif /* ASSERT_IS_APPROX_GREATER_THAN */

/*
 * ASSERT_IS_APPROX_LESS_THAN - checks if a is approximately less than b
 *
 * param a: First comparable variable
 * param b: Second comparable variable
 * param epsilon: Tolerance subtracted from b for the comparison
 * Informs user if assertion is finished with success or with failure.
 * In case of success it returns TEST_SUCCESS variable
 * In case of failure it returns TEST_FAILURE variable.
 */
#ifndef ASSERT_IS_APPROX_LESS_THAN
#define ASSERT_IS_APPROX_LESS_THAN(a, b, epsilon)           \
    do {                                                    \
        if ((a) >= (b) - (epsilon)) {                       \
            printf("Assertion failed: %s >= %s\n", #a, #b); \
            return TEST_FAILURE;                            \
        }                                                   \
        return TEST_SUCCESS;                                \
    } while (0)
#endif /* ASSERT_IS_APPROX_LESS_THAN */

/*
 * ASSERT_IS_GREATER_THAN_OR_EQUAL - checks if a is greater than or equal to b
 *
 * param a: First comparable variable
 * param b: Second comparable variable
 * Informs user if assertion is finished with success or with failure.
 * In case of success it returns TEST_SUCCESS variable
 * In case of failure it returns TEST_FAILURE variable.
 */
#ifndef ASSERT_IS_GREATER_THAN_OR_EQUAL
#define ASSERT_IS_GREATER_THAN_OR_EQUAL(a, b)              \
    do {                                                   \
        if ((a) < (b)) {                                   \
            printf("Assertion failed: %s < %s\n", #a, #b); \
            return TEST_FAILURE;                           \
        }                                                  \
        return TEST_SUCCESS;                               \
    } while (0)
#endif /* ASSERT_IS_GREATER_THAN_OR_EQUAL */

/*
 * ASSERT_IS_LESS_THAN_OR_EQUAL - checks if a is less than or equal to b
 *
 * param a: First comparable variable
 * param b: Second comparable variable
 * Informs user if assertion is finished with success or with failure.
 * In case of success it returns TEST_SUCCESS variable
 * In case of failure it returns TEST_FAILURE variable.
 */
#ifndef ASSERT_IS_LESS_THAN_OR_EQUAL
#define ASSERT_IS_LESS_THAN_OR_EQUAL(a, b)                 \
    do {                                                   \
        if ((a) > (b)) {                                   \
            printf("Assertion failed: %s > %s\n", #a, #b); \
            return TEST_FAILURE;                           \
        }                                                  \
        return TEST_SUCCESS;                               \
    } while (0)
#endif /* ASSERT_IS_LESS_THAN_OR_EQUAL */

/*
 * ASSERT_IS_APPROX_GREATER_THAN_OR_EQUAL - checks if a is approximately greater than or equal to b
 *
 * param a: First comparable variable
 * param b: Second comparable variable
 * param epsilon: Tolerance subtracted from b for the comparison
 * Informs user if assertion is finished with success or with failure.
 * In case of success it returns TEST_SUCCESS variable
 * In case of failure it returns TEST_FAILURE variable.
 */
#ifndef ASSERT_IS_APPROX_GREATER_THAN_OR_EQUAL
#define ASSERT_IS_APPROX_GREATER_THAN_OR_EQUAL(a, b, epsilon) \
    do {                                                      \
        if ((a) < (b) - (epsilon)) {                          \
            printf("Assertion failed: %s < %s\n", #a, #b);    \
            return TEST_FAILURE;                              \
        }                                                     \
        return TEST_SUCCESS;                                  \
    } while (0)
#endif /* ASSERT_IS_APPROX_GREATER_THAN_OR_EQUAL */

/*
 * ASSERT_IS_APPROX_LESS_THAN_OR_EQUAL - checks if a is approximately less than or equal to b
 *
 * param a: First comparable variable
 * param b: Second comparable variable
 * param epsilon: Tolerance added to b for the comparison
 * Informs user if assertion is finished with success or with failure.
 * In case of success it returns TEST_SUCCESS variable
 * In case of failure it returns TEST_FAILURE variable.
 */
#ifndef ASSERT_IS_APPROX_LESS_THAN_OR_EQUAL
#define ASSERT_IS_APPROX_LESS_THAN_OR_EQUAL(a, b, epsilon) \
    do {                                                   \
        if ((a) > (b) + (epsilon)) {                       \
            printf("Assertion failed: %s > %s\n", #a, #b); \
            return TEST_FAILURE;                           \
        }                                                  \
        return TEST_SUCCESS;                               \
    } while (0)
#endif /* ASSERT_IS_APPROX_LESS_THAN_OR_EQUAL */

#endif
