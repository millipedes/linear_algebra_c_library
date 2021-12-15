/**
 * @file lexer.h
 * @brief the function headers of the functions in lexer.c
 * @author Matthew C. Lindeman
 * @date 12/14/21
 * @bug None known
 * @todo Nothing atm
 */
#ifndef LEX_H
#define LEX_H

typedef struct LEXER_T {
	char * src;
	char c;
	int len;
	int c_pos;
} lexer_t;

lexer_t * init_lexer(char * src);
lexer_t * lexer_advance(lexer_t * lexer);
char * lex_id(lexer_t * lexer);
int * lex_dims(lexer_t * lexer);
void reset_lexer(lexer_t * lexer);
int ** lex_matrix(lexer_t * lexer);
void free_lexer(lexer_t * lexer);

#endif
