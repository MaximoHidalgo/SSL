CC = gcc

all: scannerTest

scannerTest: Scanner.o ScannerTest.o
	$(CC) -o scannerTest Scanner.o ScannerTest.o

Scanner.o: Scanner.c Scanner.h
	$(CC) -c Scanner.c

ScannerTest.o: ScannerTest.c Scanner.h
	$(CC) -c ScannerTest.c

clean:
	rm -f *.o scannerTest

run: scannerTest
	./scannerTest