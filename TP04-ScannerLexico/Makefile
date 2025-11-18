SHELL = sh
CC = gcc

all: main main2

main: Scanner.o parser.o main.o
	$(CC) -o main Scanner.o parser.o main.o

Scanner.o: Scanner.c Scanner.h
	$(CC) -c Scanner.c

parser.o: parser.c Scanner.h
	$(CC) -c parser.c

main.o: main.c Scanner.h
	$(CC) -c main.c

clean:
	rm -f *.o main main2
	rm -f *.txt

run: main
	./main < codigo.c > declaracionesLN.txt

# --- Versión 2 (la de parserVer2.c) ---
main2: parserVer2.c
	$(CC) -o main2 parserVer2.c

# crea un archivo de salida diferente
run2: main2
	./main2 < codigo.c > declaracionesLNVersion2.txt
