#include <lexer.h>

void run(char *file);
int main(int argc, char **argv)
{
	if (argc > 1) {
		run(argv[1]);
		return 0;
	}

	fprintf(stderr, "Expected a file name to lex. but found nothing.\n");
	fprintf(stderr, "USAGE: %s <file_name>\n", argv[0]);

	return 1;
}

void run(char *file)
{
	// NOTE: (#1) open_lexer is a function that open the "src" file and initializes the neccessiry data.
	LEXER *lx = open_lexer(file);

	{
		Token *tok;
		while ((tok = next(lx))) {
			printf("%7s -> %5s -> <(%ld, %ld)>\n",
				tok->value,
				get_type_name(tok->type),
				tok->row,
				tok->col
			);
			token_free(tok);
		}
	}

	// NOTE: (#2) close_lexer is a function that closes the file and frees resources.
	close_lexer(lx);
}
