CC = gcc
LD = $(CC)
CFLAGS = -Wall -std=c99 -pedantic
LFLAGS = -Wall -O

DIR = `basename $(CURDIR)`

NAME = a

EXEC = $(NAME).x

OBJS = $(NAME).o

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: all
all: $(EXEC)

$(EXEC): $(OBJS) 
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: run
run: $(EXEC) input.txt
	./$(EXEC) input.txt output.txt
	diff -s input.txt output.txt

.PHONY: clean
clean:
	rm -f *.o *~ *.a *.x output.txt

.PHONY: help
help:
	cat README

.PHONY: tar
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR))
