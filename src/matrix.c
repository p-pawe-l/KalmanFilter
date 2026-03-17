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


PUBLIC matrix_t add_matrices(const matrix_t *__restrict m1, const matrix_t *__restrict m2) {
        if (m1->n_rows == m2->n_rows && m1->n_cols == m2->n_cols) {
        	const uint16_t len = m1->n_rows * m1->n_cols;
        
		matrix_t new_matrix;
		init_matrix(&new_matrix, m1->n_rows, m1->n_cols);
		
		const int64_t* __restrict md1 = m1->data;
		const int64_t* __restrict md2 = m2->data;

		for ( uint16_t i = 0; i < len; ++i )
			new_matrix.data[i] = md1[i] + md2[i];

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
				printf("Temp res: %ld\n", (int64_t)temp_res);
				new_matrix.data[row_m1 * new_matrix.n_cols + col_m2] = (int64_t)temp_res;
			}
		}
		
		return new_matrix;
		
	}
	exit(-1);
}

PUBLIC matrix_t transpose(const matrix_t* m) {
	matrix_t new_matrix;
	init_matrix(&new_matrix, m->n_cols, m->m_rows);
	
	const int64_t* __restrict md = m->data;
	
	for ( uint8_t row_m = 0; row_m < m->n_rows; ++row_m ) {
		
		for ( uint8_t col_m = 0; col_m < m->n_cols; ++row_m ) {
			new_matrix.data[col_m * new_matrix.n_cols + row_m] = m->data[row_m * m->n_cols + col_m];
		}
	} 

	return new_matrix;
}

PUBLIC int64_t det(const matrix_t* m) {
	// Hell on earth

}

