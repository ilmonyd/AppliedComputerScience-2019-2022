CDFLAGS := -Wall -std=c99 -pedantic -c -pthread  -lrt
LDFLAGS := -Wall -std=c99 -pedantic -s -lm -pthread  -lrt
SFLAGS := -L. -lmysem
NAME1 = creator
NAME2 = process
NAME3 = mysem
NAME4 = libmysem
DIR = `basename $(CURDIR)`

.PHONY: run
run: compile start clean

compile: $(NAME4).a $(NAME2).x $(NAME1).x

%.x: %.o
	 $(CC)  $(LDFLAGS)  -o $@ $^ $(SFLAGS)

%.a: $(NAME3).o
	ar rv $(NAME4).a $(NAME3).o

%.o: %.c
	$(CC)  $(CDFLAGS) -o $@ $^

start:
	./$(NAME1).x ./$(NAME2).x 3 4

.PHONY: clean
clean:
	$(RM) *.o *.x *.a

.PHONY: tar
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR))
