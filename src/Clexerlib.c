#include "Clexer.h"
static void skip_spaces(LEXER *lex);

// NOTE (#1): lexer private structure.
typedef struct lexer {
	FILE   *file_pointer;
	char   *file_name;
	size_t col, row;
} LEXER;

LEXER *open_lexer(char *file)
{
	LEXER *lex = malloc(sizeof(LEXER));
	lex->file_pointer = fopen(file, "r");

	if (!lex->file_pointer) {
		perror(file);
		free(lex);
		exit(1);
	}
	
	lex->file_name = strdup(file);
	lex->row       = 1;
	lex->col       = 1;

	// NOTE (#3): Function that skips all the spaces and sets the 
	skip_spaces(lex);
	return lex;
}

void  close_lexer(LEXER *lex)
{
	fclose(lex->file_pointer);
	free(lex->file_name);
	free(lex);
}

static void skip_spaces(LEXER *lex)
{
	char c = 0;

	while (isspace((c = fgetc(lex->file_pointer)))) {
		switch (c) {
			case NL: {
				lex->col =  1;
				lex->row += 1;
			} break;
			default: {
				lex->col++;
			} break;
		}
	}

	// NOTE (#4): Ungets the latest char because it is not a space so it will not be ignored.
	ungetc(c, lex->file_pointer);
}

int is_punct(char c)
{
	return (ispunct(c) && !IS_QUOTE(c));
}

int skip_comments(LEXER *lex)
{
	char c = getc(lex->file_pointer);

	if (c == '/') {
		while ((c = getc(lex->file_pointer)) != EOF && c != NL) {
			lex->col++;
		}

		if (c == NL) {
			lex->row += 1;
			lex->col  = 1;
		}

		return 1;
	}

	// NOTE (#5): Unskip the latest char.
	ungetc(c, lex->file_pointer);
	return 0;
}

char *get_type_name(TokenType t)
{
	// NOTE (#6): Made it local static so other functions can not access it but it is indeed initialized only once and has 
	// the life time of the whole program so we don't allocate and reallocate each time we call this function.
	static char *Type_as_cstr[TOKEN_TYPE_AMOUNT] = {
		"STR_LIT",
		"INT",
		"ID",
		"SYM",
		"UNKNOWN"
	};

	return Type_as_cstr[t];
}

