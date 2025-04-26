CC = gcc
CFLAGS = -Iinclude -Wall

SRC = $(wildcard src/*.c)

%: %.c $(SRC)
	$(CC) $(CFLAGS) $^ -o $@
