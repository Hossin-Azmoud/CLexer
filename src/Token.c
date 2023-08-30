#include "Token.h"

char *get_type_name(TokenType t)
{
	// NOTE (#6): Made it local static so other functions can not access it but it is indeed initialized only once and has 
	// the life time of the whole program so we don't allocate and reallocate each time we call this function.
	static char *Type_as_cstr[TOKEN_TYPE_AMOUNT] = {
		"STR_LIT",
		"INT",
		"ID",
		"SYM",
		"UNKNOWN"
	};

	return Type_as_cstr[t];
}

