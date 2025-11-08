#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Scanner.h"

//Variables globales del parser
static Token tokenActual;
static FILE *source = NULL;

//Prototipos de funciones internas
static void declaracion();
static void tipo();
static void resto();
static void match(TokenType esperado);
static void errorSintactico(const char *esperado);

// --- Implementación ---

void parser(FILE *file) {
    source = file;
    tokenActual = GetNextToken(source);

    while (tokenActual.type != ENDFILE_TOKEN) {
        declaracion();
        tokenActual = GetNextToken(source);
    }
    printf("Análisis sintáctico completado correctamente ✅\n");
}

void declaracion() {
    tipo();

    if (tokenActual.type == IDENTIFICADOR) {
        match(IDENTIFICADOR);
    } else {
        errorSintactico("identificador");
    }

    resto();

    if (tokenActual.type == PUNCTUATOR && strcmp(tokenActual.lexema, ";") == 0) {
        match(PUNCTUATOR);
    }
    else{
        errorSintactico("';'");
    }
}


static void tipo() {
    if (tokenActual.type != KEYWORD) {
        errorSintactico("tipo de dato (int, char, float, double, void)");
        return;
    }

    switch (tokenActual.lexema[0]) {
        case 1:  // int
            if (strcmp(tokenActual.lexema, "int") == 0) {
                match(KEYWORD);
                break;
            }
            errorSintactico("tipo 'int'");
            break;

        case 2:  // char
            if (strcmp(tokenActual.lexema, "char") == 0) {
                match(KEYWORD);
                break;
            }
            errorSintactico("tipo 'char'");
            break;

        case 3:  // float
            if (strcmp(tokenActual.lexema, "float") == 0) {
                match(KEYWORD);
                break;
            }
            errorSintactico("tipo 'float'");
            break;

        case 4:  // double
            if (strcmp(tokenActual.lexema, "double") == 0) {
                match(KEYWORD);
                break;
            }
            errorSintactico("tipo 'double'");
            break;

        case 5:  // void
            if (strcmp(tokenActual.lexema, "void") == 0) {
                match(KEYWORD);
                break;
            }
            errorSintactico("tipo 'void'");
            break;

        default:
            errorSintactico("caso default switch");
            break;
    }
}

void resto() {
    if (tokenActual.type == OPERADORES && strcmp(tokenActual.lexema, "[") == 0) {
        match(OPERADORES);
        if (tokenActual.type == LITERAL_NUMERICO)
            match(LITERAL_NUMERICO);
        else
            errorSintactico("número");
            
        if (tokenActual.type == OPERADORES && strcmp(tokenActual.lexema, "]") == 0)
            match(OPERADORES);
        else
            errorSintactico("']'");
    }
    // si no hay [, es vacío (epsilon)
}

void match(TokenType esperado) {
    tokenActual = GetNextToken(source);
}

void errorSintactico(const char *esperado) {
    fprintf(stderr, "Error sintactico: se esperaba %s, se encontro '%s'\n",
            esperado, tokenActual.lexema);
    exit(EXIT_FAILURE);
}
