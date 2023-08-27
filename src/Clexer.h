#ifndef CLEXER_H
#define CLEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CAP       256
#define PATH_MAX 4096

typedef enum TokenType {
	STR_LIT,
	UNT_STR_LIT,
	INT,
	ID,
	SYM,
	NONE,
	TOKEN_TYPE_AMOUNT
} TokenType;

typedef struct token {
	TokenType type;
	char      *value;
} Token;


char  *get_type_name(TokenType t);
char  *strdup(char *s);
void set_file_pointer(char *file);
Token *next();
int is_punct(char c);
int is_quote(char c);

#endif //CLEXER_H

