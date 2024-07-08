CC=g++
CFLAGS=-Wall -std=c++17
BINS=huffman_lineal modulo.o
all: clean modulo.o
	$(CC) $(CFLAGS) -o huffman_lineal huffman_lineal.cpp modulo.o

modulo.o: modulo.cpp
	$(CC) $(CFLAGS) -c modulo.cpp

clean:
	@echo " [CLN] Removing binary files"
	@rm -f $(BINS)
