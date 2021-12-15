CC=gcc -g -Wall
CFILES=$(wildcard src/*/*.c)
HFILES=$(wildcard src/*/include/*.h)
OBJFILES=$(CFILES:.c=.o)
OBJPATH=src/objects/
EXEFILE=bin/main

all:$(OBJFILES)
	$(CC) $(OBJFILES) -o $(EXEFILE)

%.o: %.c $(HFILES)%.h
	$(CC) -c $(CFILES) $< -o $@

vim:
	nvim $(CFILES) src/constants/include/constants.h

run:
	$(EXEFILE)

debug:
	gdb -q $(EXEFILE)

memcheck:
	valgrind $(EXEFILE) --leak-check=full

git-update:
	git add README.md src/ Makefile
	git commit -m "update commit"
	git push origin main

clean:
	rm $(OBJFILES)
