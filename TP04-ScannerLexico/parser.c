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
NodoTipo* parseDeclarador();
void imprimirTipo(NodoTipo *tipo, const char *id, const char *tipoBase);

// --- Implementación ---

void parser(FILE *file) {
    source = file;
    tokenActual = GetNextToken(source);

    while (tokenActual.type != ENDFILE_TOKEN) {
        declaracion();
    }
    printf("\nAnalisis sintactico completado correctamente\n");
}

void declaracion() {
    char tipoDato[LEXEMA_MAX];
    char identificador[LEXEMA_MAX];
    char operador[LEXEMA_MAX];


    
    // Guardamos el tipo
    if (tokenActual.type == KEYWORD) {
        strcpy(tipoDato, tokenActual.lexema);
        match(KEYWORD);
    } else {
        errorSintactico("tipo de dato");
        return;
    } // int * dato;  int dato * ()

    NodoTipo* tipoComplejo = parseDeclarador();
    
    // Guardamos el identificador
    if (tokenActual.type == IDENTIFICADOR) {
        strcpy(identificador, tokenActual.lexema);
        match(IDENTIFICADOR);
    } else {
        errorSintactico("identificador");
        return;
    }

    resto(tipoDato, identificador);

    if (tokenActual.type == PUNCTUATOR && strcmp(tokenActual.lexema, ";") == 0){
        match(PUNCTUATOR);
    } else {
        errorSintactico("';'");
    }

    imprimirTipo(tipoComplejo, identificador, tipoDato);

    NodoTipo *aux;
    while(tipoComplejo){
        aux = tipoComplejo->sig;
        free(tipoComplejo);
        tipoComplejo = aux;
    }

}

void resto(const char *tipo, const char *identificador) {
    int punteros = 0;

    while (tokenActual.type == OPERADORES && strcmp(tokenActual.lexema, "*") == 0) {
        punteros++;
        matchLexema(OPERADORES, "*");
    }
    
    // Variable simple
    if (tokenActual.type == PUNCTUATOR && strcmp(tokenActual.lexema, ";") == 0) {
        printf("%s es un %s\n", identificador, traducirTipo(tipo)); //caso 1: tipo identificador punto-coma 
        return;
    }

    // Arreglo
    int arregloSize = 0;
    if (tokenActual.type == OPERADORES && strcmp(tokenActual.lexema, "[") == 0) {
        matchLexema(OPERADORES, "[");
        if (tokenActual.type == LITERAL_NUMERICO) {
            arregloSize = atoi(tokenActual.lexema);
            match(LITERAL_NUMERICO);
        }
        matchLexema(OPERADORES, "]");
    }

    // Función
    int esFuncion = 0;
    if (tokenActual.type == OPERADORES && strcmp(tokenActual.lexema, "(") == 0) {
        esFuncion = 1;
        matchLexema(OPERADORES, "(");

        // Ignorar parámetros por ahora (solo traducimos que es función)
        while (!(tokenActual.type == OPERADORES && strcmp(tokenActual.lexema, ")") == 0) &&
                tokenActual.type != ENDFILE_TOKEN) {
            tokenActual = GetNextToken(source);
        }

        matchLexema(OPERADORES, ")"); // cerrar paréntesis
    }


    // Imprimir traducción
    printf("%s es un ", identificador);
    
    // punteros
    for (int i = 0; i < punteros; i++) {
        printf("puntero a ");
    }

    // arreglos
    if (arregloSize > 0) {
        printf("arreglo de %d ", arregloSize);
    }

    // tipo o función
    if (esFuncion) {
        if (strcmp(tipo, "void") == 0) {
            printf("funcion que no retorna nada\n");
        } else {
            printf("funcion que retorna %s\n", traducirTipo(tipo));
        }
    } else {
        printf("%s\n", traducirTipo(tipo));
    }
}

// Traduce tipos de C a español
const char *traducirTipo(const char *tipo) {
    if (strcmp(tipo, "int") == 0) return "entero";
    if (strcmp(tipo, "double") == 0) return "double";
    if (strcmp(tipo, "float") == 0) return "float";
    if (strcmp(tipo, "char") == 0) return "caracter";
    if (strcmp(tipo, "void") == 0) return "void";
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
    fprintf(stderr, "Error sintactico: se esperaba %s, se encontro '%s', no se completa el analisis sintactico hasta que se corrija\n", esperado, tokenActual.lexema);
    exit(EXIT_FAILURE);
}


