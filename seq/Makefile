BINARY = seq
SOURCE = seq.c

CC = gcc
CCFLAGS = -Wall -Wextra -pedantic -O3

PREFIX = 

all: $(BINARY)

$(BINARY): $(SOURCE)
	$(CC) $(CCFLAGS) -o $(BINARY) $(SOURCE)

install: $(BINARY)
	cp $(BINARY) $(PREFIX)/bin/

uninstall:
	rm $(PREFIX)/bin/$(BINARY)

.PHONY: all
