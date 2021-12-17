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
 * This function takes in the parameters required to make a matrix_t struct
 * and makes a copy (deep) from the parameters
 * @param the id of the new matrix, the number of row and cols of new matrix
 * and the componenets of the matrix
 * @return the newly formed matrix
 */
matrix_t * init_matrix_from_params(char * id, int rows, int cols, int ** matrix) {
	matrix_t * init_matrix = calloc(1, sizeof(struct MATRIX_T));
	init_matrix->id = calloc(strnlen(id, MAX_LEN), sizeof(char));
	init_matrix->row_col = calloc(2, sizeof(int));
	init_matrix->matrix = calloc(rows, sizeof(int *));
	for(int i = 0; i < rows; i++) {
		init_matrix->matrix[i] = calloc(cols, sizeof(int));
	}
	for(int i = 0; i < strnlen(id, MAX_LEN); i++) {
		init_matrix->id[i] = id[i];
	}
	init_matrix->row_col[0] = rows;
	init_matrix->row_col[1] = cols;

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			init_matrix->matrix[i][j] = matrix[i][j];
		}
	}
	return init_matrix;
}

/**
 * This function creates an exact (deep) copy (i.e. needs to be freed
 * seperately), of the matrix that is input.
 * @param The matrix to be copied
 * @return The deep copy
 */
matrix_t * matrix_copy(matrix_t * matrix) {
	matrix_t * copy = calloc(1, sizeof(struct MATRIX_T));
	copy->id = calloc(strnlen(matrix->id, MAX_LEN), sizeof(char));
	copy->row_col = calloc(2, sizeof(int));
	copy->matrix = calloc(matrix->row_col[0], sizeof(int *));
	for(int i = 0; i < matrix->row_col[0]; i++) {
		copy->matrix[i] = calloc(matrix->row_col[1], sizeof(int));
	}
	for(int i = 0; i < strnlen(matrix->id, MAX_LEN); i++) {
		copy->id[i] = matrix->id[i];
	}
	copy->row_col[0] = matrix->row_col[0];
	copy->row_col[1] = matrix->row_col[1];

	for(int i = 0; i < copy->row_col[0]; i++) {
		for(int j = 0; j < copy->row_col[1]; j++) {
			copy->matrix[i][j] = matrix->matrix[i][j];
		}
	}
	return copy;
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
	if(matrix1->row_col[0] != matrix2->row_col[0] || matrix1->row_col[1] != matrix2->row_col[1]) {
		fprintf(stderr, "[ERROR]: add_matrix given two matrices of different dimensions");
		exit(1);
	}
	matrix_t * result = matrix_copy(matrix1);
	for(int i = 0; i < result->row_col[0]; i++) {
		for(int j = 0; j < result->row_col[1]; j++) {
			result->matrix[i][j] += matrix2->matrix[i][j];
		}
	}
	return result; 
}

/**
 * This function takes two matrices and substracts them if possible errors if not
 * @param The two matrices to be subtracted
 * @return the resulting matrix of the subtraction
 */
matrix_t * matrix_substraction(matrix_t * matrix1, matrix_t * matrix2) {
	if(matrix1->row_col[0] != matrix2->row_col[0] || matrix1->row_col[1] != matrix2->row_col[1]) {
		fprintf(stderr, "[ERROR]: add_matrix given two matrices of different dimensions");
		exit(1);
	}
	matrix_t * result = matrix_copy(matrix1);
	for(int i = 0; i < result->row_col[0]; i++) {
		for(int j = 0; j < result->row_col[1]; j++) {
			result->matrix[i][j] -= matrix2->matrix[i][j];
		}
	}
	return result; 
}

/**
 * This function takes two matrices and multiplies them if possible
 * @param the matrices
 * @return the resulting matrix
 */
matrix_t * matrix_multiply(matrix_t * matrix1, matrix_t * matrix2) {
	if(matrix1->row_col[0] != matrix2->row_col[1]) {
		fprintf(stderr, "[ERROR]: matrices of incorrect dimensions were passed to matrix_multiply\nMaybe check order");
		exit(1);
	}
	// dimenion of resulting matrix will be row1xcol2
	int ** result_matrix = calloc(matrix1->row_col[0], sizeof(int *));
	for (int i = 0; i < matrix1->row_col[0]; ++i) {
		*(result_matrix + i) = calloc(matrix2->row_col[1], sizeof(int));
	}

	for (int i = 0; i < matrix1->row_col[0]; i++) {
		for (int j = 0; j < matrix2->row_col[1]; j++) {
			for(int k = 0; k < matrix2->row_col[1]; k++) {
				result_matrix[i][j] += (matrix1->matrix[i][k] * matrix2->matrix[k][j]);
			}
		}
	}

	matrix_t * result = init_matrix_from_params("result", matrix1->row_col[0], matrix2->row_col[1], result_matrix);

	// Since result is a deep copy, unnfortunately result_matrix needs to be freed
	if (result_matrix) {
		for (int i = 0; i < matrix1->row_col[0]; i++) {
			free(*(result_matrix + i));
		}
		free(result_matrix);
	}
	return result;
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
	matrix_t * matrix1 = init_matrix("v = [15 2 3; 4 5 26; 7 18 9]\n");
	matrix_t * matrix2 = init_matrix("u = [15 2 3; 4 5 26; 7 18 9]\n");
	print_matrix(matrix1);
	print_matrix(matrix2);
	matrix_t * matrix_addr = matrix_addition(matrix1, matrix2);
	matrix_t * matrix_subr = matrix_substraction(matrix1, matrix2);
	matrix_t * matrix_mult = matrix_multiply(matrix1, matrix2);
	print_matrix(matrix_addr);
	print_matrix(matrix_subr);
	print_matrix(matrix_mult);
	free_matrix(matrix1);
	free_matrix(matrix2);
	free_matrix(matrix_addr);
	free_matrix(matrix_subr);
	free_matrix(matrix_mult);
}
