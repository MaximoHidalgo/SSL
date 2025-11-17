#ifndef SCANNER_H
#define SCANNER_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define LEXEMA_MAX 128

typedef enum TokenType{
    KEYWORD,
    IDENTIFICADOR,
    ESPACIO,
    LITERAL_NUMERICO,
    OPERADORES,
    PUNCTUATOR,
} TokenType;

int main_parser_loop(void);

typedef struct Token {
    TokenType type; // 0 1 2 3 4 5 6 7
    char lexema[LEXEMA_MAX]; //int x ; 
} Token;

typedef enum {T_BASE, T_PUNTERO, T_ARREGLO, T_FUNCION} TipoNodo;


typedef struct NodoTipo {
    TipoNodo tipo;
    int dimensiones;          // para arrays
    struct NodoTipo* sig;     // para la lista de punteros/arrays/funciones
    char parametros[256];     // lista de parámetros si es función
} NodoTipo;


extern const char* TokenTypeNames[];


bool GetNextToken(Token* tokenLeido);

void parser();
const char* nombreToken(TokenType nombreToken);


#endif