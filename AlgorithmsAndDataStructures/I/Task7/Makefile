CC = g++
CFLAGS = -Wall -std=c++11
OBJECTS = main.o
HFILES = $(patsubst %.o,%.h,$(OBJECTS))
TARGET = main.out

%.o : %.cpp $(HFILES) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBS) $(OBJECTS) -o $(TARGET)

.PHONY : clean

clean :
	$(RM) $(TARGET) *.o core