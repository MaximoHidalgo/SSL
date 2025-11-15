#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Scanner.h"


const char* nombreToken(TokenType nombreToken) {
    switch (nombreToken) {
        case KEYWORD: return "KEYWORD";
        case IDENTIFICADOR: return "IDENTIFICADOR";
        case ESPACIO: return "ESPACIO";
        case LITERAL_NUMERICO: return "LITERAL_NUMERICO";
        case OPERADORES: return "OPERADORES";
        case PUNCTUATOR: return "PUNCTUATOR";
        default: return "???";
    }
}


void printToken(Token t){
    printf("TokenType: %s, Lexema: %s.\n",TokenTypeNames[t.type], t.lexema);
}

int main() {
   // FILE* file = fopen("codigo.txt", "r");
    //if(file == NULL){
    //    perror("Error al abrir el archivo");
    //    return 1;
    //}
        Token tk;
        while(GetNextToken(&tk)) printToken(tk);

    //parser(file);
   // if (file != stdin) fclose(file);
}


