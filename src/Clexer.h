#ifndef CLEXER_H
#define CLEXER_H

#define _GNU_SOURCE
#define CAP      1024
#define PATH_MAX 4096

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef enum TokenType {
	STR_LIT,
	INT,
	ID,
	SYM,
	UNKNOWN,
	TOKEN_TYPE_AMOUNT
} TokenType;

typedef struct token {
	TokenType type;
	char      *value;
	size_t    row, col;
} Token;

typedef struct lexer {
	FILE   *file_pointer;
	char   *file_name;
	size_t col, row;
} Lexer;

char  *get_type_name(TokenType t);
Token *next(Lexer *lex);
void  open_lexer(Lexer *lex, char *file);
void  close_lexer(Lexer *lex);

#endif // CLEXER_H
