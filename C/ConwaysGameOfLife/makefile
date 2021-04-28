CC = gcc
CFLAGS = -ansi 
DEPS = functions.h
OBJ = main.o functions.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

conway: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

