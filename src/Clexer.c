#include "Clexer.h"

static FILE *file_pointer;

void set_file_pointer(char *file){
	file_pointer = fopen(file, "r");
}

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

//lexer *new_lexer(char *path)
//{
//	lexer *lex = malloc(sizeof(lexer));
//
//	if (path == NULL)
//	{
//		free(lex);
//		fprintf(stderr, "Could not open the file! because u provided null path..\n");
//		return (NULL);
//	}
//
//	if (lex == NULL)
//		return (NULL);
//	
//	lex->file_path    = strdup(path);
//	lex->file_pointer = fopen(lex->file_path, "r");
//
//	if (lex->file_pointer == NULL)
//	{
//		fprintf(stderr, "Could not read the file..\n");
//		free(lex);
//		return (NULL);
//	}
//
//	return (lex);
//}

Token *next() {
	// allocate toke struct
	Token *token = malloc(sizeof(Token));
	// set value token = s_next()
	token->value = s_next();
	// set type = s_get_token_type()
	token->type = s_get_token_type(token->value);
	return token;
}

static TokenType s_get_token_type() {
	return INT;
}

static char *s_next() {
	char c;
	short it = 0;
	char buf[CAP] = {0};

	while ( ( c = fgetc(file_pointer)) != EOF )
	{
		if (ispunct(c)) {
			if (it > 0) {
				ungetc(c, file_pointer);
				break;
			}
			return strdup(&c);
		}

		if (isalnum(c)) {
			buf[it++] = c;
			continue;
		}

		// if not a valid token continue
		if(!(*buf))
			continue;

		// if space exit out of the loop
		break;
	}

	if (c == EOF)
			return (NULL);

	char *value = malloc(strlen(buf) + 1);
	strcpy(value, buf);
	return value;
}

//void free_lexer(lexer *lex)
//{
//	if (lex == NULL)
//		return;
//
//	fclose(lex->file_pointer);
//	free(lex->file_path);
//	free(lex);
//}
