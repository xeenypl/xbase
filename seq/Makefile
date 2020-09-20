CC = gcc
CCFLAGS = -Wall -Wextra -pedantic -O3

PREFIX = 

seq: seq.c
	$(CC) $(CCFLAGS) -o $@ $<

install: seq
	cp seq $(PREFIX)/bin

.PHONY: install
