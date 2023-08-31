#ifndef TOKEN_H
#define TOKEN_H
#include <core.h>

typedef enum TokenType {
	STR_LIT,
	INT,
	ID,
	SYM,
	PLUS,
	MINUS,
	MUL,
	DIV,
	UNKNOWN,
	TOKEN_TYPE_AMOUNT
} TokenType;

typedef struct token {
	TokenType type;
	char      *value;
	size_t    row, col;
} Token;

char *get_type_name(TokenType t);
#endif // TOKEN_H
