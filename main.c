#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#define SZ       32
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
	char    *source;
	char    *file_path;
	size_t  index;
	size_t  size;
	size_t  cap;
} lexer;

char *get_type_name(TokenType t)
{
	switch(t)
	{
		case STR_LIT: { return "STR_LIT"; } break;
		case INT:     { return "INT"; } break;
		case ID:      { return "ID"; } break;
		case SYM:     { return "SYM"; } break;
		default:
			return ("NONE");
	}

	return ("NONE");
}

char *strdup(char *s)
{
	size_t it = 0;
	char *ptr;

	if (s == NULL)
		return (NULL);

	ptr = malloc(strlen(s) + 1);

	while (*(s + it))
	{
		*(ptr + it) = *(s + it);
		it++;
	}

	*(ptr + it)	 = 0;
	return (ptr);
}

lexer *new_lexer(char *path)
{
	lexer *lex = malloc(sizeof(lexer));

	if (path == NULL)
	{
		free(lex);
		fprintf(stderr, "Could not open the file! because u provided null path..\n");
		return (NULL);
	}

	if (lex == NULL)
		return (NULL);
	
	lex->source       = malloc(SZ);
	lex->cap          = SZ;
	lex->index        = 0;
	lex->file_path    = strdup(path);
	lex->file_pointer = fopen(lex->file_path, "r");

	if (lex->file_pointer == NULL)
	{
		fprintf(stderr, "Could not read the file..\n");
		free(lex);
		return (NULL);
	}

	return (lex);
}

token *next(lexer *lex)
{
	char byte    = lex->source[lex->index];
	size_t it    = 0;
	size_t cap   = SZ;
	token *Token = malloc(sizeof(token));
	char  *value = malloc(SZ);

	while (isspace(byte))
	{
		lex->index++;
		byte = lex->source[lex->index];
	}

	if (!byte)
	{
		free(value);
		free(Token);
		return (NULL);
	}

	while (byte && !isspace(byte) && byte != EOF)
	{
		if (it >= cap)
		{
			value  = realloc(value, cap * 2);
			cap   *= 2;
		}

		value[it] = byte;
		lex->index++;
		byte      = lex->source[lex->index];
		it++;
	}
	value[it] = 0;
	Token->value = (value);
	Token->Type = ID;
	return Token;
}

void read_into_lexer(lexer *lex)
{
	char c = 0;

	while (1)
	{
		if (lex->index >= lex->cap)
		{
			lex->source = realloc(lex->source, lex->cap * 2);
			lex->cap *= 2;
		}

		c = fgetc(lex->file_pointer);

		if (c == EOF)
			break;

		lex->source[lex->index++] = c;
	}

	lex->source[lex->index++] = 0;
	lex->size                 = lex->index;
	lex->index                = 0;
}

void free_lexer(lexer *lex)
{
	if (lex == NULL)
		return;

	fclose(lex->file_pointer);
	free(lex->source);
	free(lex->file_path);
	free(lex);
}

int main()
{
	lexer *lx = new_lexer("./src.txt");
	token *tok = NULL;
	if (lx)
		read_into_lexer(lx);
	
	tok = next(lx);
	while (tok)
	{
		putchar('\n');
		printf("Token: %s\n", tok->value);
		printf("Type:  %s\n", get_type_name(tok->Type));	
		putchar('\n');
		free(tok->value);
		free(tok);
		tok = next(lx);
	}

	printf("%s\n", lx->source);
	free_lexer(lx);
	return (0);
}
