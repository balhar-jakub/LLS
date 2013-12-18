CC=g++
CFLAGS=-c -Wall
HEADER_BASIC=src/types.h src/codes.h

files.o: src/files.c src/files.h $(HEADER_BASIC)
	$(CC) $(CFLAGS) src/files.c

test_files.o: test/test_files.c
	$(CC) $(CFLAGS) test/test_files.c

memory.o: src/memory.h src/memory.c $(HEADER_BASIC)
	$(CC) $(CFLAGS) src/memory.c

matrix.o: src/matrix.h src/matrix.c $(HEADER_BASIC)
	$(CC) $(CFLAGS) src/matrix.c

test_matrix.o: test/test_matrix.c
	$(CC) $(CFLAGS) test/test_matrix.c

test_files: files.o memory.o test_files.o
	$(CC) memory.o files.o test_files.o -lcunit -o test_files

test_matrix: matrix.o memory.o test_matrix.o
	$(CC) memory.o matrix.o test_matrix.o -lcunit -o test_matrix

all: build test

build: files.o memory.o test_files.o

test: test_files test_matrix
	valgrind --leak-check=yes ./test_files
	valgrind --leak-check=yes ./test_matrix

clean: 
	rm -rf *o files test_files