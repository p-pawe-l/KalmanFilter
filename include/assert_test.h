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

#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"

#ifndef ASSERTION_FAILED
#define ASSERTION_FAILED(msg) \
    (fprintf(stderr, ANSI_RED "[FAIL] %s:%d: " msg "\n" ANSI_RESET, __FILE__, __LINE__))
#endif /* ASSERTION_FAILED */

#ifndef ASSERTION_SUCCEEDED
#define ASSERTION_SUCCEEDED(msg) \
    fprintf(stdout, ANSI_GREEN "[PASS] %s:%d: " msg "\n" ANSI_RESET, __FILE__, __LINE__)
#endif /* ASSERTION_SUCCEEDED */

/*
 * ASSERT_IS_EQUAL - checks if a and b are the same
 *
 * param a: First comparable variable
 * param b: Second comparable variable
 */
#ifndef ASSERT_IS_EQUAL
#define ASSERT_IS_EQUAL(a, b)                  \
    do {                                       \
        if ((a) != (b))                        \
            ASSERTION_FAILED(#a " != " #b);    \
        else                                   \
            ASSERTION_SUCCEEDED(#a " == " #b); \
    } while (0)
#endif /* ASSERT_IS_EQUAL */

/*
 * ASSERT_IS_APPROX_EQUAL - checks if a and b are approximately the same
 *
 * param a: First comparable variable
 * param b: Second comparable variable
 * param epsilon: Maximum allowed difference between a and b
 */
#ifndef ASSERT_IS_APPROX_EQUAL
#define ASSERT_IS_APPROX_EQUAL(a, b, epsilon)  \
    do {                                       \
        if (fabs((a) - (b)) > (epsilon))       \
            ASSERTION_FAILED(#a " !~ " #b);    \
        else                                   \
            ASSERTION_SUCCEEDED(#a " =~ " #b); \
    } while (0)
#endif /* ASSERT_IS_APPROX_EQUAL */

/*
 * ASSERT_IS_NOT_EQUAL - checks if a and b are not the same
 *
 * param a: First comparable variable
 * param b: Second comparable variable
 */
#ifndef ASSERT_IS_NOT_EQUAL
#define ASSERT_IS_NOT_EQUAL(a, b)              \
    do {                                       \
        if ((a) == (b))                        \
            ASSERTION_FAILED(#a " == " #b);    \
        else                                   \
            ASSERTION_SUCCEEDED(#a " != " #b); \
    } while (0)
#endif /* ASSERT_IS_NOT_EQUAL */

/*
 * ASSERT_IS_APPROX_NOT_EQUAL - checks if a and b are not approximately the same
 *
 * param a: First comparable variable
 * param b: Second comparable variable
 * param epsilon: Maximum allowed difference between a and b
 */
#ifndef ASSERT_IS_APPROX_NOT_EQUAL
#define ASSERT_IS_APPROX_NOT_EQUAL(a, b, epsilon) \
    do {                                          \
        if (fabs((a) - (b)) <= (epsilon))         \
            ASSERTION_FAILED(#a " =~ " #b);       \
        else                                      \
            ASSERTION_SUCCEEDED(#a " !~ " #b);    \
    } while (0)
#endif /* ASSERT_IS_APPROX_NOT_EQUAL */

/*
 * ASSERT_IS_GREATER_THAN - checks if a is greater than b
 *
 * param a: First comparable variable
 * param b: Second comparable variable
 */
#ifndef ASSERT_IS_GREATER_THAN
#define ASSERT_IS_GREATER_THAN(a, b)          \
    do {                                      \
        if ((a) <= (b))                       \
            ASSERTION_FAILED(#a " <= " #b);   \
        else                                  \
            ASSERTION_SUCCEEDED(#a " > " #b); \
    } while (0)
#endif /* ASSERT_IS_GREATER_THAN */

/*
 * ASSERT_IS_LESS_THAN - checks if a is less than b
 *
 * param a: First comparable variable
 * param b: Second comparable variable
 */
#ifndef ASSERT_IS_LESS_THAN
#define ASSERT_IS_LESS_THAN(a, b)             \
    do {                                      \
        if ((a) >= (b))                       \
            ASSERTION_FAILED(#a " >= " #b);   \
        else                                  \
            ASSERTION_SUCCEEDED(#a " < " #b); \
    } while (0)
#endif /* ASSERT_IS_LESS_THAN */

/*
 * ASSERT_IS_APPROX_GREATER_THAN - checks if a is approximately greater than b
 *
 * param a: First comparable variable
 * param b: Second comparable variable
 * param epsilon: Tolerance added to b for the comparison
 */
#ifndef ASSERT_IS_APPROX_GREATER_THAN
#define ASSERT_IS_APPROX_GREATER_THAN(a, b, epsilon) \
    do {                                             \
        if ((a) <= (b) + (epsilon))                  \
            ASSERTION_FAILED(#a " <=~ " #b);         \
        else                                         \
            ASSERTION_SUCCEEDED(#a " >~ " #b);       \
    } while (0)
#endif /* ASSERT_IS_APPROX_GREATER_THAN */

/*
 * ASSERT_IS_APPROX_LESS_THAN - checks if a is approximately less than b
 *
 * param a: First comparable variable
 * param b: Second comparable variable
 * param epsilon: Tolerance subtracted from b for the comparison
 */
#ifndef ASSERT_IS_APPROX_LESS_THAN
#define ASSERT_IS_APPROX_LESS_THAN(a, b, epsilon) \
    do {                                          \
        if ((a) >= (b) - (epsilon))               \
            ASSERTION_FAILED(#a " >=~ " #b);      \
        else                                      \
            ASSERTION_SUCCEEDED(#a " <~ " #b);    \
    } while (0)
#endif /* ASSERT_IS_APPROX_LESS_THAN */

/*
 * ASSERT_IS_GREATER_THAN_OR_EQUAL - checks if a is greater than or equal to b
 *
 * param a: First comparable variable
 * param b: Second comparable variable
 */
#ifndef ASSERT_IS_GREATER_THAN_OR_EQUAL
#define ASSERT_IS_GREATER_THAN_OR_EQUAL(a, b)  \
    do {                                       \
        if ((a) < (b))                         \
            ASSERTION_FAILED(#a " < " #b);     \
        else                                   \
            ASSERTION_SUCCEEDED(#a " >= " #b); \
    } while (0)
#endif /* ASSERT_IS_GREATER_THAN_OR_EQUAL */

/*
 * ASSERT_IS_LESS_THAN_OR_EQUAL - checks if a is less than or equal to b
 *
 * param a: First comparable variable
 * param b: Second comparable variable
 */
#ifndef ASSERT_IS_LESS_THAN_OR_EQUAL
#define ASSERT_IS_LESS_THAN_OR_EQUAL(a, b)     \
    do {                                       \
        if ((a) > (b))                         \
            ASSERTION_FAILED(#a " > " #b);     \
        else                                   \
            ASSERTION_SUCCEEDED(#a " <= " #b); \
    } while (0)
#endif /* ASSERT_IS_LESS_THAN_OR_EQUAL */

/*
 * ASSERT_IS_APPROX_GREATER_THAN_OR_EQUAL - checks if a is approximately greater than or equal to b
 *
 * param a: First comparable variable
 * param b: Second comparable variable
 * param epsilon: Tolerance subtracted from b for the comparison
 */
#ifndef ASSERT_IS_APPROX_GREATER_THAN_OR_EQUAL
#define ASSERT_IS_APPROX_GREATER_THAN_OR_EQUAL(a, b, epsilon) \
    do {                                                      \
        if ((a) < (b) - (epsilon))                            \
            ASSERTION_FAILED(#a " <~ " #b);                   \
        else                                                  \
            ASSERTION_SUCCEEDED(#a " >=~ " #b);               \
    } while (0)
#endif /* ASSERT_IS_APPROX_GREATER_THAN_OR_EQUAL */

/*
 * ASSERT_IS_APPROX_LESS_THAN_OR_EQUAL - checks if a is approximately less than or equal to b
 *
 * param a: First comparable variable
 * param b: Second comparable variable
 * param epsilon: Tolerance added to b for the comparison
 */
#ifndef ASSERT_IS_APPROX_LESS_THAN_OR_EQUAL
#define ASSERT_IS_APPROX_LESS_THAN_OR_EQUAL(a, b, epsilon) \
    do {                                                   \
        if ((a) > (b) + (epsilon))                         \
            ASSERTION_FAILED(#a " >~ " #b);                \
        else                                               \
            ASSERTION_SUCCEEDED(#a " <=~ " #b);            \
    } while (0)
#endif /* ASSERT_IS_APPROX_LESS_THAN_OR_EQUAL */

#endif
