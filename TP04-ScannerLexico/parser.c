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
static void resto(const char *tipo, const char *identificador);
static void match(TokenType esperado);
static void matchLexema(TokenType esperado, const char *lexemaEsperado);
static void errorSintactico(const char *esperado);
static const char *traducirTipo(const char *tipo);

// --- Implementación ---

void parser(FILE *file) {
    source = file;
    tokenActual = GetNextToken(source);

    while (tokenActual.type != ENDFILE_TOKEN) {
        declaracion();
        tokenActual = GetNextToken(source);
    }
    printf("\nAnalisis sintactico completado correctamente\n");
}

void declaracion() {
    char tipoDato[LEXEMA_MAX];
    char identificador[LEXEMA_MAX];

    // Guardamos el tipo
    if (tokenActual.type == KEYWORD) {
        strcpy(tipoDato, tokenActual.lexema);
        match(KEYWORD);
    } else {
        errorSintactico("tipo de dato");
        return;
    }

    // Guardamos el identificador
    if (tokenActual.type == IDENTIFICADOR) {
        strcpy(identificador, tokenActual.lexema);
        match(IDENTIFICADOR);
    } else {
        errorSintactico("identificador");
        return;
    }

    // Analiza si es arreglo, función o variable simple
    resto(tipoDato, identificador);

    // Consume ;
    if (tokenActual.type == PUNCTUATOR && strcmp(tokenActual.lexema, ";") == 0) {
        match(PUNCTUATOR);
    } else {
        errorSintactico("';'");
    }
}

void resto(const char *tipo, const char *identificador) {
    // Variable simple
    if (tokenActual.type == PUNCTUATOR && strcmp(tokenActual.lexema, ";") == 0) {
        printf("%s es un %s\n", identificador, traducirTipo(tipo)); //caso 1: tipo identificador punto-coma 
        return;
    }

    // Arreglo
    if (tokenActual.type == OPERADORES && strcmp(tokenActual.lexema, "[") == 0) {
        matchLexema(OPERADORES, "[");
        char tamanio[LEXEMA_MAX] = "";
        if (tokenActual.type == LITERAL_NUMERICO) {
            strcpy(tamanio, tokenActual.lexema);
            match(LITERAL_NUMERICO);
        } else {
            errorSintactico("número");
        }
        matchLexema(OPERADORES, "]");
        printf("%s es un arreglo de %s elementos de tipo %s\n", identificador, tamanio, traducirTipo(tipo)); // caso 2: tipo identificador [tamanio] punto-coma 
        return;
    }

    // Función
    if (tokenActual.type == OPERADORES && strcmp(tokenActual.lexema, "(") == 0) {
        matchLexema(OPERADORES, "(");

        if (tokenActual.type == KEYWORD) {
            char tipoParametro[LEXEMA_MAX];
            strcpy(tipoParametro, tokenActual.lexema);
            match(KEYWORD);

            if (tokenActual.type == IDENTIFICADOR) {
                match(IDENTIFICADOR);
            }
        }

        if (tokenActual.type == OPERADORES && strcmp(tokenActual.lexema, ")") == 0) {
            matchLexema(OPERADORES, ")");
        } else {
            errorSintactico("')'");
        }

        printf("%s es una función que retorna %s\n",
               identificador, traducirTipo(tipo));
        return;
    }
}

// Traduce tipos de C a español
const char *traducirTipo(const char *tipo) {
    if (strcmp(tipo, "int") == 0) return "entero";
    if (strcmp(tipo, "double") == 0) return "double";
    if (strcmp(tipo, "float") == 0) return "float";
    if (strcmp(tipo, "char") == 0) return "caracter";
    if (strcmp(tipo, "void") == 0) return "nada";
    return tipo;
}

void match(TokenType esperado) {
    if (tokenActual.type == esperado) {
        tokenActual = GetNextToken(source);
    } else {
        errorSintactico("token inesperado");
    }
}

void matchLexema(TokenType esperado, const char *lexemaEsperado) {
    if (tokenActual.type == esperado && strcmp(tokenActual.lexema, lexemaEsperado) == 0) {
        tokenActual = GetNextToken(source);
    } else {
        char buf[256];
        snprintf(buf, sizeof(buf), "'%s'", lexemaEsperado);
        
        errorSintactico(buf);
    }
}

void errorSintactico(const char *esperado) {
    if ( strcmp(tokenActual.lexema, "EOF") == 0){
        printf("\nAnalisis sintactico completado correctamente\n");
        exit(EXIT_SUCCESS);
    }
    fprintf(stderr, "Error sintactico: se esperaba %s, se encontro '%s'\n", esperado, tokenActual.lexema);
    exit(EXIT_FAILURE);
}