CC = gcc
LD = $(CC)
CFLAGS = -Wall -O -fPIC
LFLAGS = -Wall -O

DIR = `basename $(CURDIR)`

NAME1 = main
NAME2 = ex

EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x

OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o

AR = ar
ARFLAGS = rsv

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: all
all: $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: run
run: $(EXEC1) $(EXEC2)
	./$(EXEC1) ./$(EXEC2) $(EXEC2)

.PHONY: test
test: $(EXEC1)
	./$(EXEC1) /bin/ls ls

.PHONY: clean
clean:
	rm -f *.o *~ *.a *.x

.PHONY: help
help:
	cat README

.PHONY: tar
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR))
