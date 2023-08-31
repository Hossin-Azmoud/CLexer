#ifndef CORE_H
#define _GNU_SOURCE
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define CAP      1024
#define TOK_MAX  512
#define PATH_MAX 4096
#define NL '\n'
#define SQ '\''
#define DQ '\"'

#define PLUS_C  '+'
#define MINUS_C '-'
#define MUL_C   '*'
#define DIV_C   '/'

#define IS_QUOTE(c) (c == SQ || c == DQ)

int is_punct(char c);
#endif // CORE_H
