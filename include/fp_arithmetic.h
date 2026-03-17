#ifndef FP_ARITHMETIC_H
#define FP_ARITHMETIC_H

/*
 * Header file that contains fixed-point operations for 64-bit/32-bit numbers
 * fp_add - Add operation for two 64-bit/32-bit numbers in fixed-point
 * fp_substract - Substract operation for two 64-bit/32-bit numbers in fixed-point
 * fp_multiply - Multiplication operation for two 64-bit/32-bit numbers in fixed-point
 * fp_divide - Divide opeeration for two 64-bit/32-bit numbers in fixed-point
 * */


#include <stdint.h>


/*
 * If our machine is supporting 128-bit integer types our fixed-point size can 
 * be up to 64-bit. If not, we are only allowed to use up to 32-bit format.
 * Standard format for machines supporting 128-bit integer
 * Q32.32 - 64bit number is divide in half (32bit each) for integer part and fractional part
 * Standard format for machine not-supporting 128-bit integer
 * Q16.16 - 32bit number is divided in half (16 bit each) for integer part and fractional part
 * */
#if defined(__SIZEOF_INT128__)
	#define EXTENDED_FP_TYPE 	__int128
	#define FP_TYPE 		int64_t
	#define FIXED_POINT_SIZE 	64

        #ifndef INTEGER_PART_SIZE
                #define INTEGER_PART_SIZE 32
        #endif
#else
	#define EXTENDED_FP_TYPE 	int64_t
	#define FP_TYPE			int32_t
	#define FIXED_POINT_SIZE 	32

        #ifndef INTEGER_PART_SIZE
                #define INTEGER_PART_SIZE 16
        #endif
#endif 

#define FRACTIONAL_PART_SIZE (FIXED_POINT_SIZE - INTEGER_PART_SIZE)
#define IS_FORMAT_GOOD(i) ( !( (i) > FIXED_POINT_SIZE ) && !( (i) < 0 ) )

/*
 * Add operation
 * Param x1 (int64_t/int32_t) - first 64-bit fixed-point format number
 * Param x2 (int64_t/int32_t) - second 64-bit fixed-point format number
 * Returns  (int64_t/int32_t) - x1 + x2 in 64-bit fixed-point format
 * */
FP_TYPE fp_add(const FP_TYPE x1, const FP_TYPE x2);

/*
 * Substract operation
 * Param x1 (int64_t/int32_t) - first 64-bit fixed-point format number
 * Param x2 (int64_t/int32_t) - second 64-bit fixed-point format number
 * Returns  (int64_t/int32_t) - x1 - x2 in 64-bit fixed-point format
 * */
FP_TYPE fp_substract(const FP_TYPE x1, const FP_TYPE x2);

/*
 * Substract operation
 * Param x1 (int64_t/int32_t) - first 64-bit/32-bit fixed-point format number
 * Param x2 (int64_t/int32_t) - second 64-bit/32-bit fixed-point format number
 * Returns  (int64_t/int32_t) - x1 * x2 in 64-bit/32-bit fixed-point format
 * */
FP_TYPE fp_multiply(const FP_TYPE x1, const FP_TYPE x2);

/*
 * Substract operation
 * Param x1 (int64_t/int32_t) - first 64-bit/32-bit fixed-point format number
 * Param x2 (int64_t/int32_t) - second 64-bit/32-bit fixed-point format number
 * Returns  (int64_t/int32_t) - x1 / x2 in 64-bit/32-bit fixed-point format
 * */
FP_TYPE fp_divide(const FP_TYPE x1, const FP_TYPE x2); 


#endif
