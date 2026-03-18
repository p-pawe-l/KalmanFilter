#include "../include/matrix.h"
#include "../include/other.h"
#include "../include/fixed_point/fp_arithmetic.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

PUBLIC mo_status_t destroy_matrix_LINEAR(linear_matrix_t *m) 
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
	if ( row < m->n_rows && col < m->n_cols )
	{	
		return (FP_TYPE_RESULT) { .result = m->data[row * m->n_cols + col], .status_code = SUCCESS };
	}
	else
	{
		return (FP_TYPE_RESULT) { .result = 0, .status_code = ERR_INDEX_OUT_OF_RANGE };
	}
}

PUBLIC LINEAR_MATRIX_RESULT negate(const linear_matrix_t *m) 
{
        struct linear_matrix new_Lmatrix;
        init_matrix(&new_Lmatrix, m->n_rows, m->n_cols);
        
        const uint16_t len = m->n_rows * m->n_cols;
        const FP_TYPE* __restrict md = m->data;
        
        for ( uint16_t i = 0; i < len; ++i )
	{
                new_Lmatrix.data[i] = -md[i];
	}        

        return new_matrix;
}


PUBLIC struct linear_matrix scale(const struct linear_matrix *m, const int64_t factor) 
{
	struct linear_matrix new_Lmatrix;
	init_matrix_LINEAR(&new_Lmatrix, m->n_rows, m->n_cols);
	
	const uint16_t len = m->n_rows * m->n_cols;
	const FP_TYPE* __restrict md = m->data;
	
	for ( uint16_t i = 0; i < len; ++i ) 
	{
		new_Lmatrix.data[i] = fp_multiply(md[i], factor);	
	}
	
	return new_matrix;
}


PUBLIC struct linear_matrix add_matrices(const struct linear_matrix *__restrict m1, const struct linear_matrix *__restrict m2) 
{
        if HAS_SAME_DIMS(m1, m2) 
	{
        	const uint16_t len = m1->n_rows * m1->n_cols;
        
		struct linear_matrix new_Lmatrix;
		init_matrix_LINEAR(&new_matrix, m1->n_rows, m1->n_cols);
		
		const FP_TYPE* __restrict md1 = m1->data;
		const FP_TYPE* __restrict md2 = m2->data;
		
		for ( uint16_t i = 0; i < len; ++i )
		{
			new_Lmatrix.data[i] = fp_add(md1[i], md2[i]);
		}

                return new_Lmatrix;
        } 
	else
        {
		log_error("add_matrices", "Matrices must to have the same dimensions!");
		exit(OPERATION_FAILURE);
	}
}

PUBLIC struct linear_matrix dot_product(const struct linear_matrix *__restrict m1, const struct linear_matrix *__restrict m2) 
{
	if CAN_MULTIPLY(m1, m2) 
	{
		struct linear_matrix new_Lmatrix;
		init_matrix(&new_Lmatrix, m1->n_rows, m2->n_cols);
		
		const FP_TYPE* __restrict md1 = m1->data;
		const FP_TYPE* __restrict md2 = m2->data;
		
		for ( uint8_t row_m1 = 0; row_m1 < m1->n_rows; ++row_m1 ) 
		{
			for ( uint8_t col_m2 = 0; col_m2 < m2->n_cols; ++col_m2 ) 
			{
				FP_TYPE temp_res = 0;
				for ( uint8_t col_m1 = 0; col_m1 < m1->n_cols; ++col_m1 ) 
				{
					FP_TYPE num1 = md1[row_m1 * m1->n_cols + col_m1]; 
					FP_TYPE num2 = md2[col_m1 * m2->n_cols + col_m2];	
					temp_res += fp_multiply(num1, num2);	
				}
				new_Lmatrix.data[row_m1 * new_Lmatrix.n_cols + col_m2] = temp_res;
			}
		}
		
		return new_matrix;
		
	}
	else 
	{
		log_error("dot_product", "Matrix-1 need to have the same number of columns, as Matrix-2 rows!");
		exit(OPERATION_FAILED);
	}
}

PUBLIC struct linear_matrix transpose(const struct linear_matrix *m) 
{
	struct linear_matrix new_Lmatrix;
	init_matrix(&new_Lmatrix, m->n_cols, m->n_rows);
	
	const FP_TYPE* __restrict md = m->data;
	
	for ( uint8_t row_m = 0; row_m < m->n_rows; ++row_m ) 
	{	
		for ( uint8_t col_m = 0; col_m < m->n_cols; ++col_m ) 
		{
			new_Lmatrix.data[col_m * new_matrix.n_cols + row_m] = md[row_m * m->n_cols + col_m];
		}
	} 

	return new_matrix;
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

PUBLIC FP_TYPE det(const struct linear_matrix *m) {
	const FP_TYPE* __restrict md = m->data;
	
	if (m->n_rows == 2 && m->n_cols == 2) 
	{
		FP_TYPE ad = fp_multiply(md[0], md[3]);
		FP_TYPE bc = fp_multiply(md[1], md[2]);
		
		return fp_substract(ad, db);
	}
	else if (m->n_rows == 3 && m->n_cols == 3) 
	{
		FP_TYPE aei = for_det_calc_help(md[0], md[4], md[8]);
		FP_TYPE bgf = for_det_calc_help(md[0], md[4], md[6]);
		FP_TYPE cdh = for_det_calc_help(md[2], md[3], md[7]);
		
		FP_TYPE ceg = for_det_calc_help(md[2], md[4], md[6]);
		FP_TYPE bdi = for_det_calc_help(md[1], md[3], md[8]);	
		FP_TYPE afh = for_det_calc_help(md[0], md[5], md[7]);	
		
		return (aei + bgf + cdh) - (ceg + bdi + afh);
	}
	else 
	{
		log_error("det", "Unsupported matrix provided! - Only 2x2 and 3x3 ;//");
		exit(OPERATION_FAILURE);
	}
	
}

PRIVATE FP_TYPE cofactor_calc_help(const FP_TYPE x1, const FP_TYPE x2, const FP_TYPE x3, const FP_TYPE x4)
{
	return fp_substract( fp_multiply( x1, x2 ) , fp_multiply( x3, x4 ) );
}

PUBLIC matrix_t inverse(const struct linear_matrix *m) {
	struct linear_matrix new_Lmatrix;
	
	const FP_TYPE* __restrict md = m->data;
	FP_TYPE determinant = det(m);	

	if ( IS_SQUARE_MATRIX(m) && determimant != AS_FP(0LL) ) 
	{
		FP_TYPE div_factor = fp_divide(AS_FP(1LL), determinant);
		if ( m->n_rows == 2 ) 
		{
			init_matrix(&new_Lmatrix, 2, 2);
			
			new_matrix.data[0] = md[3];
			new_matrix.data[1] = -md[1];
			new_matrix.data[2] = -md[2];
			new_matrix.data[3] = md[0];
			
			new_Lmatrix = scale(&new_Lmatrix, div_factor);
		}
		else if (m->n_rows == 3) 
		{
			init_matrix(&new_Lmatrix, 3, 3);
			
			FP_TYPE c00 = cofactor_calc_help(md[4], md[8], md[5], md[7]);
			FP_TYPE c10 = -cofactor_calc_help(md[1], md[8], md[2], md[7]);
			FP_TYPE c20 = cofactor_calc_help(md[1], md[5], md[2], md[4]); 			
		
		}
	
	}
	else 
	{
		log_error("inverse", "Cannot inverse non-square matrixes or with determinant=0");
		exit(OPERATION_FAILURE);
	}
	return new_matrix;

}








