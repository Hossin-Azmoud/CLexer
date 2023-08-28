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
	char      *location;
} Token;

typedef struct location {
	size_t row;
	size_t col;
} location;

char  *get_file_name();
char  *get_type_name(TokenType t);
void  set_file_pointer(char *file);
Token *next();
int   is_punct(char c);
int   is_quote(char c);

#endif //CLEXER_H

