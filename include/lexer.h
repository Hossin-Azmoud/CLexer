#ifndef CLEXER_H
#define CLEXER_H
#include <Token.h>

typedef struct lexer LEXER;

Token *next(LEXER *lex);
LEXER *open_lexer(char *file);
void  close_lexer(LEXER *lex);
int   skip_comments(LEXER *lex);

#endif // CLEXER_H