NodoTipo* parseDeclarador() {
    NodoTipo *raiz = NULL;
    NodoTipo *ultimo = NULL;


    // Leer Punteros
    while(tokenActual.type == OPERADORES && strcmp(tokenActual.lexema, "*") == 0){
        NodoTipo *n = malloc(sizeof(NodoTipo));
        n->tipo = T_PUNTERO;
        n->sig = NULL;
        if(!raiz) raiz = n; else ultimo->sig = n;
        ultimo = n;
        matchLexema(OPERADORES, "*");
    }

    // Parentesis
    if(tokenActual.type == OPERADORES && strcmp(tokenActual.lexema, "(") == 0){
        matchLexema(OPERADORES, "(");
        NodoTipo* dentroDelPatentesis = parseDeclarador();
        matchLexema(OPERADORES, ")");
        if(!raiz) return dentroDelPatentesis;

        NodoTipo *actual = raiz;
        while(actual->sig) actual = actual->sig;
        actual->sig = dentroDelPatentesis;
        return raiz;
    }

    // Arreglos
    NodoTipo *actual = raiz;
    while(tokenActual.type == OPERADORES){
        if(strcmp(tokenActual.lexema, "[") == 0){
            NodoTipo *n = malloc(sizeof(NodoTipo));
            n->tipo = T_ARREGLO;
            n->dimensiones = 0;
            n->sig = NULL;
            matchLexema(OPERADORES, "[");
            if(tokenActual.type == LITERAL_NUMERICO){
                n->dimensiones = atoi(tokenActual.lexema);
                match(LITERAL_NUMERICO);
            }
            matchLexema(OPERADORES, "]");

            if(!raiz) raiz = n;
            else {
                if (!actual) actual = raiz;
                while(actual->sig) actual = actual->sig;
                actual->sig = n;
            }
        } else if (strcmp(tokenActual.lexema, "(") == 0){
            NodoTipo *n = malloc(sizeof(NodoTipo));
            n->tipo = T_FUNCION;
            n->parametros[0] = '\0';
            n->sig = NULL;

            matchLexema(OPERADORES, "(");
            int primero = 1;
            while(tokenActual.type != OPERADORES || strcmp(tokenActual.lexema, ")") != 0) {
                if (!primero) strncat(n->parametros, ", ", sizeof(n->parametros) - strlen(n->parametros) - 1);
                primero = 0;
                if(tokenActual.type == KEYWORD) {
                    const char *tipoParametro = tokenActual.lexema;
                    match(KEYWORD);
                    if( tokenActual.type == IDENTIFICADOR) {
                        char aux[128];
                        snprintf(aux, sizeof(aux), "%s: %s", tokenActual.lexema, traducirTipo(tipoParametro));
                        strncat(n->parametros, aux, sizeof(n->parametros) - strlen(n->parametros) -1);
                        match(IDENTIFICADOR);
                    } else {
                          strncat(n->parametros, traducirTipo(tipoParametro), sizeof(n->parametros) - strlen(n->parametros) -1);
                    }
                }
                if (tokenActual.type == OPERADORES && strcmp(tokenActual.lexema, ",") == 0){
                    matchLexema(OPERADORES, ",");
                } else break;
                }
                matchLexema(OPERADORES, ")");

                if(!raiz) raiz = n;
                else{
                    if(!actual) actual = raiz;
                    while (actual->sig) actual = actual->sig;
                    actual->sig = n;
                }
            } else break;
        }

    return raiz;
}

void imprimirTipo(NodoTipo *tipo, const char *id, const char *tipoBase) {
    printf("%s es un ", id);
    NodoTipo* actual = tipo;
    while(actual) {
        switch (actual->tipo)
        {
        case T_PUNTERO: printf("puntero a "); break;
        case T_ARREGLO: printf("arreglo de %d elementos de ", actual->dimensiones); break;        
        case T_FUNCION: 
            if (actual->parametros[0] == '\0') 
                printf("funcion que no recibe parametros y devuelve");
            else
                printf("funcion que recibe (%s) y devuelve ", actual->parametros); 
            break;
        default: break;
        }
        actual = actual->sig;
    }
    printf("%s\n", traducirTipo(tipoBase));
}


