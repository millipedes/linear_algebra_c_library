/**
 * @file lexer.c
 * @brief this file supports the lexer struct used to parse matrix input
 * @author Matthew C. Lindeman
 * @date 12/14/21
 * @bug None known
 * @todo Nothing atm
 */

#include"include/lexer.h"
#include"../constants/include/constants.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/**
 * This function initializes a lexer structure
 * @param the source string to build from
 * @return the newly formed lexer
 */
lexer_t * init_lexer(char * src) {
	lexer_t * lexer = calloc(1, sizeof(struct LEXER_T));
	lexer->src = src;
	lexer->c = *(src + 0);
	lexer->c_pos = 0;
	lexer->len = strnlen(src, MAX_LEN);
	return lexer;
}

/**
 * This function "advances" the lexer 1 space forward
 * @param the lexer to advance
 * @return the lexer post advance
 */
lexer_t * lexer_advance(lexer_t * lexer) {
	lexer->c_pos++;
	if(lexer->c_pos < lexer->len) {
		lexer->c = lexer->src[lexer->c_pos];
	}
	return lexer;
}

/**
 * This function takes in a lexer with expected matrix format (see 
 * README.md) and parses the id.
 * @param the lexer
 * @return the name of the matrix
 */
char * lex_id(lexer_t * lexer) {
	char * name = calloc(2, sizeof(char));
	int name_size = 2;
	int count = 1;

	while(lexer->c != ' ') {
		if(count > name_size) {
			name = realloc(name, 2*count*sizeof(char));
			name_size *= 2;
		}
		*(name + count - 1) = lexer->c;
		lexer_advance(lexer);
		count++;
	}
	
	// lexer is reset after all functions to give a standard
	reset_lexer(lexer);
	return name;
}

/**
 * This function returns the number of rows and the number of columns for a
 * matrix from a lexer struct.
 * @param The lexer that contains the matrix
 * @return An integer pointer with two elements, rows, cols
 */
int * lex_dims(lexer_t * lexer) {
	int count_semis = 0;
	int count_nums = 0;

	while (lexer->c != '=') {
		lexer_advance(lexer);
	}

	while(lexer->c != ']') {
		if(lexer->c == ';') {
			lexer_advance(lexer);
			count_semis++;
		} else if(lexer->c == ' ' || lexer->c == '[' || lexer->c == '=') {
			lexer_advance(lexer);
		} else if(isdigit(lexer->c)) {
			while(isdigit(lexer->c)) {
				lexer_advance(lexer);
			}
			count_nums++;
		}
	}
	// There is no semicolon for either the first/last row
	count_semis++;

	// lexer is reset after all functions to give a standard
	reset_lexer(lexer);
	
	int * row_col = calloc(2, sizeof(int));
	if(strchr(lexer->src, '\'')) {
		*(row_col + 0) = count_nums / count_semis;
		*(row_col + 1) = count_semis;
	} else {
		*(row_col + 0) = count_semis;
		*(row_col + 1) = count_nums / count_semis;
	}

	return row_col;
}  

/**
 * This function restarts where the c member of a lexer struct is and resets
 * the position member as well
 * @param The lexer to be reset
 * @return The reset lexer
 */
void reset_lexer(lexer_t * lexer) {
	lexer->c = lexer->src[0];
	lexer->c_pos = 0;
}  

/**
 * This function parses a matrix defined by the user and returns an integer
 * pointer with the values that the user passed
 * @param the lexer with a valid matrix definition
 * @return the integer pointer containing the components of the matrix
 */
int ** lex_matrix(lexer_t * lexer) {
	int count_rows = 1;
	int max_rows = 2;
	int count_comp = 1;
	int max_comp = 2;
	int ** matrix = calloc(max_rows, sizeof(int *));

	while(lexer->c != '[') {
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	
	while(lexer->c != ']') {
		if(count_rows > max_rows) {
			matrix = realloc(matrix, 2*count_rows*sizeof(int *));
			max_rows *= 2;
		}
		*(matrix + count_rows - 1) = calloc(max_comp, sizeof(int));
		// This loop processes rows
		while(lexer->c != ';' && lexer->c != ']') {
			if(count_comp > max_comp) {
				*(matrix + count_rows - 1) = realloc(*(matrix + count_rows - 1), 2*count_comp*sizeof(int));
				max_comp *= 2;
			}

			if(lexer->c == ' ') {
				lexer_advance(lexer);
			} else if(isdigit(lexer->c)) {
				*(*(matrix + count_rows - 1) + count_comp - 1) = lex_int(lexer);
				count_comp++;
			}
		}
		count_comp = 1;
		max_comp = 2;
		if(lexer->c == ';') {
			lexer_advance(lexer);
		}
		if(lexer->c == ' ') {
			lexer_advance(lexer);
		}
		count_rows++;
	}

	if(strchr(lexer->src, '\'')) {
		matrix = transpose_matrix(matrix, count_rows, count_comp);
	}

	return matrix;
}  

/**
 * This function parses an integer (assuming that the lexer is pointing to one)
 * @param the lexer
 * @return the integer
 */
int lex_int(lexer_t * lexer) {
	int count = 0;
	char * number = calloc(lexer->len - lexer->c_pos, sizeof(char));

	while(isdigit(lexer->c)) {
		*(number + count) = lexer->c;
		lexer_advance(lexer);
		count++;
	}
	int tmp = atoi(number);
	free(number);
	return tmp;
}

int ** transpose_matrix(int ** matrix, int rows, int cols) {
	return NULL;
}

/**
 * This function frees the lexer.  (It is never feed DA src i.e. src cant be freed)
 * @param the lexer to be freed
 * @return N/a
 */
void free_lexer(lexer_t * lexer) {
	free(lexer);
}

/**
 * This function is just a demo of the correct input format
 * @param N/a
 * @return N/a
 */
void lexer_function_tests(void) {
	lexer_t * lexer1 = init_lexer("v = [1 2 3; 4 5 6]\n");
	lexer_t * lexer2 = init_lexer("u = [1 2; 3 4; 5 6]'\n");
	char * name1 = lex_id(lexer1);
	char * name2 = lex_id(lexer2);
	int * rows1 = lex_dims(lexer1);
	int * rows2 = lex_dims(lexer2);
	int ** matrix1 = lex_matrix(lexer1);
	for(int i = 0; i < *(rows1 + 0); i++) {
		for(int j = 0; j < *(rows1 + 1); j++) {
			printf("%d ", *(*(matrix1 + i) + j));
		}
		printf("\n");
	}
	printf("[NAME1]: `%s`, [ROWS1]: %d, [COLS1]: %d\n", name1, *rows1, *(rows1 + 1));
	printf("[NAME2]: `%s`, [ROWS2]: %d, [COLS2]: %d\n", name2, *rows2, *(rows2 + 1));
	free(name1);
	free(name2);
	free(rows1);
	free(rows2);
	free_lexer(lexer1);
	free_lexer(lexer2);
}
