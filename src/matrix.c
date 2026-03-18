#include "../include/matrix.h"
#include "../include/other.h"
#include "../include/fixed_point/fp_arithmetic.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LM_SUCCESS(lm)          ( LINEAR_MATRIX_RESULT ) { .result = lm, .status_code = SUCCESS }
#define LM_ERROR(lm, ec)        ( LINEAR_MATRIX_RESULT ) { .result = lm, .status_code = ec }
#define FP_SUCCESS(fp)          ( FP_TYPE_RESULT ) { .result = fp, .status_code = SUCCESS }
#define FP_ERROR(ec)            ( FP_TYPE_RESULT ) { .result = 0, .status_code = ec }

#define LM_VALIDATE_ERR_C(m, ec)                                                                                \
        if ( ec != SUCCESS )                                                                                    \
                return ( LINEAR_MATRIX_RESULT ) { .result =  m, .status_code = ec}                              \
                
#define FP_VALIDATE_ERR_C(ec)                                                                                   \
        if ( ec != SUCCESS )                                                                                    \
                return ( FP_TYPE_RESULT ) { .result = 0, .status_code = ec}                                     \

#define VALIDATE_M_DATA_FP_TYPE(m)                                                                              \
                if ( !m->data )                                                                                 \
                        return ( FP_TYPE_RESULT ) { .result = 0, .status_code = ERR_NULL_DATA_POINTER }         \

#define VALIDATE_M_DATA_LM_TYPE(m, nm)                                                                          \
                if ( !m->data )                                                                                 \
                        return ( LINEAR_MATRIX_RESULT ) { .result = nm, .status_code = ERR_NULL_DATA_POINTER }  \

PUBLIC mo_status_t init_matrix(linear_matrix_t *m, const uint32_t n_rows, const uint32_t n_cols) 
{
	if (n_rows == 0 || n_cols == 0)
	{
		return ERR_INVALID_PARAMS;
	}
	m->data = (FP_TYPE*)malloc(sizeof(FP_TYPE) * n_rows * n_cols);
	if (!m->data)
	{
		return ERR_MALLOC_FAILED;
	}
	m->n_rows = n_rows;
	m->n_cols = n_cols;
	return SUCCESS;
	
}

PUBLIC mo_status_t destroy_matrix(linear_matrix_t *m) 
{ 
	if (m->data)
	{
		free(m->data);
		memset(m, 0, sizeof(linear_matrix_t));
		return SUCCESS;
	}
	else 
	{
		return ERR_MATRIX_DESTROY;
	}	
}

PUBLIC FP_TYPE_RESULT at(const linear_matrix_t *m, const uint32_t row, const uint32_t col) 
{
        VALIDATE_M_DATA_FP_TYPE(m);
	if ( row < m->n_rows && col < m->n_cols )
	{	
		return FP_SUCCESS(m->data[row * m->n_cols + col]);
	}
	else
        {
                return FP_ERROR(ERR_INDEX_OUT_OF_RANGE);
        }
	
}

PUBLIC LINEAR_MATRIX_RESULT negate(const linear_matrix_t *m) 
{
        linear_matrix_t new_matrix;
	mo_status_t result = init_matrix(&new_matrix, m->n_rows, m->n_cols);
        LM_VALIDATE_ERR_C(new_matrix, result);

        const uint64_t len = m->n_rows * m->n_cols;

        VALIDATE_M_DATA_LM_TYPE(m, new_matrix);
        const FP_TYPE* __restrict md = m->data;
        
        for ( uint64_t i = 0; i < len; ++i )
	{
                new_matrix.data[i] = -md[i];
	}        

        return LM_SUCCESS(new_matrix);
}

PUBLIC LINEAR_MATRIX_RESULT scale(const linear_matrix_t *m, const int64_t factor) 
{
	struct linear_matrix new_matrix;
	mo_status_t result = init_matrix(&new_matrix, m->n_rows, m->n_cols);
	LM_VALIDATE_ERR_C(new_matrix, result);

	const uint64_t len = m->n_rows * m->n_cols;
        VALIDATE_M_DATA_LM_TYPE(m, new_matrix);
	const FP_TYPE* __restrict md = m->data;
	
	for ( uint64_t i = 0; i < len; ++i ) 
	{
		new_matrix.data[i] = fp_multiply(md[i], factor);	
	}
	
	return LM_SUCCESS(new_matrix);
}

