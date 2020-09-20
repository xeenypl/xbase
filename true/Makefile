CC = gcc
CCFLAGS = -Wall -Wextra -pedantic -O3

PREFIX = 

true: true.c
	$(CC) $(CCFLAGS) -o $@ $<

install: true
	cp true $(PREFIX)/bin

.PHONY: install
