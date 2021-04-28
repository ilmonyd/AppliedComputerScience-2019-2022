# # # #===================================================
# # # #			Przykładowy plik Makefile
# # # #===================================================

# Makefile
# Kompilator g++.
CC = g++
# Mozliwe dodatkowe zmienne
# LIBS = -ll -lm
LIBS =
CFLAGS = -Wall -std=c++11
# Pliki obiektowe.
OBJECTS = main.o
# Pliki naglowkowe.
HFILES = $(patsubst %.o,%.h,$(OBJECTS))
# Koncowy plik wykonywalny.
TARGET = main.out

%.o : %.cpp $(HFILES) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBS) $(OBJECTS) -o $(TARGET)

# Okreslenie celow sztucznych.
.PHONY : clean
clean :
	$(RM) $(TARGET) *.o core