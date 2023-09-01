CC=gcc
OUTPUTDIR=./bin
INCLUDE=-I./include
CFLAGS=-Wall -pedantic -Werror -g -ggdb -Wextra -std=c11

all: main

main: ./src/*.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $(OUTPUTDIR)/main $^
run:
	$(OUTPUTDIR)/main
clean:
	rm $(OUTPUTDIR)/main
