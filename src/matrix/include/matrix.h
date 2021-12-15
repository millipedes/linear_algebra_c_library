/**
 * @file matrix.h
 * @brief the function headers of the functions defined in matrix.c
 * @author Matthew C. Lindeman
 * @date 12/14/21
 * @bug None known
 * @todo Nothing atm
 */
#ifndef MAT_H
#define MAT_H

typedef struct MATRIX_T {
	char * id;
	int * row_col;
	int ** matrix;
} matrix_t;

matrix_t * init_matrix(char * ui);
int matrix_finder(matrix_t ** matrix_list, char * name);
matrix_t * matrix_multiply(matrix_t * matrix1, matrix_t * matrix2);
int matrix_determinent(matrix_t * matrix);
void free_matrix(matrix_t * matrix);

#endif
