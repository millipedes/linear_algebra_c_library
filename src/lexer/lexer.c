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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

int ** lex_matrix(lexer_t * lexer) {
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

