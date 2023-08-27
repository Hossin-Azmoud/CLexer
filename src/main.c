#include "Clexer.h"

int main()
{
	lexer *lx = new_lexer("./src.txt");
	token *tok = NULL;

	while ((tok = next(lx)))
	{
		printf("Token: %s\n", tok->value);
		printf("Type: %s\n", get_type_name(tok->Type));
		printf("\n");
		free(tok->value);
		free(tok);
	}

	free_lexer(lx);
	return (0);
}
