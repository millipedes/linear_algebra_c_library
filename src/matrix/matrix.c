/**
 * @file matrix.c
 * @brief This file defines matrices and basic function support matrices.
 * @author Matthew C. Lindeman
 * @date 12/14/21
 * @bug None known
 * @todo Nothing atm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"include/matrix.h"
#include"../lexer/include/lexer.h"
#include"../constants/include/constants.h"

/**
 * This function initializes a matrix
 * @param a parseable input (see README.md)
 * @return a matrix according to the user's specification
 */
matrix_t * init_matrix(char * ui) {
	lexer_t * lexer = init_lexer(ui);
	matrix_t * matrix = calloc(1, sizeof(struct MATRIX_T));
	matrix->id = lex_id(lexer);
	matrix->matrix = lex_matrix(lexer);
	matrix->row_col = lex_dims(lexer);
	free_lexer(lexer);
	return matrix;
}

/**
 * This function find the matrix with the specified name and returns the index of it
 * @param the list of matrices from which it is to be found
 * @return the matrix with the desired name (or exits with an error)
 */
int matrix_finder(matrix_t ** matrix_list, int list_size, char * name) {
	for(int i = 0; i < list_size; i++) {
		if(!strncmp(matrix_list[i]->id, name, MAX_LEN)) {
			return i;
		}
	}
	return -1;
}

/**
 * This function takes two matrices and adds them if possible errors if not
 * @param the two matrices to be added
 * @return the resulting matrix of the addition
 */
matrix_t * matrix_addition(matrix_t * matrix1, matrix_t * matrix2) {
	return NULL; 
}

/**
 * This function takes two matrices and substracts them if possible erros if not
 * @param The two matrices to be subtracted
 * @return the resulting matrix of the subtraction
 */
matrix_t * matrix_substraction(matrix_t * matrix1, matrix_t * matrix2) {
 	return NULL;
}

/**
 * This function takes two matrices and multiplies them if possible
 * @param the matrices
 * @return the resulting matrix
 */
matrix_t * matrix_multiply(matrix_t * matrix1, matrix_t * matrix2) {
	 return NULL;
}

/**
 * This function takes in a matrix and finds its determinent
 * @param The matrix
 * @return the determinent
 */
int matrix_determinent(matrix_t * matrix) {
	return -1;
}
 
/**
 * This function prints a matrix in a relatively user-friendly way
 * @param the matrix to be pinted
 * @return N/a
 */
void print_matrix(matrix_t * matrix) {
	printf("%s =\n", matrix->id);
	for(int i = 0; i < matrix->row_col[0]; i++) {
		printf("| ");
		for(int j = 0; j < matrix->row_col[1]; j++) {
			printf("%d ", matrix->matrix[i][j]);
		}
		printf("|\n");
	}
}

/**
 * This function frees the matrix
 * @param The matrix
 * @return N/a
 */
void free_matrix(matrix_t * matrix) {
	for(int i = 0; i < matrix->row_col[0]; i++) {
		free(matrix->matrix[i]);
	}
	free(matrix->id);
	free(matrix->matrix);
	free(matrix->row_col);
	free(matrix);
} 
  
/**
 * The test function for the matrix functions that I am implementing
 * @param N/a
 * @return N/a
 */
void matrix_tests(void) {
	matrix_t * matrix = init_matrix("v = [15 2 3; 4 5 26; 7 18 9]\n");
	print_matrix(matrix);
	free_matrix(matrix);
}
