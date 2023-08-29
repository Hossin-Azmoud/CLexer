# Desc
- Lexical analysis in C and that is all to it.


# Quick Start

- Compile
```console
   $ git clone https://github.com/Hossin-Azmoud/CLexer
   $ cd CLexer
   $ cd src
   $ make
```
- run
```console
   $ ./Clexer <file_path>
```
# Lexer Usage
- Token By Token
```c
#include "Clexer.h"
int main()
{
    // (#1): Get a new lexer to iterate.
    LEXER *lx = open_lexer("file.txt");
    Token t   = NULL;
 
    // (#2): iterate token by token until next returns NULL.
    while ((t = next(lx))) {
        // (#) Parse the tokens.
        free(t->value);
        free(t);
    }

    // (#3): frees the lexer and closes the file.
    close_lexer();
}
```

# NOTE
- It is not finished yet..
