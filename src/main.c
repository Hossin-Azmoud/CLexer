#include "Clexer.h"

int main()
{
	char* tok = NULL;

	set_file_pointer("src.txt");

	//tok = next();
	//printf("Token: %s\n", tok);

	while ((tok = next()))
	{
		printf("Token: %s\n", tok);
		free(tok);
	}

	return (0);
}
