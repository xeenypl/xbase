CC = gcc
CCFLAGS = -Wall -Wextra -pedantic -O3

PREFIX = 

cat: cat.c
	$(CC) $(CCFLAGS) -o $@ $<

install: cat
	cp cat $(PREFIX)/bin

.PHONY: install
