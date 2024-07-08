CC=g++
CFLAGS=-Wall -std=c++17
BINS=explicita_lineal modulo.o
all: clean modulo.o
	$(CC) $(CFLAGS) -o explicita_lineal explicita_lineal.cpp modulo.o

modulo.o: modulo.cpp
	$(CC) $(CFLAGS) -c modulo.cpp

clean:
	@echo " [CLN] Removing binary files"
	@rm -f $(BINS)
