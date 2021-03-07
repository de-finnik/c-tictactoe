CC=gcc
CFLAGS=-o tictactoe
SOURCES=$(wildcard src/*.c)

all:
	$(CC) $(CFLAGS) $(SOURCES)
