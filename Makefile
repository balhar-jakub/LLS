CC=g++
CFLAGS=-c -Wall -g -O0
LINKFLAGS=-lcunit -o
HEADER_BASIC=src/types.h src/codes.h

files.o: src/files.c src/files.h $(HEADER_BASIC)
	$(CC) $(CFLAGS) src/files.c

memory.o: src/memory.h src/memory.c $(HEADER_BASIC)
	$(CC) $(CFLAGS) src/memory.c

matrix.o: src/matrix.h src/matrix.c $(HEADER_BASIC)
	$(CC) $(CFLAGS) src/matrix.c

parameters.o: src/parameters.h src/parameters.c $(HEADER_BASIC)
	$(CC) $(CFLAGS) src/parameters.c

print.o: src/print.h src/print.c $(HEADER_BASIC)
	$(CC) $(CFLAGS) src/print.c

gem.o: src/gem.h src/gem.c $(HEADER_BASIC) print.o
	$(CC) $(CFLAGS) src/gem.c

test_files.o: test/test_files.c
	$(CC) $(CFLAGS) test/test_files.c

test_matrix.o: test/test_matrix.c
	$(CC) $(CFLAGS) test/test_matrix.c

test_parameters.o: test/test_parameters.c
	$(CC) $(CFLAGS) test/test_parameters.c

test_gem.o: test/test_gem.c
	$(CC) $(CFLAGS) test/test_gem.c


test_files: files.o memory.o test_files.o
	$(CC) memory.o files.o test_files.o $(LINKFLAGS) test_files

test_matrix: matrix.o memory.o test_matrix.o
	$(CC) memory.o matrix.o test_matrix.o $(LINKFLAGS) test_matrix

test_parameters: parameters.o test_parameters.o 
	$(CC) parameters.o test_parameters.o $(LINKFLAGS) test_parameters

test_gem: memory.o gem.o print.o test_gem.o
	$(CC) memory.o gem.o print.o test_gem.o $(LINKFLAGS) test_gem

all: build test

build: files.o memory.o matrix.o test_files.o test_matrix.o

test: test_files test_matrix test_parameters test_gem
	valgrind --leak-check=full ./test_files
	valgrind --leak-check=full ./test_matrix
	valgrind --leak-check=full ./test_parameters
	valgrind --leak-check=full ./test_gem

clean: 
	rm -rf *o files test_files
	rm test*