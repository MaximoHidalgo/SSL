SHELL = sh
CC = gcc

all: scannerTest

scannerTest: Scanner.o parser.o ScannerTest.o
	$(CC) -o scannerTest Scanner.o parser.o ScannerTest.o

Scanner.o: Scanner.c Scanner.h
	$(CC) -c Scanner.c

parser.o: parser.c Scanner.h
	$(CC) -c parser.c

ScannerTest.o: ScannerTest.c Scanner.h
	$(CC) -c ScannerTest.c

clean:
	rm -f *.o scannerTest

run: scannerTest
	./scannerTest < codigo.txt