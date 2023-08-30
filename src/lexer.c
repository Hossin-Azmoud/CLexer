#include <lexer.h>

// NOTE (#1): lexer private structure.
typedef struct lexer {
	FILE   *file_pointer;
	char   *file_name;
	size_t col, row;
} LEXER;

static void s_get_token_type(Token *token, LEXER *lex);
static Token *s_next(LEXER *lex);
static void  s_warning(char *error, Token *token, char *file);

Token *next(LEXER *lex)
{
	Token *token = s_next(lex);

	if (!token)
		return NULL;

	s_get_token_type(token, lex);
	return token;
}

static void s_get_token_type(Token *token, LEXER *lex)
{
	size_t length = strlen(token->value);
	char   first_char = *(token->value), last_char = token->value[length - 1];

	if (is_punct(first_char)) {
		switch (first_char) {
			case PLUS_C : {
				token->type = PLUS;
			} break;
			case MINUS_C: {
				token->type = MINUS;
			} break;
			case MUL_C  : {
				token->type = MUL;
			} break;
			case DIV_C: {
				token->type = DIV;
			} break;
			default:
				token->type = SYM;
		}

		return;
	}

	if (IS_QUOTE(first_char) || IS_QUOTE(last_char)) {
		// TODO (#1): Handle singular quotes.
		// TODO (#2): Handle escape sequences.
		if (IS_QUOTE(last_char) && (first_char == last_char) && length > 1) {
			token->type = STR_LIT;
			return;
		}

		if(IS_QUOTE(last_char) && first_char != last_char)
			s_warning("Invalid", token, lex->file_name);
		else
			s_warning("Unterminated", token, lex->file_name);

		token->type = UNKNOWN;
		return;
	}

	// check the whole thing
	if (isdigit(first_char)) {
		token->type = INT;
		return;
	}

	if (isalpha(first_char)) {
		token->type = ID;
		return;
	}
}

static Token *s_next(LEXER *lex)
{
	char c = 0;
	short it = 0;
	Token *token = malloc(sizeof(Token));
	char buf[CAP] = {0};

	{
		// NOTE (#2): Define the location of the current token.
		token->row = lex->row;
		token->col = lex->col;
	}

	while ( (c = fgetc(lex->file_pointer)) != EOF ) {
		lex->col++;
		switch (c) {
			case NL: {
				lex->row += 1;
				lex->col  = 1;
			} break;
			case '/': {
				if (!skip_comments(lex)) {
					buf[it++] = c;
					lex->col++;
					continue;
				} 

				token->row = lex->row;
				token->col = lex->col;
			} break;
			case SQ:
			case DQ: {
				buf[it++] = c;
				lex->col++;
				while ((c = getc(lex->file_pointer)) != EOF && !IS_QUOTE(c) && c != NL) {
					if (c == '\\') {
						
					}

					lex->col++;
					buf[it++] = c;
				}

				if (IS_QUOTE(c)) {
					buf[it++] = c;
					lex->col++;
					continue;
				}

				ungetc(c, lex->file_pointer);
			} break;
			default: {
				if (is_punct(c)) {

					if (it > 0) {
						ungetc(c, lex->file_pointer);
						lex->col--;
						break;
					}

					token->value = strdup(&c);
					return token;
				}

				if (!isspace(c))
				{
					buf[it++] = c;
					continue;
				}
			} break;
		}

		if(!(*buf))
			continue;

		break;
	}

	if (c == EOF) {
		free(token);
		return NULL;
	}
	
	token->value = strdup(buf);
	return token;
}
// TODO (#1): this function does unnecessiry move of memory so I think it is useless??
static void s_warning(char *error, Token *token, char *file)
{
	// This part can just be moved to a macro or something..
	fprintf(stderr, "%s:%ld:%ld %s String literal %s\n",
		 file, 
		 token->row, 
		 token->col, 
		 error, 
		 token->value
	);
}

