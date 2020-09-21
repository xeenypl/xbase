CC = gcc
CCFLAGS = -Wall -Wextra -pedantic -O3

PREFIX = 

mv: mv.c
	$(CC) $(CCFLAGS) -o $@ $<

install: mv
	cp mv $(PREFIX)/bin

.PHONY: install
