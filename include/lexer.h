#ifndef CLEXER_H
#define CLEXER_H
#include <Token.h>
// NOTE (#1): lexer private structure.
typedef struct lexer {
	FILE   *file_pointer;
	char   *file_name;
	size_t col, row;
} LEXER;

Token *next(LEXER *lex);
LEXER *open_lexer(char *file);
void  close_lexer(LEXER *lex);
int   skip_comments(LEXER *lex);

#endif // CLEXER_H
