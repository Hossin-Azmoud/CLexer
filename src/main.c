#include "Clexer.h"
int main()
{
	Lexer *lx = malloc(sizeof(Lexer));

	// NOTE: (#1) open_lexer is a function that open the "src" file and initializes the neccessiry data.
	open_lexer(lx, "src");
	
	{
		Token *tok;
		while ((tok = next(lx))) {
			printf("VALUE: %s\n", tok->value);
			printf("TYPE: %s\n", get_type_name(tok->type));
			printf("LOCATION: (%ld, %ld)\n", tok->row, tok->col);

			free(tok->value);
			free(tok);
		}
	}

	// NOTE: (#2) close_lexer is a function that closes the file and frees resources.
	close_lexer(lx);
}
