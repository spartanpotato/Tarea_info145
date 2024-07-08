CC=g++
CFLAGS=-Wall -std=c++17
BINS=gap_coded_normal modulo.o
all: clean modulo.o
	$(CC) $(CFLAGS) -o gap_coded_normal gap_coded_normal.cpp modulo.o

modulo.o: modulo.cpp
	$(CC) $(CFLAGS) -c modulo.cpp

clean:
	@echo " [CLN] Removing binary files"
	@rm -f $(BINS)

