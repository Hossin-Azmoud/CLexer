#ifndef CLEXER_H
#define CLEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define CAP       256
#define PATH_MAX 4096

typedef enum TokenType {
	STR_LIT,
	INT,
	ID,
	SYM
} TokenType;

typedef struct token {
	TokenType Type;
	char      *value;
} token;

typedef struct lexer {
	FILE    *file_pointer;
	char    *file_path;
} lexer;

char  *get_type_name(TokenType t);
char  *strdup(char *s);
lexer *new_lexer(char *path);
token *next(lexer *lex);
void  free_lexer(lexer *lex);

#endif //CLEXER_H

