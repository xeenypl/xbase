CC = gcc
CCFLAGS = -Wall -Wextra -pedantic -O3

PREFIX = 

tee: tee.c
	$(CC) $(CCFLAGS) -o $@ $<

install: tee
	cp tee $(PREFIX)/bin

.PHONY: install
