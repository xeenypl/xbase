CCFLAGS=-Wall -Wextra -pedantic -O3
PREFIX= 
ALL = true cat echo false mkdir mv seq tee sync pwd cp

.PHONY: all
all: $(ALL)

.PHONY: test
test:
	echo $(TEST)

.PHONY: clean
clean:
	rm $(ALL)

.PHONY: install
install: all
	cp $(ALL) $(PREFIX)/bin

true: true.c
	$(CC) $(CCFLAGS) -o $@ $<

.PHONY: install-true
install-true: true
	cp true $(PREFIX)/bin

cat: cat.c
	$(CC) $(CCFLAGS) -o $@ $<

.PHONY: install-cat
install-cat: cat
	cp cat $(PREFIX)/bin

echo: echo.c
	$(CC) $(CCFLAGS) -o $@ $<

.PHONY: install-echo
install-echo: echo
	cp echo $(PREFIX)/bin

false: false.c
	$(CC) $(CCFLAGS) -o $@ $<

.PHONY: install-false
install-false: false
	cp false $(PREFIX)/bin

mkdir: mkdir.c
	$(CC) $(CCFLAGS) -o $@ $<

.PHONY: install-mkdir
install-mkdir: mkdir
	cp mkdir $(PREFIX)/bin

mv: mv.c
	$(CC) $(CCFLAGS) -o $@ $<

.PHONY: install-mv
install-mv: mv
	cp mv $(PREFIX)/bin

seq: seq.c
	$(CC) $(CCFLAGS) -o $@ $<

.PHONY: install-seq
install-seq: seq
	cp seq $(PREFIX)/bin

tee: tee.c
	$(CC) $(CCFLAGS) -o $@ $<

.PHONY: install-tee
install-tee: tee
	cp tee $(PREFIX)/bin

sync: sync.c
	$(CC) $(CCFLAGS) -o $@ $<

.PHONY: install-sync
install-sync: sync
	cp sync $(PREFIX)/bin

pwd: pwd.c
	$(CC) $(CCFLAGS) -o $@ $<

.PHONY: install-pwd
install-pwd: pwd
	cp pwd $(PREFIX)/bin

cp: cp.c
	$(CC) $(CCFLAGS) -o $@ $<

.PHONY: install-cp
install-cp: cp
	cp cp $(PREFIX)/bin
