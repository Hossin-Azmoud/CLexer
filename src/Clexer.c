#include "Clexer.h"

static char *Type_as_cstr[TOKEN_TYPE_AMOUNT] = {
	"STR_LIT",
	"INT",
	"ID",
	"SYM",
	"UNKNOWN"
};

static struct S_TOKEN {
	char *value;
	char *location;
};

static FILE   *file_pointer;
static TokenType s_get_token_type(char *buff);
static char *s_next();
static void s_warning(char *error, char *token);

Token *next() {
	// allocate toke struct
	Token *token = malloc(sizeof(Token));
	// set value token = s_next()
	if (!(token->value = s_next()))
	{
		free(token);
		fclose(file_pointer);
		return (NULL);
	}
	// set type = s_get_token_type()
	token->type = s_get_token_type(token->value);
	return token;
}

static TokenType s_get_token_type(char *buff) {
	char lbuff_char   = buff[strlen(buff) - 1];

	if (is_punct(buff[0])) // SYMBOLS
		return (SYM);

	if (is_quote(buff[0])) {

		if (is_quote(lbuff_char) && buff[0] == lbuff_char)
			return (STR_LIT);
		if(is_quote(lbuff_char) && buff[0] != lbuff_char)
			s_warning("Invalid", buff);
		else
			s_warning("Unterminated", buff);
	}

	// check the whole thing
	if (isdigit(buff[0])) {
		return (INT);
	}

	if (isalpha(buff[0]) && !(is_quote(lbuff_char))) {
		return (ID);
	}

	return (UNKNOWN);
}

/*
 * todo: location, src file name output "token file_name:row:colm"
 */
static char *s_next() {
	static int row = 1, col = 1;
	short it = 0;
	char buf[CAP] = {0};

	while ( ( char c = fgetc(file_pointer)) != EOF )
	{
		if (c == '\n') {
			col = 0;
			row++;
		}

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
	if (!file_pointer)
	{
		perror(file);
		exit(1);
	}
}

char *get_type_name(TokenType t) {
	return Type_as_cstr[t];
}

// make file name global variable.
char *get_file_name()
{
	int     fd;
	char    fd_path[255];
	char    *filename = malloc(255);
	ssize_t n;

	fd = fileno(file_pointer);
	sprintf(fd_path, "/proc/self/fd/%d", fd);
	n = readlink(fd_path, filename, 255);

	if (n < 0)
		return NULL;

	filename[n] = '\0';
	return filename;
}

static void s_warning(char *error, char *token) {
		char *file_name = get_file_name();
		fprintf(stderr, "%s: %s String literal %s\n", (file_name), error, token);
		free(file_name);
}
