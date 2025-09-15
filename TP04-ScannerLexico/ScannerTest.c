#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Scanner.h"


static const char* nombreToken(TokenType nombreToken) {
    switch (nombreToken) {
        case KEYWORD: return "KEYWORD";
        case IDENTIFICADOR: return "IDENTIFICADOR";
        case ESPACIO: return "ESPACIO";
        case LITERAL_NUMERICO: return "LITERAL_NUMERICO";
        case OPERADORES: return "OPERADORES";
        case PUNCTUATOR: return "PUNCTUATOR";
        case ENDFILE_TOKEN: return "ENDFILE_TOKEN";
        default: return "???";
    }
}

int main() {
    FILE* fp = fopen("codigo.txt", "r");
    if(fp == NULL){
        perror("Error al abrir el archivo");
        return 1;
    }

    Token token;
    do {
        token = GetNextToken(fp);
        if (token.type == ENDFILE_TOKEN) break;

        if (token.type != ESPACIO)
            printf("%-16s '%s'\n", nombreToken(token.type), token.lexema);
    } while (1);
    if (fp != stdin) fclose(fp);

    return 0;
}
