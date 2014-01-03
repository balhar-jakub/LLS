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

print.o: src/print.hpp src/print.cpp $(HEADER_BASIC)
	$(CC) $(CFLAGS) src/print.cpp

gem.o: src/gem.h src/gem.c $(HEADER_BASIC) print.o
	$(CC) $(CFLAGS) src/gem.c

statistics.o: src/statistics.h src/statistics.c $(HEADER_BASIC)
	$(CC) $(CFLAGS) src/statistics.c

lls.o: src/lls.h src/lls.c $(HEADER_BASIC)
	$(CC) $(CFLAGS) src/lls.c

test_files.o: test/test_files.c
	$(CC) $(CFLAGS) test/test_files.c

test_matrix.o: test/test_matrix.c
	$(CC) $(CFLAGS) test/test_matrix.c

test_parameters.o: test/test_parameters.c
	$(CC) $(CFLAGS) test/test_parameters.c

test_gem.o: test/test_gem.c
	$(CC) $(CFLAGS) test/test_gem.c

test_lls.o: test/test_lls.c
	$(CC) $(CFLAGS) test/test_lls.c

test_files: files.o memory.o test_files.o
	$(CC) memory.o files.o test_files.o $(LINKFLAGS) test_files

test_matrix: matrix.o memory.o test_matrix.o
	$(CC) memory.o matrix.o test_matrix.o $(LINKFLAGS) test_matrix

test_parameters: parameters.o test_parameters.o 
	$(CC) parameters.o test_parameters.o $(LINKFLAGS) test_parameters

test_gem: memory.o gem.o print.o test_gem.o
	$(CC) memory.o gem.o print.o test_gem.o $(LINKFLAGS) test_gem

test_lls: memory.o gem.o lls.o print.o files.o statistics.o matrix.o parameters.o test_lls.o
	$(CC) memory.o gem.o lls.o print.o files.o statistics.o matrix.o parameters.o test_lls.o $(LINKFLAGS) test_lls

all: build test

build: memory.o gem.o lls.o print.o files.o matrix.o parameters.o statistics.o test_files.o test_matrix.o

test: test_files test_matrix test_parameters test_gem test_lls
	valgrind --leak-check=full ./test_files
	valgrind --leak-check=full ./test_matrix
	valgrind --leak-check=full ./test_parameters
	valgrind --leak-check=full ./test_gem
	valgrind --leak-check=full ./test_lls

test_lls_run: test_lls
	valgrind --leak-check=full --track-origins=yes ./test_lls

clean: 
	rm -rf *o files test_files
	rm test*