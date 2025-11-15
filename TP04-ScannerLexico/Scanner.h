#ifndef SCANNER_H
#define SCANNER_H
#include <stdbool.h>
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
} TokenType;






typedef struct Token {
    TokenType type; // 0 1 2 3 4 5 6 7
    char lexema[LEXEMA_MAX]; //int x ; 
} Token;
/**/

typedef enum {T_BASE, T_PUNTERO, T_ARREGLO, T_FUNCION} TipoNodo;

typedef struct NodoTipo {
    TipoNodo tipo;
    int dimensiones;      // arreglos
    char parametros[256]; // funciones
    struct NodoTipo *sig; 
}NodoTipo;


extern const char* TokenTypeNames[];


bool GetNextToken(Token* tokenLeido);

void parser(FILE *file);
const char* nombreToken(TokenType nombreToken);


#endif