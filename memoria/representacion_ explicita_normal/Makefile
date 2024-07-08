CC=g++
CFLAGS=-Wall -std=c++17
BINS=explicita_normal modulo.o
all: clean modulo.o
	$(CC) $(CFLAGS) -o explicita_normal explicita_normal.cpp modulo.o

modulo.o: modulo.cpp
	$(CC) $(CFLAGS) -c modulo.cpp

clean:
	@echo " [CLN] Removing binary files"
	@rm -f $(BINS)
