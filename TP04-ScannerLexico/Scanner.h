#ifndef SCANNER_H
#define SCANNER_H
#include <stdio.h>
#include <stdlib.h>

#define LEXEMA_MAX 128

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
    TokenType type; // 0 1 2 3 4 5 6 7
    char lexema[LEXEMA_MAX]; //int x ; 
} Token;

Token GetNextToken (FILE*fp);
void parser(FILE *file);
const char* nombreToken(TokenType nombreToken);


#endif