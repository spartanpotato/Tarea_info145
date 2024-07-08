CC=g++
CFLAGS=-Wall -std=c++17
BINS=huffman_normal modulo.o
all: clean modulo.o
	$(CC) $(CFLAGS) -o huffman_normal huffman_normal.cpp modulo.o

modulo.o: modulo.cpp
	$(CC) $(CFLAGS) -c modulo.cpp

clean:
	@echo " [CLN] Removing binary files"
	@rm -f $(BINS)