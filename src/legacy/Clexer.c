#include "Clexer.h"

static char *Type_as_cstr[TOKEN_TYPE_AMOUNT] = {
	"STR_LIT",
	"INT",
	"ID",
	"SYM",
	"UNKNOWN"
};

static location current_location = {.row = 1, .col = 1};
static location temp_location = {.row = 1, .col = 1};

static FILE      *file_pointer;
static TokenType s_get_token_type(char *buff);
static char      *s_next();
static void      s_warning(char *error, char *token);
static void      s_set_global_loc();

Token *next()
{
	// allocate toke struct
	Token *token = malloc(sizeof(Token));
	// set value token = s_next()
	if (!(token->value = s_next())) {
		free(token);
		fclose(file_pointer);
		return (NULL);
	}

	// set type = s_get_token_type()
	token->type = s_get_token_type(token->value);
	return token;
}


static TokenType s_get_token_type(char *buff)
{
	char lbuff_char   = buff[strlen(buff) - 1];

	if (is_punct(buff[0])) // SYMBOLS
		return SYM;

	if (is_quote(buff[0])) {
		// TODO (#1): Handle singular quotes.
		if (is_quote(lbuff_char) && buff[0] == lbuff_char)
			return (STR_LIT);
		if(is_quote(lbuff_char) && buff[0] != lbuff_char)
			s_warning("Invalid", buff);
		else
			s_warning("Unterminated", buff);
	}

	// check the whole thing
	if (isdigit(buff[0])) {
		return INT;
	}

	if (isalpha(buff[0]) && !(is_quote(lbuff_char))) {
		return ID;
	}

	return UNKNOWN;
}

/*
 * todo: location, src file name output "token file_name:row:colm"
 */
static char *s_next()
{
	char c = 0;
	short it = 0;
	char buf[CAP] = {0};
	s_set_global_loc();

	while ( (c = fgetc(file_pointer)) != EOF ) {
		temp_location.col++;
		if (is_punct(c)) {
			if (it > 0) {
				ungetc(c, file_pointer);
				temp_location.col--;
				break;
			}
	
			return strdup(&c);
		}
		// clang -fsyntax-only -Xclang -dump-tokens
		if (!isspace(c)) {
			// NOTE (#1): Buufffer overflow if the size of the token is more than (255)
			buf[it++] = c;
			continue;
		}

		// if not a valid token continue
		if(!(*buf))
			continue;

		// if space exit out of the loop
		if (c == '\n') {
			temp_location.row += 1;
			temp_location.col  = 1;
		}

		break;
	}

	if (c == EOF)
		return NULL;

	char *value = malloc(strlen(buf) + 1);
	strcpy(value, buf);
	return value;
}

static void s_set_global_loc()
{
	current_location.row = temp_location.row;
	current_location.col = temp_location.col;
}

int is_quote(char c)
{
	return (c == '\"') || (c == '\'');
}

int is_punct(char c)
{
	return (ispunct(c) && !is_quote(c));
}

void set_file_pointer(char *file)
{
	file_pointer = fopen(file, "r");
	if (!file_pointer) {
		perror(file);
		exit(1);
	}
}

char *get_type_name(TokenType t)
{
	return Type_as_cstr[t];
}

// make file name global variable.
char *get_file_name()
{
	// NOTE (#2): This func gets the abs path, but we want the file name only..
	int     fd = fileno(file_pointer);
	char    fd_path[PATH_MAX], *filename = malloc(PATH_MAX);
	ssize_t n;

	sprintf(fd_path, "/proc/self/fd/%d", fd);
	n = readlink(fd_path, filename, PATH_MAX);

	if (n < 0)
		return NULL;

	filename[n] = '\0';
	return filename;
}

static void s_warning(char *error, char *token_value)
{
	char *file_name = get_file_name();

	fprintf(stderr, "%s:%ld:%ld %s String literal %s\n", (file_name), 
		 current_location.row, 
		 current_location.col, 
		 error, 
		 token_value
	);

	free(file_name);
}
