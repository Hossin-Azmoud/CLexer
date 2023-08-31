#include <Lexer.h>
#include <Structures/Stack.h>

int run(int argc, char **argv);

int main()
{
	Token *tok = malloc(sizeof(Token));

	// ({.value = "Hello\0", .type=STR_LIT})
	tok->type  = STR_LIT;
	tok->value = strdup("Hello");

	Stack *s = stack_new();

	stack_push(s, (void *) tok);
	free_stack(s, free_raw_token);
}

int run(int argc, char **argv)
{
	char *file = NULL;
	if (argc <= 1) {
		fprintf(stderr, "Expected a file name to lex. but found nothing.\n");
		fprintf(stderr, "USAGE: %s <file_name>\n", argv[0]);
		return 1;
	}
	
	file = argv[1];
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
	return 0;
}
