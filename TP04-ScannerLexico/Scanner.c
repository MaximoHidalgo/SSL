#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Scanner.h"

// Un analizador léxico que reconoce identificadores de tipo, 
//números, punctuadores y operadores:

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

Token GetNextToken(FILE *fp){

    Token tokenLeido;
    int c;

    do{c = fgetc(fp);} while (c != EOF && esEspacio(c));

    if (c == EOF){
        tokenLeido.type = ENDFILE_TOKEN;
        strcpy(tokenLeido.lexema, "EOF");
        return tokenLeido;
    }

    if (esLetra(c)){
        int i = 0;
        tokenLeido.lexema[i++] = c;
        while ((c = fgetc(fp)) != EOF && esAlfanumerico(c)){
            tokenLeido.lexema[i++] = c;
        }
        tokenLeido.lexema[i] = '\0';
        if (c != EOF) ungetc(c, fp);

            // consume identificador
        if (strcmp(tokenLeido.lexema, "int") == 0 ||
            strcmp(tokenLeido.lexema, "char") == 0 ||
            strcmp(tokenLeido.lexema, "void") == 0 ||
            strcmp(tokenLeido.lexema, "double") == 0 ||
            strcmp(tokenLeido.lexema, "float") == 0){
            tokenLeido.type = KEYWORD;
        } else{
                tokenLeido.type = IDENTIFICADOR;
            }
            return tokenLeido;
        }

    if (esNumero(c)){
        int i = 0;
        tokenLeido.lexema[i++] = c;
        while (((c = fgetc(fp)) != EOF) && esNumero(c)){
            tokenLeido.lexema[i++] = c;
        }
        tokenLeido.lexema[i] = '\0';
        // consume número
        if (c != EOF) ungetc(c, fp);
        tokenLeido.type = LITERAL_NUMERICO;
        return tokenLeido;
    }

    switch(c) {
        case ';':
            tokenLeido.type = PUNCTUATOR;
            strcpy(tokenLeido.lexema, ";");
            return tokenLeido;
        case '(':
            tokenLeido.type = OPERADORES;
            strcpy(tokenLeido.lexema, "(");
            return tokenLeido;
        case ')':
            tokenLeido.type = OPERADORES;
            strcpy(tokenLeido.lexema, ")");
            return tokenLeido;
        case '[':
            tokenLeido.type = OPERADORES;
            strcpy(tokenLeido.lexema, "[");
            return tokenLeido;
        case ']':
            tokenLeido.type = OPERADORES;
            strcpy(tokenLeido.lexema, "]");
            return tokenLeido;
        case '*':
            tokenLeido.type = OPERADORES;
            strcpy(tokenLeido.lexema, "*");
            return tokenLeido;

        default:
            tokenLeido.type = PUNCTUATOR;
            strcpy(tokenLeido.lexema, "desconocido");
            return tokenLeido;
    }
    //return tokenLeido;
}