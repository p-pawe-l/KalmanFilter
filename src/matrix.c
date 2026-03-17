#include "../include/matrix.h"
#include "../include/other.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

PUBLIC void init_matrix(matrix_t *m, const uint8_t n_rows, const uint8_t n_cols) {
        m->data = malloc(sizeof(int64_t) * n_rows * n_cols);
        m->n_rows = n_rows;
        m->n_cols = n_cols;
}

PUBLIC void destroy_matrix(matrix_t *m) { 
	free(m->data); 
}

PUBLIC int64_t at(const matrix_t *m, const uint8_t row, const uint8_t col) {
	if (row <= (m->n_rows - 1) && col <= (m->n_cols - 1))	
		return m->data[row * m->n_cols + col];
	exit(-1);
}

PUBLIC matrix_t negate(const matrix_t *m) {
        matrix_t new_matrix;
        init_matrix(&new_matrix, m->n_rows, m->n_cols);
        
        const uint16_t len = m->n_rows * m->n_cols;
        const int64_t* __restrict md = m->data;
        
        for ( uint16_t i = 0; i < len; ++i )
                new_matrix.data[i] = -md[i];
        
        return new_matrix;
}

PUBLIC matrix_t scale(const matrix_t *m, const int64_t factor) {
	matrix_t new_matrix;
	init_matrix(&new_matrix, m->n_rows, m->n_cols);
	
	const uint16_t len = m->n_rows * m->n_cols;
	const int64_t* __restrict md = m->data;
	
	for ( uint16_t i = 0; i < len; ++i ) {
		int64_t f_num  = (int64_t)
		(
			( (int128_t)md[i] * (int128_t)factor ) >> 32
		);
		new_matrix.data[i] = f_num;	
	}
	
	return new_matrix;
}


PUBLIC matrix_t add_matrices(const matrix_t *__restrict m1, const matrix_t *__restrict m2) {
        if (m1->n_rows == m2->n_rows && m1->n_cols == m2->n_cols) {
        	const uint16_t len = m1->n_rows * m1->n_cols;
        
		matrix_t new_matrix;
		init_matrix(&new_matrix, m1->n_rows, m1->n_cols);
		
		const int64_t* __restrict md1 = m1->data;
		const int64_t* __restrict md2 = m2->data;

		for ( uint16_t i = 0; i < len; ++i ) {
			new_matrix.data[i] = md1[i] + md2[i];
		}

                return new_matrix;
        }
        exit(-1);
}

PUBLIC matrix_t dot_product(const matrix_t * __restrict m1, const matrix_t * __restrict m2) {
	if (m1->n_cols == m2->n_rows) {
		matrix_t new_matrix;
		init_matrix(&new_matrix, m1->n_rows, m2->n_cols);
		
		const int64_t* __restrict md1 = m1->data;
		const int64_t* __restrict md2 = m2->data;
		
		for ( uint8_t row_m1 = 0; row_m1 < m1->n_rows; ++row_m1 ) {
			for ( uint8_t col_m2 = 0; col_m2 < m2->n_cols; ++col_m2 ) {
				int128_t temp_res = 0;
				
				for ( uint8_t col_m1 = 0; col_m1 < m1->n_cols; ++col_m1 ) {
					int128_t num = (int128_t)md1[row_m1 * m1->n_cols + col_m1] * 
						       (int128_t)md2[col_m1 * m2->n_cols + col_m2];	
					temp_res += num;	
				}
				temp_res = temp_res >> 32;
				new_matrix.data[row_m1 * new_matrix.n_cols + col_m2] = (int64_t)temp_res;
			}
		}
		
		return new_matrix;
		
	}
	exit(-1);
}

PUBLIC matrix_t transpose(const matrix_t* m) {
	matrix_t new_matrix;
	init_matrix(&new_matrix, m->n_cols, m->n_rows);
	
	const int64_t* __restrict md = m->data;
	
	for ( uint8_t row_m = 0; row_m < m->n_rows; ++row_m ) {
		
		for ( uint8_t col_m = 0; col_m < m->n_cols; ++row_m ) {
			new_matrix.data[col_m * new_matrix.n_cols + row_m] = md[row_m * m->n_cols + col_m];
		}
	} 

	return new_matrix;
}

PUBLIC int64_t det(const matrix_t* m) {
	const int64_t* __restrict md = m->data;
	
	/* 2x2 Matrix */
	if (m->n_rows == 2 && m->n_cols == 2) {
		int64_t ad = (int64_t)
		(
			( (int128_t)md[0] * (int128_t)md[3] ) >> 32
		);
		int64_t bc = (int64_t)
		(
			( (int128_t)md[1] * (int128_t)md[2] ) >> 32
		);
		
		return ad - bc;
	}
	/* 3x3 Matrix */
	else if (m->n_rows == 3 && m->n_cols == 3) {
		int64_t aei = (int64_t)
		(
			( ( ( (int128_t)md[0] * (int128_t)md[4] ) >> 32 ) * (int128_t)md[8] ) >> 32
		);
		int64_t bgf = (int64_t)
		(
			( ( ( (int128_t)md[1] * (int128_t)md[5] ) >> 32 ) * (int128_t)md[6] ) >> 32
		);
		int64_t cdh = (int64_t)
		(
			( ( ( (int128_t)md[2] * (int128_t)md[3] ) >> 32 ) * (int128_t)md[7] ) >> 32
		);
		
		int64_t ceg = (int64_t)
		(
			( ( ( (int128_t)md[2] * (int128_t)md[4] ) >> 32 ) * (int128_t)md[6] ) >> 32
		);
		int64_t bdi = (int64_t)
		(
			( ( ( (int128_t)md[1] * (int128_t)md[3] ) >> 32 ) * (int128_t)md[8] ) >> 32
		);
		int64_t afh = (int64_t)
		(
			( ( ( (int128_t)md[0] * (int128_t)md[5] ) >> 32 ) * (int128_t)md[7] ) >> 32
		);
	
		return (aei + bgf + cdh) - (ceg + bdi + afh);
	}
	/* other Matrix */
	else {
		printf("Unsupported matrix for calculating determinant!\n");
		exit(-1);
	}
	
}

PUBLIC matrix_t inverse(const matrix_t* m) {
	matrix_t new_matrix;
	
	if ( m->n_rows == m->n_cols) {
		int64_t m_det = det(m);
		if (m_det == 0LL) {
			printf("Cannot invert matrix where det=0!\n");
			exit(-1);
		}
		
		if ( m->n_rows == 2 ) {
			init_matrix(&new_matrix, 2, 2);
			new_matrix.data[0] = m->data[3];
			new_matrix.data[1] = -m->data[1];
			new_matrix.data[2] = -m->data[2];
			new_matrix.data[3] = m->data[0];
			
			int64_t div_factor;
			scale(&new_matrix, div_factor);
		}
	
	}
	else {
		printf("Cannot invert non-square matrixes!\n");
		exit(-1);
	}
	return new_matrix;

}








