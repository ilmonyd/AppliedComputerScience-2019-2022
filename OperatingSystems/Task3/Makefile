CC = gcc
LD = $(CC)
CFLAGS = -Wall -std=c99 -pedantic
LFLAGS = -Wall -O

DIR = `basename $(CURDIR)`

NAME1 = a
NAME2 = b
NAME3 = c1
NAME4 = c2

EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x
EXEC4 = $(NAME4).x

OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o
OBJS4 = $(NAME4).o

AR = ar
ARFLAGS = rsv

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4)

$(EXEC1): $(OBJS1) 
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC3): $(OBJS3)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC4): $(OBJS4)
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: test_a
test_a: $(EXEC1)
	./$(EXEC1) custom 2

.PHONY: test_b
test_b: $(EXEC2)
	./$(EXEC2) custom 2

.PHONY: test_c
test_c: $(EXEC1) $(EXEC3) $(EXEC4)
	./$(EXEC3) default 2

.PHONY: clean
clean:
	rm -f *.o *~ *.a *.x

.PHONY: help
help:
	cat README

.PHONY: tar
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR))
