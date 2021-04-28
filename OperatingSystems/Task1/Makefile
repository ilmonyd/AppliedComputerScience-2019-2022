CC = gcc
LD = $(CC)
CFLAGS = -Wall -O -fPIC
LFLAGS = -Wall -O

DIR = `basename $(CURDIR)`

NAME1 = a
NAME2 = b
NAME3 = c
NAME4 = d
NAME5 = e

EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x
EXEC4 = $(NAME4).x
EXEC5 = $(NAME5).x

OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o
OBJS4 = $(NAME4).o
OBJS5 = $(NAME5).o

# LDLIBS = -lm

AR = ar
ARFLAGS = rsv

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5)

$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC3): $(OBJS3)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC4): $(OBJS4)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC5): $(OBJS5)
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: run_a run_b run_c run_d run_e
run_a: $(EXEC1)
	./$(EXEC1)
run_b: $(EXEC2)
	./$(EXEC2)
run_c: $(EXEC3)
	(./$(EXEC3);(pstree -p | egrep "systemd\(1\)|c.x"))
run_d: $(EXEC4)
	(./$(EXEC4); echo ""; echo "For the process ancestry tree read README.";)
run_e: $(EXEC5)
	./$(EXEC5)

.PHONY: clean
clean:
	rm -f *.o *~ *.a *.x

.PHONY: tar
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR))
