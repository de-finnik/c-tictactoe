CC=gcc
CFLAGS=-o tictactoe -lncurses
SOURCES=$(wildcard src/*.c)

all:
	$(CC) $(SOURCES) $(CFLAGS)
