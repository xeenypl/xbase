CC = gcc
CCFLAGS = -Wall -Wextra -pedantic -O3

PREFIX = 

.PHONY: all
all: bin echo cat false seq tee true mkdir

bin:
	mkdir bin

.PHONY: echo
echo: bin/echo
bin/echo: echo/echo.c
	cd echo && make && cp echo ../bin/

.PHONY: cat
cat: bin/cat
bin/cat: cat/cat.c
	cd cat && make && cp cat ../bin/

.PHONY: false
false: bin/false
bin/false: false/false.c
	cd false && make && cp false ../bin/

.PHONY: seq
seq: bin/seq
bin/seq: seq/seq.c
	cd seq && make && cp seq ../bin/

.PHONY: tee
tee: bin/tee
bin/tee: tee/tee.c
	cd tee && make && cp tee ../bin/

.PHONY: true
true: bin/true
bin/true: true/true.c
	cd true && make && cp true ../bin/

.PHONY: mkdir
mkdir: bin/mkdir
bin/mkdir: mkdir/mkdir.c
	cd mkdir && make && cp mkdir ../bin/

.PHONY: install
install: all
	cp bin/* $(PREFIX)/bin/

