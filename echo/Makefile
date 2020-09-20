CC = gcc
CCFLAGS = -Wall -Wextra -pedantic -O3

PREFIX = 

echo: echo.c
	$(CC) $(CCFLAGS) -o $@ $<

install: echo
	cp echo $(PREFIX)/bin

.PHONY: install
