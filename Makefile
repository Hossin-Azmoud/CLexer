CC=gcc
OUTPUTDIR=./bin
INCLUDE=-I./include
CFLAGS=-Wall -pedantic -Werror -g -ggdb -Wextra -std=c11
SRC=./src/main.c ./libs/lexer/*.c ./libs/structures/*.c

all: main

main:
	$(CC) $(CFLAGS) $(INCLUDE) -o $(OUTPUTDIR)/main $(SRC)

run:
	$(OUTPUTDIR)/main

clean:
	rm $(OUTPUTDIR)/main
