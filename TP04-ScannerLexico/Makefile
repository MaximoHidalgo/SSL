SHELL = sh
CC = gcc

all: main

main: Scanner.o parser.o main.o
	$(CC) -o main Scanner.o parser.o main.o

Scanner.o: Scanner.c Scanner.h
	$(CC) -c Scanner.c

parser.o: parser.c Scanner.h
	$(CC) -c parser.c

main.o: main.c Scanner.h
	$(CC) -c main.c

clean:
	rm -f *.o main
	rm -f *.txt

run: main
	./main < codigo.c > declaracionesLN.txt