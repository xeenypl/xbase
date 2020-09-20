CC = gcc
CCFLAGS = -Wall -Wextra -pedantic -O3

PREFIX = 

false: false.c
	$(CC) $(CCFLAGS) -o $@ $<

install: false
	cp false $(PREFIX)/bin

.PHONY: install
