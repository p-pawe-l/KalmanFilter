#include "../../include/fixed_point/fp_arithmetic.h"
#include "../../include/other.h"

PUBLIC FP_TYPE fp_add(const FP_TYPE x1, const FP_TYPE x2) 
{
        return x1 + x2;        
}

PUBLIC FP_TYPE fp_substract(const FP_TYPE x1, const FP_TYPE x2) 
{
        return x1 - x2;
}

PUBLIC FP_TYPE fp_multiply(const FP_TYPE x1, const FP_TYPE x2)
{
        return 
        (
                ( (EXTENDED_FP_TYPE)x1 * (EXTENDED_FP_TYPE)x2 ) >> FRACTIONAL_PART_SIZE
        );
}

PUBLIC FP_TYPE fp_divide(const FP_TYPE x1, const FP_TYPE x2)
{
        return 
        (
                ( ( (EXTENDED_FP_TYPE)x1 << FRACTIONAL_PART_SIZE ) / (EXTENDED_FP_TYPE)x2 )
        );
}
