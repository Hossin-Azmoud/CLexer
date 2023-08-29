#include "Clexer.h"

static char *Type_as_cstr[TOKEN_TYPE_AMOUNT] = {
	"STR_LIT",
	"INT",
	"ID",
	"SYM",
	"UNKNOWN"
};

// NOTE (#1): lexer private structure.
typedef struct lexer {
	FILE   *file_pointer;
	char   *file_name;
	size_t col, row;
} LEXER;

static void skip_spaces(LEXER *lex);
static int  skip_comments(LEXER *lex);
static void s_get_token_type(Token *token, LEXER *lex);
// static Token *s_next(LEXER *lex);
static Token *s_next_o(LEXER *lex);
static void s_warning(char *error, Token *token, char *file);

static inline int is_punct(char c);
static inline int is_quote(char c);

Token *next(LEXER *lex)
{
	Token *token;

	if (!(token = s_next_o(lex)))
		return NULL;

	s_get_token_type(token, lex);
	return token;
}

static void s_get_token_type(Token *token, LEXER *lex)
{
	char first_char = *(token->value), last_char = token->value[strlen(token->value) - 1];

	if (is_punct(first_char)) {
		token->type = SYM;
		return;
	}

	if (is_quote(first_char)) {
		// TODO (#1): Handle singular quotes.
		if (is_quote(last_char) && (first_char == last_char)) {
			token->type = STR_LIT;
			return;
		}

		if(is_quote(last_char) && first_char != last_char)
			s_warning("Invalid", token, lex->file_name);
		else
			s_warning("Unterminated", token, lex->file_name);
	}

	// check the whole thing
	if (isdigit(first_char)) {
		token->type = INT;
		return;
	}

	if (isalpha(first_char)) {
		token->type = ID;
		return;
	}

	token->type = UNKNOWN;
}

static Token *s_next_o(LEXER *lex)
{
	char c = 0;
	short it = 0;
	Token *token = malloc(sizeof(Token));
	char buf[CAP] = {0};

	{
		// NOTE (#2): Define the location of the current token.
		token->row = lex->row;
		token->col = lex->col;
	}

	while ( (c = fgetc(lex->file_pointer)) != EOF ) {
		lex->col++;
		switch (c) {
			case '\n': {
				lex->row += 1;
				lex->col  = 1;
			} break;
			case '/': {
				if (!skip_comments(lex)) {
					buf[it++] = c;
					lex->col++;
					continue;
				} 

				token->row = lex->row;
				token->col = lex->col;
			} break;
			case '\'':
			case '\"': {
				buf[it++] = c;
				lex->col++;
				while ((c = getc(lex->file_pointer)) != EOF && !is_quote(c) && c != '\n') {
					lex->col++;
					buf[it++] = c;
				}

				if (is_quote(c)) {
					buf[it++] = c;
					lex->col++;
					continue;
				}

				ungetc(c, lex->file_pointer);
			} break;
			default: {
				if (is_punct(c)) {
					if (it > 0) {
						ungetc(c, lex->file_pointer);
						lex->col--;
						break;
					}

					token->value = strdup(&c);
					return token;
				}

				if (!isspace(c))
				{
					buf[it++] = c;
					continue;
				}
			} break;
		}

		if(!(*buf))
			continue;

		break;
	}

	if (c == EOF) {
		free(token);
		return NULL;
	}
	
	token->value = strdup(buf);
	return token;
}

// static Token *s_next(LEXER *lex)
// {
// 	char c = 0;
// 	short it = 0;
// 	Token *token = malloc(sizeof(Token));
// 	char buf[CAP] = {0};
//
// 	{
// 		// NOTE (#2): Define the location of the current token.
// 		token->row = lex->row;
// 		token->col = lex->col;
// 	}
//
// 	while ( (c = fgetc(lex->file_pointer)) != EOF ) {
// 		lex->col++;
// 		if (is_punct(c)) {
// 			if (it > 0) {
// 				ungetc(c, lex->file_pointer);
// 				lex->col--;
// 				break;
// 			}
//
// 			token->value = strdup(&c);
// 			return token;
// 		}
//
// 		if (is_quote(c)) {
// 			while ((c = getc(lex->file_pointer)) != EOF && !is_quote(c)) {
// 				lex->col++;
// 				buf[it++] = c;
// 			}
// 		}
//
// 		if (!isspace(c)) {
// 			buf[it++] = c;
// 			continue;
// 		}
//
// 		// if not a valid token continue
// 		if(!(*buf))
// 			continue;
//
// 		// if space exit out of the loop
// 		if (c == '\n') {
// 			lex->row += 1;
// 			lex->col  = 1;
// 		}
// 		
// 		break;
// 	}
//
// 	if (c == EOF) {
// 		free(token);
// 		return NULL;
// 	}
// 	
// 	token->value = strdup(buf);
// 	return token;
// }
 
static inline int is_quote(char c)
{
	return (c == '\"') || (c == '\'');
}

static inline int is_punct(char c)
{
	return (ispunct(c) && !is_quote(c));
}

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

char *get_type_name(TokenType t)
{
	return Type_as_cstr[t];
}

static void s_warning(char *error, Token *token, char *file)
{
	fprintf(stderr, "%s:%ld:%ld %s String literal %s\n",
		 file, 
		 token->row, 
		 token->col, 
		 error, 
		 token->value
	);
}

static void skip_spaces(LEXER *lex)
{
	char c = 0;

	while (isspace((c = fgetc(lex->file_pointer)))) {
		switch (c) {
			case '\n': {
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

static int skip_comments(LEXER *lex)
{
	char c = getc(lex->file_pointer);

	if (c == '/') {
		while ((c = getc(lex->file_pointer)) != EOF && c != '\n') {
			lex->col++;
		}

		if (c == '\n') {
			lex->row += 1;
			lex->col  = 1;
		}

		return 1;
	}

	// NOTE (#5): Unskip the latest char.
	ungetc(c, lex->file_pointer);
	return 0;
}
