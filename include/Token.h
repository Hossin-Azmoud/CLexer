#ifndef TOKEN_H
#define TOKEN_H
#define _GNU_SOURCE

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define PLUS_C  '+'
#define MINUS_C '-'
#define MUL_C   '*'
#define DIV_C   '/'

#define O_PAREN_C   '('
#define C_PAREN_C   ')'
#define O_BRACKET_C '['
#define C_BRACKET_C ']'
#define O_CURLY_C   '{'
#define C_CURLY_C   '}'

#define CAP      1024
#define TOK_MAX  512
#define PATH_MAX 4096
#define NL '\n'
#define SQ '\''
#define DQ '\"'
#define IS_QUOTE(c) (c == SQ || c == DQ)

typedef enum TokenType {
	// primitive token types.
	STR_LIT,
	INT,
	ID,
	SYM,

	// Operators.
	PLUS,
	MINUS,
	MUL,
	DIV,

	// Seperators. () [] {}
	O_PAREN,
	C_PAREN,
	O_BRACKET,
	C_BRACKET,
	O_CURLY,
	C_CURLY,
	UNKNOWN,
	TOKEN_TYPE_AMOUNT
} TokenType;

typedef struct token {
	TokenType type;
	char      *value;
	size_t    row, col;
} Token;

int is_punct(char c);
char *get_type_name(TokenType t);
void migrate_token(Token *token, TokenType type);
void token_free(Token *token);

#endif // TOKEN_H
