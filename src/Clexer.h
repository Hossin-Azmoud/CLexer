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
	INT,
	ID,
	SYM
} TokenType;

typedef struct token {
	TokenType type;
	char      *value;
} Token;


char  *get_type_name(TokenType t);
char  *strdup(char *s);
void set_file_pointer(char *file);
Token *next();

#endif //CLEXER_H

