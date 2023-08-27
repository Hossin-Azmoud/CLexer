CC=gcc
INCLUDE=
CFLAGS=-Wall -pedantic -Werror -g -ggdb -Wextra -std=c11

all: main

main: *.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^
run:
	./main
clean:
	rm main
