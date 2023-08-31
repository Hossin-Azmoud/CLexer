#include "Token.h"

int is_punct(char c)
{
	return (ispunct(c) && !IS_QUOTE(c));
}

void free_raw_token(void *token)
{
	token_free((Token *) token);
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
		"PLUS",
		"MINUS",
		"MUL",
		"DIV",
		"O_PAREN",
		"C_PAREN",
		"O_BRACKET",
		"C_BRACKET",
		"O_CURLY",
		"C_CURLY",
		"UNKNOWN"
	};

	return Type_as_cstr[t];
}

void migrate_token(Token *token, TokenType type)
{
	if (token) {
		free(token->value);
		token->type  = type;
		token->value = NULL;
	}
}

void token_free(Token *token)
{
	if (token) {
		if (token->value)
			free(token->value);
		free(token);
	}
}

