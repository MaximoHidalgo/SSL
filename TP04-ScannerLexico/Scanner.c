#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Scanner.h"

// Un analizador léxico que reconoce identificadores de tipo, 
//números, punctuadores y operadores:

int esLetra(int c);
int esNumero(int c);
int esAlfanumerico(int c);
int esEspacio(int c);
int esKeyword(const char* token);

Token GetNextToken(FILE *file){
    Token tokenLeido;
    tokenLeido.lexema[0] = '\0';
    int c;

    do{c = fgetc(file);} while (c != EOF && esEspacio(c));

    if (c == EOF){
        tokenLeido.type = ENDFILE_TOKEN;
        strcpy(tokenLeido.lexema, "EOF");
        return tokenLeido;
    }

    if (esLetra(c)){
        int i = 0;
        if (i < LEXEMA_MAX-1) tokenLeido.lexema[i++] = (char)c;

        while ((c = fgetc(file)) != EOF && esAlfanumerico(c)){
            if (i < LEXEMA_MAX-1) tokenLeido.lexema[i++] = (char)c;
        }
        tokenLeido.lexema[i] = '\0';
        if (c != EOF) ungetc(c, file);

        if (esKeyword(tokenLeido.lexema)) {
            tokenLeido.type = KEYWORD;
        } else {
            tokenLeido.type = IDENTIFICADOR;
        }
        return tokenLeido;
    }

    if (esNumero(c)){
        int i = 0;
        if (i < LEXEMA_MAX-1) tokenLeido.lexema[i++] = (char)c;

        while ((c = fgetc(file)) != EOF && esNumero(c)){
            if (i < LEXEMA_MAX-1) tokenLeido.lexema[i++] = (char)c;
        }
        tokenLeido.lexema[i] = '\0';
        // consume número
        if (c != EOF) ungetc(c, file);

        tokenLeido.type = LITERAL_NUMERICO;
        return tokenLeido;
    }

    switch (c) {
        case '*':
        case '(':
        case ')':
        case '[':
        case ']':
        {
            tokenLeido.type = OPERADORES;
            tokenLeido.lexema[0] = (char)c;
            tokenLeido.lexema[1] = '\0';
            return tokenLeido;
        }
        case ';':
        {
            tokenLeido.type = PUNCTUATOR;
            tokenLeido.lexema[0] = (char)c;
            tokenLeido.lexema[1] = '\0';
            return tokenLeido;
        }
        default:
        {
            tokenLeido.type = ERROR;
            tokenLeido.lexema[0] = (char)c;
            tokenLeido.lexema[1] = '\0';
            return tokenLeido;
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