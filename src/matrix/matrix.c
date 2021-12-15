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
	return matrix;
}

/**
 * This function find the matrix with the specified name and returns the index of it
 * @param the list of matrices from which it is to be found
 * @return the matrix with the desired name (or exits with an error)
 */
int matrix_finder(matrix_t ** matrix_list, char * name) {
	 return -1;
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
 * This function frees the matrix
 * @param The matrix
 * @return N/a
 */
void free_matrix(matrix_t * matrix) {
 
} 
  
