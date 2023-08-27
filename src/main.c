#include "Clexer.h"

int test();
int tokenize();

int main()
{
	return (tokenize());
}

int test()
{
	return (0);
}

int tokenize()
{
	Token *tok = NULL;

	set_file_pointer("src.txt");

	//tok = next();
	//printf("Token: %s\n", tok);

	while ((tok = next()))
	{
		printf("Token: %s\n", tok->value);
		printf("TokenType: %s\n",get_type_name(tok->type));
		free(tok);
	}

	return (0);
}
