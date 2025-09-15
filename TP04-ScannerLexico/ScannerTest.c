#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Scanner.h"

int main() {
    FILE* fp = fopen("codigo.txt", "r");
    if(fp == NULL){
        perror("Error al abrir el archivo");
        return 1;
    }

    Token token;
    token = GetNextToken(fp);
    while(token.type != ENDFILE_TOKEN ) {
        printf("Token: %-10s Tipo: %d\n", token.lexema, token.type);
        token = GetNextToken(fp);
    }
    return 0;
}


/*
int main()
{
    TokenType token;
    while ((token = getNextToken(FILE *)) != EOF){
        printf("Token: %d\n", token);
    }
    return 0;
}
*/