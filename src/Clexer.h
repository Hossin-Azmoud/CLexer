#ifndef CLEXER_H
#define CLEXER_H
#define _GNU_SOURCE

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define CAP      1024
#define PATH_MAX 4096
#define NL '\n'
#define SQ '\''
#define DQ '\"'
#define IS_QUOTE(c) (c == SQ || c == DQ)

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

typedef struct lexer LEXER;

char  *get_type_name(TokenType t);
Token *next(LEXER *lex);
LEXER *open_lexer(char *file);
void   close_lexer(LEXER *lex);
int is_punct(char c);
int skip_comments(LEXER *lex);

#endif // CLEXER_H
