#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Scanner.h"



int esLetra(int c);
int esNumero(int c);
int esAlfanumerico(int c);
int esEspacio(int c);
int esKeyword(const char* token);

bool GetNextToken(Token* tokenLeido){
    tokenLeido->lexema[0] = '\0';
    int c;

    // saltar espacion si hay
    do{c = getchar();} while (c != EOF && esEspacio(c));

    if (c == EOF){ 
        return false;
    }

    if (esLetra(c)){
        int i = 0;
        tokenLeido->lexema[i++] = (char)c; // tokenLeido->lexema[0] = c; y i++ dsp

        while ((c = getchar()) != EOF && esAlfanumerico(c)){
            if (i < LEXEMA_MAX-1) tokenLeido->lexema[i++] = (char)c;
            else fprintf(stderr, "Advertencia: token demasiado largo, truncado\n");
        }
        tokenLeido->lexema[i] = '\0';
        if (c != EOF) ungetc(c, stdin);

        if (esKeyword(tokenLeido->lexema)) {
            tokenLeido->type = KEYWORD;
        } else {
            tokenLeido->type = IDENTIFICADOR;
        }
        return true;
    }

    if (esNumero(c)){ 
        int i = 0;
        if (i < LEXEMA_MAX-1) tokenLeido->lexema[i++] = (char)c;

        while ((c = getchar()) != EOF && esNumero(c)){
            if (i < LEXEMA_MAX-1) tokenLeido->lexema[i++] = (char)c;
        }
        tokenLeido->lexema[i] = '\0';

        if (esLetra(c)) {
            fprintf(stderr, "Error lexico: numero seguido de letra, teniamos: %s y llego '%c'\n",tokenLeido->lexema, c);
            while ((c = getchar()) != EOF && esAlfanumerico(c)); // consumo resto del identificador corrupto y roto
            if (c != EOF) ungetc(c, stdin);
            return false;
        }
        if (c != EOF) ungetc(c, stdin); // no vino letra vino otra cosa 
        tokenLeido->type = LITERAL_NUMERICO;
        return true;
    }

    switch (c) { // OPERADORES Y PUNRUACTORS
        case ';': // char es un numero difrazado
        case '(':
        case ')':
        case '[':
        case ']':
        {
            tokenLeido->type = PUNCTUATOR;
            tokenLeido->lexema[0] = (char)c;
            tokenLeido->lexema[1] = '\0';
            return true;
        }
        case '*':
        {
            tokenLeido->type = OPERADORES;
            tokenLeido->lexema[0] = (char)c; // 
            tokenLeido->lexema[1] = '\0';
            return true;
        }
        default:
        {
            fprintf(stderr, "Error lexico: caracter inesperado '%c'\n", c);
            return false;
        }
    }
}

// Retorna true si es letra (A-Z o a-z)
int esLetra(int c){
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_'));
}

// Retorna true si es dígito (0-9)
int esNumero(int c){
    return (c >= '0' && c <= '9');
}

// Retorna true si es alfanumérico (letra o dígito o guion bajo)
int esAlfanumerico(int c){
    return (esLetra(c) || esNumero(c));
}

// Retorna true si es un carácter de espacio en blanco
int esEspacio(int c){
    return (c == ' ' ||  // espacio
            c == '\t' || // tab horizontal
            c == '\n' || // salto de línea
            c == '\v' || // tab vertical
            c == '\f' || // avance de página
            c == '\r');  // retorno de carro
}

int esKeyword(const char* token){
    return strcmp(token,"int")==0 || strcmp(token,"char")==0 || strcmp(token,"void")==0 ||
           strcmp(token,"double")==0 || strcmp(token,"float")==0;
}

const char* TokenTypeNames[] = {"KEYWORD", "IDENTIFICADOR", "ESPACIO", "LITERAL_NUMERICO", "OPERADORES", "PUNCTUATOR"};