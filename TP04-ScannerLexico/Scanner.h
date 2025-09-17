#ifndef SCANNER_H
#define SCANNER_H
#include <stdio.h>
#include <stdlib.h>

typedef enum{
    KEYWORD,
    IDENTIFICADOR,
    ESPACIO,
    LITERAL_NUMERICO,
    OPERADORES,
    PUNCTUATOR,
    ENDFILE_TOKEN,
    ERROR,
} TokenType;

typedef struct {
    TokenType type; // 0 1 2 3 4 5 6
    char lexema[128]; //int x ; 
} Token;

Token GetNextToken (FILE*fp);
int esLetra(int c);
int esNumero(int c);
int esAlfanumerico(int c);
int esEspacio(int c);


#endif