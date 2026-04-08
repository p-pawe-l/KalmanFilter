#include "../include/fp_arithmetic.h"

#include <stdint.h>

#include "../include/assert_test.h"
#include "../include/other.h"

PRIVATE TEST void test_as_fp(void)
{
    ASSERT_IS_EQUAL(AS_FP(0), (FP_TYPE)0);
    ASSERT_IS_EQUAL(AS_FP(1), ((FP_TYPE)1 << FRACTIONAL_PART_SIZE));
    ASSERT_IS_EQUAL(AS_FP(3), ((FP_TYPE)3 << FRACTIONAL_PART_SIZE));
}

PRIVATE TEST void test_is_format_good(void)
{
    ASSERT_IS_EQUAL(IS_FORMAT_GOOD(0), TRUE);
    ASSERT_IS_EQUAL(IS_FORMAT_GOOD(INTEGER_PART_SIZE), TRUE);
    ASSERT_IS_EQUAL(IS_FORMAT_GOOD(FIXED_POINT_SIZE), TRUE);
    ASSERT_IS_EQUAL(IS_FORMAT_GOOD(FIXED_POINT_SIZE + 1), FALSE);
    ASSERT_IS_EQUAL(IS_FORMAT_GOOD(-1), FALSE);
}

PRIVATE TEST void test_fp_add(void)
{
    FP_TYPE x1 = AS_FP(2);
    FP_TYPE x2 = AS_FP(3);
    FP_TYPE result = fp_add(x1, x2);

    ASSERT_IS_EQUAL(result, AS_FP(5));
}

PRIVATE TEST void test_fp_substract(void)
{
    FP_TYPE x1 = AS_FP(7);
    FP_TYPE x2 = AS_FP(4);
    FP_TYPE result = fp_substract(x1, x2);

    ASSERT_IS_EQUAL(result, AS_FP(3));
}

PRIVATE TEST void test_fp_multiply(void)
{
    FP_TYPE x1 = AS_FP(3);
    FP_TYPE x2 = AS_FP(2);
    FP_TYPE result = fp_multiply(x1, x2);

    ASSERT_IS_EQUAL(result, AS_FP(6));
}

PRIVATE TEST void test_fp_multiply_fractional(void)
{
    FP_TYPE x1 = AS_FP(3) / 2;
    FP_TYPE x2 = AS_FP(2);
    FP_TYPE result = fp_multiply(x1, x2);

    ASSERT_IS_EQUAL(result, AS_FP(3));
}

PRIVATE TEST void test_fp_divide(void)
{
    FP_TYPE x1 = AS_FP(8);
    FP_TYPE x2 = AS_FP(2);
    FP_TYPE result = fp_divide(x1, x2);

    ASSERT_IS_EQUAL(result, AS_FP(4));
}

PRIVATE TEST void test_fp_divide_fractional(void)
{
    FP_TYPE x1 = AS_FP(3);
    FP_TYPE x2 = AS_FP(2);
    FP_TYPE result = fp_divide(x1, x2);

    ASSERT_IS_EQUAL(result, AS_FP(3) / 2);
}

PRIVATE TEST void test_fp_abs(void)
{
    ASSERT_IS_EQUAL(fp_abs(AS_FP(5)), AS_FP(5));
    ASSERT_IS_EQUAL(fp_abs(-AS_FP(5)), AS_FP(5));
    ASSERT_IS_EQUAL(fp_abs((FP_TYPE)0), (FP_TYPE)0);
}

PRIVATE TEST void test_fp_max(void)
{
    FP_TYPE x1 = AS_FP(2);
    FP_TYPE x2 = AS_FP(7);

    ASSERT_IS_EQUAL(fp_max(x1, x2), AS_FP(7));
    ASSERT_IS_EQUAL(fp_max(x2, x1), AS_FP(7));
}

PRIVATE TEST void test_fp_min(void)
{
    FP_TYPE x1 = AS_FP(2);
    FP_TYPE x2 = AS_FP(7);

    ASSERT_IS_EQUAL(fp_min(x1, x2), AS_FP(2));
    ASSERT_IS_EQUAL(fp_min(x2, x1), AS_FP(2));
}

PRIVATE TEST void test_fp_clip_inside_range(void)
{
    FP_TYPE value = AS_FP(5);
    FP_TYPE result = fp_clip(value, AS_FP(2), AS_FP(7));

    ASSERT_IS_EQUAL(result, AS_FP(5));
}

PRIVATE TEST void test_fp_clip_below_range(void)
{
    FP_TYPE value = AS_FP(1);
    FP_TYPE result = fp_clip(value, AS_FP(2), AS_FP(7));

    ASSERT_IS_EQUAL(result, AS_FP(2));
}

PRIVATE TEST void test_fp_clip_above_range(void)
{
    FP_TYPE value = AS_FP(9);
    FP_TYPE result = fp_clip(value, AS_FP(2), AS_FP(7));

    ASSERT_IS_EQUAL(result, AS_FP(7));
}

PRIVATE TEST void test_fp_pow_zero_exponent(void)
{
    FP_TYPE result = fp_pow(AS_FP(3), 0);

    ASSERT_IS_EQUAL(result, AS_FP(1));
}

PRIVATE TEST void test_fp_pow_integer(void)
{
    FP_TYPE result = fp_pow(AS_FP(2), 3);

    ASSERT_IS_EQUAL(result, AS_FP(8));
}

PRIVATE TEST void test_fp_pow_fractional_base(void)
{
    FP_TYPE result = fp_pow(AS_FP(3) / 2, 2);

    ASSERT_IS_EQUAL(result, AS_FP(9) / 4);
}

int main(void)
{
    test_as_fp();
    test_is_format_good();
    test_fp_add();
    test_fp_substract();
    test_fp_multiply();
    test_fp_multiply_fractional();
    test_fp_divide();
    test_fp_divide_fractional();
    test_fp_abs();
    test_fp_max();
    test_fp_min();
    test_fp_clip_inside_range();
    test_fp_clip_below_range();
    test_fp_clip_above_range();
    test_fp_pow_zero_exponent();
    test_fp_pow_integer();
    test_fp_pow_fractional_base();
}
