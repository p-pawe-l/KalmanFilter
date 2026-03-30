#ifndef FP_ARITHMETIC_H
#define FP_ARITHMETIC_H

/*
 * Copyright (c) 2026 Paweł Kozikowski
 *
 * This file is part of a Kalman filter implementation in C.
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for full license information.
 */

/*
 * Header file that contains fixed-point operations for 64-bit/32-bit numbers
 * fp_add - Add operation for two 64-bit/32-bit numbers in fixed-point
 * fp_substract - Substract operation for two 64-bit/32-bit numbers in
 * fixed-point fp_multiply - Multiplication operation for two 64-bit/32-bit
 * numbers in fixed-point fp_divide - Divide opeeration for two 64-bit/32-bit
 * numbers in fixed-point
 * */

#include <stdint.h>

#include "other.h"

/*
 * If our machine is supporting 128-bit integer types our fixed-point size can
 * be up to 64-bit. If not, we are only allowed to use up to 32-bit format.
 * Standard format for machines supporting 128-bit integer
 * Q32.32 - 64bit number is divide in half (32bit each) for integer part and
 * fractional part Standard format for machine not-supporting 128-bit integer
 * Q16.16 - 32bit number is divided in half (16 bit each) for integer part and
 * fractional part
 * */
#if defined(__SIZEOF_INT128__)

#define EXTENDED_FP_TYPE __int128
#define FP_TYPE int64_t
#define FIXED_POINT_SIZE 64

#ifndef INTEGER_PART_SIZE

#define INTEGER_PART_SIZE 32

#endif

#else

#define EXTENDED_FP_TYPE int64_t
#define FP_TYPE int32_t
#define FIXED_POINT_SIZE 32

#ifndef INTEGER_PART_SIZE

#define INTEGER_PART_SIZE 16

#endif

#endif

#ifndef FRACTIONAL_PART_SIZE
#define FRACTIONAL_PART_SIZE (FIXED_POINT_SIZE - INTEGER_PART_SIZE)
#endif /* FRACTIONAL_PART_SIZE */

#ifndef AS_FP
#define AS_FP(x) ((FP_TYPE)x << FRACTIONAL_PART_SIZE)
#endif /* AS_FP */

#ifndef IS_FORMAT_GOOD
#define IS_FORMAT_GOOD(i) (!((i) > FIXED_POINT_SIZE) && !((i) < 0))
#endif /* IS_FORMAT_GOOD */

/*
 * Add operation
 * Param x1 (int64_t/int32_t) - first 64-bit fixed-point format number
 * Param x2 (int64_t/int32_t) - second 64-bit fixed-point format number
 * Returns  (int64_t/int32_t) - x1 + x2 in 64-bit fixed-point format
 * */
#ifndef fp_add
#define fp_add(x1, x2) (x1 + x2)
#endif /* fp_add */

/*
 * Substract operation
 * Param x1 (int64_t/int32_t) - first 64-bit fixed-point format number
 * Param x2 (int64_t/int32_t) - second 64-bit fixed-point format number
 * Returns  (int64_t/int32_t) - x1 - x2 in 64-bit fixed-point format
 * */
#ifndef fp_substract
#define fp_substract(x1, x2) (x1 - x2)
#endif /* fp_substract */

/*
 * Substract operation
 * Param x1 (int64_t/int32_t) - first 64-bit/32-bit fixed-point format number
 * Param x2 (int64_t/int32_t) - second 64-bit/32-bit fixed-point format number
 * Returns  (int64_t/int32_t) - x1 * x2 in 64-bit/32-bit fixed-point format
 * */
#ifndef fp_multiply
#define fp_multiply(x1, x2) (((EXTENDED_FP_TYPE)x1 * (EXTENDED_FP_TYPE)x2) >> FRACTIONAL_PART_SIZE)
#endif /* fp_multiply */

/*
 * Substract operation
 * Param x1 (int64_t/int32_t) - first 64-bit/32-bit fixed-point format number
 * Param x2 (int64_t/int32_t) - second 64-bit/32-bit fixed-point format number
 * Returns  (int64_t/int32_t) - x1 / x2 in 64-bit/32-bit fixed-point format
 * */
#ifndef fp_divide
#define fp_divide(x1, x2) (((EXTENDED_FP_TYPE)x1 << FRACTIONAL_PART_SIZE) / (EXTENDED_FP_TYPE)x2)
#endif /* fp_divide */

/*
 * Absolute value operation
 * Param x1 (int64_t/int32_t) - 64-bit/32-bit fixed-point format number
 * Returns  (int64_t/int32_t) - absolute value of x1 in 64-bit/32-bit fixed-point format
 * */
#ifndef fp_abs
#define fp_abs(x1) ((x1) > 0 ? (x1) : -(x1))
#endif /* fp_abs */

/*
 * Max operation
 * Param x1 (int64_t/int32_t) - first 64-bit/32-bit fixed-point format number
 * Param x2 (int64_t/int32_t) - second 64-bit/32-bit fixed-point format number
 * Returns  (int64_t/int32_t) - greater of x1 and x2 in 64-bit/32-bit fixed-point format
 * */
#ifndef fp_max
#define fp_max(x1, x2) ((x1) > (x2) ? (x1) : (x2))
#endif /* fp_max */

/*
 * Min operation
 * Param x1 (int64_t/int32_t) - first 64-bit/32-bit fixed-point format number
 * Param x2 (int64_t/int32_t) - second 64-bit/32-bit fixed-point format number
 * Returns  (int64_t/int32_t) - lesser of x1 and x2 in 64-bit/32-bit fixed-point format
 * */
#ifndef fp_min
#define fp_min(x1, x2) ((x1) < (x2) ? (x1) : (x2))
#endif /* fp_min */

/*
 * Clip operation
 * Param x   (int64_t/int32_t) - 64-bit/32-bit fixed-point format number
 * Param min (int64_t/int32_t) - lower bound in 64-bit/32-bit fixed-point format
 * Param max (int64_t/int32_t) - upper bound in 64-bit/32-bit fixed-point format
 * Returns   (int64_t/int32_t) - x clamped to [min, max] in 64-bit/32-bit fixed-point format
 * */
#ifndef fp_clip
#define fp_clip(x, min, max) (fp_min(fp_max((x), (min)), (max)))
#endif /* fp_clip */

/*
 * Power operation
 * Param x (int64_t/int32_t) - base in 64-bit/32-bit fixed-point format
 * Param n (int)             - non-negative integer exponent
 * Returns (int64_t/int32_t) - x raised to the power of n in 64-bit/32-bit fixed-point format
 * */
static INLINE FP_TYPE fp_pow(FP_TYPE x, int n)
{
    FP_TYPE result = AS_FP(1);
    for (int i = 0; i < n; ++i) {
        result = fp_multiply(result, x);
    }
    return result;
}

#endif
