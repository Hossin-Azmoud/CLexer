#include <core.h>

int is_punct(char c)
{
	return (ispunct(c) && !IS_QUOTE(c));
}
