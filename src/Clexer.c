#include "Clexer.h"

static char *Type_as_cstr[TOKEN_TYPE_AMOUNT] = {
	"STR_LIT",
	"UNT_STR_LIT",
	"INT",
	"ID",
	"SYM",
	"NONE"
};

static FILE *file_pointer;
static TokenType s_get_token_type(char *buff);
static char *s_next();

Token *next() {
	// allocate toke struct
	Token *token = malloc(sizeof(Token));
	// set value token = s_next()
	if (!(token->value = s_next()))
	{
		free(token);
		return (NULL);
	}
	// set type = s_get_token_type()
	token->type = s_get_token_type(token->value);
	return token;
}

static TokenType s_get_token_type(char *buff) {
	char _quote = 0;
	size_t it   = 0;

	if (is_punct(buff[it])) // SYMBOLS
		return (SYM);

	if (is_quote(buff[it]))
	{
		_quote = buff[it++];
		while (buff[it] != _quote)
		{
			if (!buff[it])
				break;
			it++;
		}
	
		if (buff[it] == _quote)
			return (STR_LIT);

		return (UNT_STR_LIT);
	}

	if (isdigit(buff[it])) 
	{
		while (buff[it])
		{
			if (!isdigit(buff[it]))
			{
				return (NONE);
			}

			it++;
		}

		return (INT);
	}

	if (isalnum(buff[it]))
		return (ID);

	return (NONE);
}

static char *s_next() {
	char c;
	short it = 0;
	char buf[CAP] = {0};

	while ( ( c = fgetc(file_pointer)) != EOF )
	{

		if (is_punct(c)) {

			if (it > 0) {
				ungetc(c, file_pointer);
				break;
			}

			return strdup(&c);
		}

		if (!isspace(c)) {
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

int is_quote(char c) {
	return (c == '\"') || (c == '\'');
}

int is_punct(char c) {
	return (ispunct(c) && !is_quote(c));
}

void set_file_pointer(char *file) {
	file_pointer = fopen(file, "r");
}

char *get_type_name(TokenType t) {
	return Type_as_cstr[t];
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

