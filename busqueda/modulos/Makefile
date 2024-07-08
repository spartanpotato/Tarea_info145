CC=g++
CFLAGS=-Wall -std=c++17
BINS=arreglos modulo.o
all: clean modulo.o
	$(CC) $(CFLAGS) -o arreglos arreglos.cpp modulo.o

modulo.o: modulo.cpp
	$(CC) $(CFLAGS) -c modulo.cpp

clean:
	@echo " [CLN] Removing binary files"
	@rm -f $(BINS)
