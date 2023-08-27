CC=gcc
INCLUDE=
CFLAGS=-Wall -pedantic -Werror -Wextra -std=c11

all: main

main: main.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^
run:
	./main
clean:
	rm main
