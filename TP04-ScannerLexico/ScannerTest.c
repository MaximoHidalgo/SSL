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
        case ERROR: return "desconocido";
        default: return "???";
    }
}

int main() {
    FILE* file = fopen("codigo.txt", "r");
    if(file == NULL){
        perror("Error al abrir el archivo");
        return 1;
    }

    for (Token token = GetNextToken(file); token.type != ENDFILE_TOKEN; token = GetNextToken(file)) {
    if (token.type != ESPACIO)
        printf("%-16s '%s'\n", nombreToken(token.type), token.lexema);
    }
    if (file != stdin) fclose(file);
}
