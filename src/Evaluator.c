#include <Evaluator.h>

Token *read_source(char *src)
{
	size_t iterator = 0;
	Token  *toks    = malloc(sizeof(Token *) * TOK_MAX);
	LEXER *lx       = open_lexer(src);
	while ((toks[iterator++] = next(lx)));
	close_lexer(lx);
	return toks;
}