PUBLIC matrix_t inverse(const matrix_t* m) {
	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣠⣄⢄⡤⠤⣤⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⡤⠖⠚⠉⠉⠀⠀⠄⠀⠀⡠⢀⠀⢀⡀⠉⠉⠑⠒⠢⢄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠤⠚⠉⠀⠀⢀⣠⣼⣾⣿⣶⣶⣿⣿⣿⣿⣿⣿⣿⣷⣤⡀⠐⣤⠀⠀⠙⠢⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡤⠋⠁⠀⢀⣠⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣮⢹⣿⣷⣶⣤⡀⠙⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠉⠀⢀⣴⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣀⠙⢆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠎⠀⣠⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡀⢣⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡏⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⢳⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡾⢨⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡈⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡏⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣻⣯⣿⣿⣿⡿⠿⣿⢻⢞⣻⣳⣽⣮⣷⣼⣭⣭⣭⣭⣽⣯⣿⡿⠿⠿⢿⡼⠦⡀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⢯⣽⣵⡾⣷⣻⣟⡿⠿⠛⢛⣛⣛⣩⣭⣽⣷⣶⣶⣿⣿⣿⣿⣿⣿⣿⣦⡌⠢⡄⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣯⣷⡿⠿⣟⣻⣫⣭⣥⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⠈⣆⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⣛⣿⣯⣵⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣼⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⡎⣿⣿⣿⣿⣿⣿⣟⣿⣷⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠫⠿⢿⣿⣿⣿⣿⣿⣼⣍⣹⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠄⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢣⣽⡿⢿⣽⣿⣿⣿⣿⣿⣵⣿⣏⢻⣿⣿⣟⣿⣿⣿⣿⣿⣿⣶⣦⣿⣿⣿⡙⣿⣿⠿⣹⣿⣷⡘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⣸⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠏⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡷⠏⢭⣍⣤⣾⣿⣿⣿⡟⣿⣿⣿⣿⣶⡉⠄⠠⠚⣛⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣶⠁⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡟⣹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣹⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣹⣻⣿⣿⣿⣿⣷⣮⣕⡦⣝⢫⠟⡽⣿⣿⣿⣿⣿⣿⣿⣿⣿⢄⠇⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣿⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣯⣿⣿⣿⣿⣿⣽⢿⣿⣿⣮⣻⣵⣿⣿⣿⣿⡟⣿⡨⣿⡏⢹⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢏⡟⣹⣿⣿⣿⡀⢀⡹⣿⣿⣿⢭⣛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠋⡇⢻⡇⢸⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣏⠾⣴⣼⣿⣿⣿⣿⣾⣿⣿⣿⣿⣶⡽⢎⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠁⠀⣧⣸⡇⣼⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣆⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣽⣻⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⢮⡽⣿⣿⣿⣿⣿⣿⡿⠃⠀⠀⢿⢼⣇⡏⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⢿⠋⣿⢯⣹⣋⣿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣛⣟⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣩⠟⠁⠀⠀⠀⢸⡾⡿⡇⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡼⢨⣼⠛⠉⠀⠀⠀⠘⣟⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣏⣸⠁⠀⠀⠀⠀⠀⢸⣇⣧⡷⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠿⠃⠀⠀⠀⠀⠀⠀⠘⡾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣿⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢻⡃⠀⠀⠀⠀⠀⠀⠀⣿⢿⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣷⣼⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠛⠳⣄⠀⠀⠀⠀⠀⢸⣿⢸⡆⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡠⠛⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣆⡉⠑⠦⡀⠀⠀⡏⣿⣴⠇⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠋⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣿⡀⣤⡬⣷⣄⡈⠉⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡾⠁⣆⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⠈⠎⢷⣀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⡿⠤⠖⣿⣿⣿⢋⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣤⣥⣌⡇⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠤⠞⢁⣌⣄⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣯⡟⡵⢯⣷⣻⣾⣿⣿⣻⣽⣿⣿⣿⣿⣿⣿⣱⣿⢿⣿⣾⣟⠋⠙⠦⢤⣀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡤⠞⠃⢠⣴⡿⠁⣲⡿⢡⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣻⣶⣿⣿⣿⣽⣳⣿⣿⣿⣿⣿⣿⣿⣿⣷⣾⣿⣿⣿⣿⣦⡀⠳⡌⠙⠢⢀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⠔⠋⠀⠀⣠⣤⣾⢟⣀⣼⠿⣿⣿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣻⣿⣿⣿⣳⢯⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡙⠿⣿⣿⣿⣿⣷⡀⢹⣦⣀⡀⠄
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⠔⠊⢁⣠⣴⣾⣿⣿⣿⣃⣈⣿⣄⢸⣯⣤⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣯⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣿⣿⠿⣿⣿⣿⡀⠹⣿⣿⡷
⠀⠀⠀⠀⠀⠀⢀⣀⠴⠚⠁⣤⣀⣬⡿⢟⣿⣿⣿⣿⣧⣿⡿⣿⣿⣶⣹⡿⢿⣿⣿⣿⡿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⢟⣳⣿⣿⣿⣿⣿⣿⣿⣿⣯⣿⣿⣿⣫⣿⣿⣟⡘⢛⣿⣿⣿⣁⣽⣿⣿
⠀⠀⠀⣀⠴⠚⠏⣤⡤⣤⡜⢻⣿⣿⣷⣮⣽⣿⣿⣿⣿⣿⣷⣿⣿⣿⡷⣿⣿⣿⣏⣿⣻⣽⢿⡿⣟⡟⠳⡈⠿⢿⣿⣿⢿⢧⣟⣻⢏⡟⣭⢡⣟⣬⣱⣿⣿⡿⣽⡟⣸⣏⣿⣿⣿⣶⣿⣿⣿⡿⣷⣿⣿
⠀⠀⢀⡄⢲⡀⣴⣏⣿⣹⣬⢳⣿⣿⣿⣿⣿⣿⣿⣟⣻⣽⣷⣿⣿⡞⢷⡟⣯⣿⣿⣷⣻⢿⣾⢻⡼⣽⡳⣇⣎⡳⢽⣞⣯⣟⣯⣟⣯⢿⣽⣿⣿⡿⣿⣿⣿⢧⣿⠡⣿⣿⣿⣿⢿⣿⣿⣿⣿⣿⣿⣿⣿
⣴⣿⣿⣿⣿⣯⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣾⡿⢿⣿⣿⡌⣷⠀⣿⣿⣽⣻⢿⣻⣯⣟⣳⡽⣞⣬⢳⢿⣺⢷⣛⣮⡽⣯⣟⣾⣿⣿⢿⣿⣿⣿⣿⡟⢸⣿⣿⣿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣻	

}