PUBLIC LINEAR_MATRIX_RESULT add_matrices(const linear_matrix_t *__restrict m1, const linear_matrix_t *__restrict m2) 
{
	linear_matrix_t new_matrix;
        if HAS_SAME_DIMS(m1, m2) 
	{
		mo_status_t result = init_matrix(&new_matrix, m1->n_rows, m1->n_cols);
		LM_VALIDATE_ERR_C(new_matrix, result);

        	const uint64_t len = m1->n_rows * m1->n_cols;

                VALIDATE_M_DATA_LM_TYPE(m1, new_matrix);
		const FP_TYPE* __restrict md1 = m1->data;

                VALIDATE_M_DATA_LM_TYPE(m2, new_matrix);
		const FP_TYPE* __restrict md2 = m2->data;
		
		for ( uint64_t i = 0; i < len; ++i )
		{
			new_matrix.data[i] = fp_add(md1[i], md2[i]);
		}

                return LM_SUCCESS(new_matrix);
        } 
        else
        {
		return LM_ERROR(new_matrix, ERR_DIMENSION_MISMATCH);
	}
}

PUBLIC LINEAR_MATRIX_RESULT dot_product(const linear_matrix_t *__restrict m1, const linear_matrix_t *__restrict m2) 
{
	linear_matrix_t new_matrix;
	if CAN_MULTIPLY(m1, m2) 
	{
		mo_status_t result = init_matrix(&new_matrix, m1->n_rows, m2->n_cols);
		LM_VALIDATE_ERR_C(new_matrix, result);

                VALIDATE_M_DATA_LM_TYPE(m1, new_matrix);
		const FP_TYPE* __restrict md1 = m1->data;

                VALIDATE_M_DATA_LM_TYPE(m2, new_matrix);
		const FP_TYPE* __restrict md2 = m2->data;
		
		for ( uint32_t row_m1 = 0; row_m1 < m1->n_rows; ++row_m1 ) 
		{
			for ( uint32_t col_m2 = 0; col_m2 < m2->n_cols; ++col_m2 ) 
			{
				FP_TYPE temp_res = 0;
				for ( uint32_t col_m1 = 0; col_m1 < m1->n_cols; ++col_m1 ) 
				{
					FP_TYPE num1 = md1[row_m1 * m1->n_cols + col_m1]; 
					FP_TYPE num2 = md2[col_m1 * m2->n_cols + col_m2];	
					temp_res += fp_multiply(num1, num2);	
				}
				new_matrix.data[row_m1 * new_matrix.n_cols + col_m2] = temp_res;
			}
		}
		
		return LM_SUCCESS(new_matrix);
	}
	else 
	{
		return LM_ERROR(new_matrix, ERR_DIMENSION_MISMATCH);
	}
}

PUBLIC LINEAR_MATRIX_RESULT transpose(const linear_matrix_t *m) 
{
	linear_matrix_t new_matrix;
	mo_status_t result = init_matrix(&new_matrix, m->n_cols, m->n_rows);
	LM_VALIDATE_ERR_C(new_matrix, result);

        VALIDATE_M_DATA_LM_TYPE(m, new_matrix);
	const FP_TYPE* __restrict md = m->data;
	
	for ( uint32_t row_m = 0; row_m < m->n_rows; ++row_m ) 
	{	
		for ( uint32_t col_m = 0; col_m < m->n_cols; ++col_m ) 
		{
			new_matrix.data[col_m * new_matrix.n_cols + row_m] = md[row_m * m->n_cols + col_m];
		}
	} 

	return LM_SUCCESS(new_matrix);
}

