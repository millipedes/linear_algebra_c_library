#include<stdio.h>
#include<stdlib.h>
#include"../lexer/include/lexer.h"

int main(void)
{
	lexer_t * lexer1 = init_lexer("This_is_a_test_variable = [1 2 3; 4 5 6]\n");
	lexer_t * lexer2 = init_lexer("This_is_a_test_variable = [1 2; 3 4; 5 6]'\n");
	char * name1 = lex_id(lexer1);
	char * name2 = lex_id(lexer2);
	int * rows1 = lex_dims(lexer1);
	int * rows2 = lex_dims(lexer2);
	printf("[NAME1]: `%s`, [ROWS1]: %d, [COLS1]: %d\n", name1, *rows1, *(rows1 + 1));
	printf("[NAME2]: `%s`, [ROWS2]: %d, [COLS2]: %d\n", name2, *rows2, *(rows2 + 1));
	free(name1);
	free(name2);
	free(rows1);
	free(rows2);
	free_lexer(lexer1);
	free_lexer(lexer2);
	return 0;
}
