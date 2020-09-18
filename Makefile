CC = gcc
CCFLAGS = -Wall -Wextra -pedantic -O3

PREFIX = 

all: bin/echo bin/cat bin/false\
     bin/seq  bin/tee bin/true

bin:
	mkdir bin

bin/cat: cat/cat.c bin
	$(CC) $(CCFLAGS) -o $@ $<

bin/echo: echo/echo.c bin
	$(CC) $(CCFLAGS) -o $@ $<

bin/false: false/false.c bin
	$(CC) $(CCFLAGS) -o $@ $<

bin/seq: seq/seq.c bin
	$(CC) $(CCFLAGS) -o $@ $<

bin/tee: tee/tee.c bin
	$(CC) $(CCFLAGS) -o $@ $<

bin/true: true/true.c bin
	$(CC) $(CCFLAGS) -o $@ $<

install: $(BINARY)
	cp bin/* $(PREFIX)/bin/

.PHONY: all install
