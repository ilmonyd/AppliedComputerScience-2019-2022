CC = gcc
LD = $(CC)
CFLAGS = -Wall -std=c99 -pedantic
LFLAGS = -Wall -O

FILE_IN = input.txt
FILE_OUT = output.txt
FIFO = fifo.fifo
PRODUCER= ./$(EXEC2) $(FILE_IN) $(FIFO)
CONSUMER= ./$(EXEC3) $(FILE_OUT) $(FIFO)

DIR = `basename $(CURDIR)`

NAME1 = main
NAME2 = producent
NAME3 = konsument

EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x

OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o

AR = ar
ARFLAGS = rsv

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3)

$(EXEC1): $(OBJS1) 
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC3): $(OBJS3)
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: run_a
run_a: $(EXEC1) $(EXEC2) $(EXEC3)
	./$(EXEC1) $(FILE_IN) $(FILE_OUT) $(FIFO)
	diff -s $(FILE_IN) $(FILE_OUT)

.PHONY: run_b
run_b: $(EXEC2) $(EXEC3)
	rm -f $(FIFO)
	mkfifo $(FIFO)
	xterm -hold -title PRODUCER -e $(PRODUCER) & xterm -hold -title CONSUMER -e $(CONSUMER)
	rm -f $(FIFO)
	diff -s $(FILE_IN) $(FILE_OUT)

.PHONY: clean
clean:
	rm -f *.o *~ *.a *.x output.txt fifo.fifo

.PHONY: help
help:
	cat README

.PHONY: tar
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR))