/*
 * Helper function for calculating part of the determinant of the 3x3 matrix.
 * 
 * Example matrix:
 * a   b   c
 * d   e   f
 * g   h   i
 *
 * As we know our determinant is aei + bfg + cdh - ceg - bdi - afh.
 * This function is useful to calculate this number from diagonal numbers on each diagonal
 * param x1 (int64_t/int32_t) - first number from diagonal   | 64-bit/32-bit fixed_point format
 * param x2 (int64_t/int32_t) - second number from diagonal  | 64-bit/32-bit fixed_point format
 * param x3 (int64_t/int32_t) - third number from diagonal   | 64-bit/32-bit fixed-point format
 *
 * return   (int64_t/int32_t) - x1 * x2 * x3		     | 64-bit/32-bit fixed-point format		
 * */
PRIVATE FP_TYPE for_det_calc_help(const FP_TYPE x1, const FP_TYPE x2, const FP_TYPE x3)
{
	return fp_multiply( fp_multiply( x1, x2 ), x3 );
}

PUBLIC FP_TYPE_RESULT det(const linear_matrix_t *m) {
        VALIDATE_M_DATA_FP_TYPE(m);
        const FP_TYPE* __restrict md = m->data;
	
	if (m->n_rows == 2 && m->n_cols == 2) 
	{
		FP_TYPE ad = fp_multiply(md[0], md[3]);
		FP_TYPE bc = fp_multiply(md[1], md[2]);
		
		return FP_SUCCESS(fp_substract(ad, bc));
	}
	else if (m->n_rows == 3 && m->n_cols == 3) 
	{
		FP_TYPE aei = for_det_calc_help(md[0], md[4], md[8]);
		FP_TYPE bgf = for_det_calc_help(md[0], md[4], md[6]);
		FP_TYPE cdh = for_det_calc_help(md[2], md[3], md[7]);
		
		FP_TYPE ceg = for_det_calc_help(md[2], md[4], md[6]);
		FP_TYPE bdi = for_det_calc_help(md[1], md[3], md[8]);	
		FP_TYPE afh = for_det_calc_help(md[0], md[5], md[7]);	
		
		return FP_SUCCESS((aei + bgf + cdh) - (ceg + bdi + afh));
	}
	else 
	{
		return FP_ERROR(ERR_UNSUPPORTED_TYPE);
	}
	
}

PRIVATE FP_TYPE cofactor_calc_help(const FP_TYPE x1, const FP_TYPE x2, const FP_TYPE x3, const FP_TYPE x4)
{
	return fp_substract( fp_multiply( x1, x2 ) , fp_multiply( x3, x4 ) );
}

PUBLIC LINEAR_MATRIX_RESULT inverse(const linear_matrix_t *m) {
	linear_matrix_t new_matrix;
	
        VALIDATE_M_DATA_LM_TYPE(m, new_matrix);
	const FP_TYPE* __restrict md = m->data;

	FP_TYPE_RESULT determinant_res = det(m);	
        LM_VALIDATE_ERR_C(new_matrix, determinant_res.status_code);

	if ( IS_SQUARE_MATRIX(m) && determinant_res.result != AS_FP(0LL) ) 
	{
		FP_TYPE div_factor = fp_divide(AS_FP(1LL), determinant_res.result);
		if ( m->n_rows == 2 ) 
		{
			mo_status_t result = init_matrix(&new_matrix, 2, 2);
			LM_VALIDATE_ERR_C(new_matrix, result);

			new_matrix.data[0] = md[3];
			new_matrix.data[1] = -md[1];
			new_matrix.data[2] = -md[2];
			new_matrix.data[3] = md[0];
			
			LINEAR_MATRIX_RESULT scaling_result = scale(&new_matrix, div_factor);
                        LM_VALIDATE_ERR_C(new_matrix, scaling_result.status_code);
                        new_matrix = scaling_result.result;
		}
		else if (m->n_rows == 3) 
		{
			init_matrix(&new_matrix, 3, 3);
			
			FP_TYPE c00 = cofactor_calc_help(md[4], md[8], md[5], md[7]);
			FP_TYPE c10 = -cofactor_calc_help(md[1], md[8], md[2], md[7]);
			FP_TYPE c20 = cofactor_calc_help(md[1], md[5], md[2], md[4]); 			
                        // TODO
		}
	
	}
	else 
	{
                return LM_ERROR(new_matrix, ERR_SINGULAR_MATRIX || ERR_DIMENSION_MISMATCH);
	}
	return LM_SUCCESS(new_matrix);

}