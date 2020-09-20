CC = gcc
CCFLAGS = -Wall -Wextra -pedantic -O3

PREFIX = 

mkdir: mkdir.c
	$(CC) $(CCFLAGS) -o $@ $<

install: mkdir
	cp mkdir $(PREFIX)/bin

.PHONY: install
