CC=gcc
INCLUDE=-I../include
CFLAGS=-Wall -pedantic -Werror -g -ggdb -Wextra -std=c11

all: main

main: *.c
	$(CC) $(CFLAGS) $(INCLUDE) -o main $^
run:
	./Clexer
clean:
	rm Clexer
