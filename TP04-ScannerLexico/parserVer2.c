#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*
CON EL FIN DE BUSCAR UNA ESTRUCTURA MAS SIMILAR AL BNF, SE CREA
ESTA SEGUNDA VERSION DEL PARSER, QUE TIENE CARACTERISTICAS DIFERENTES
PERO EN GENERAL REALIZA LA MISMA FUNCION QUE LA PRIMERA VERSION.

translation-unit :
        declaration
        translation-unit  declaration

declaration :
        name dcl ';'

dcl :
        optional *'s  direct-dcl

direct-dcl :
        name
        ( dcl )
        direct-dcl()
        direct-dcl[ optional size ]
 */


enum { NAME, PARENS, BRACKETS, NUMBER, TYPE };

// Variables globales
char token[100];
int tokentype;
char name[100];
char datatype[100];
char out[1000];

// Prototipos
int getNextToken(void);
void dcl(void);
void dirdcl(void);
int parserVer2(void);

int main() {
    parserVer2();
    return 0;
}

int parserVer2() {
    while (getNextToken() != EOF) {
        
        while (tokentype == '\n' || tokentype == ';') {
            if (tokentype == EOF) return 0;
            tokentype = getNextToken();
        }

        if (tokentype != TYPE) {
            printf("error: se esperaba un tipo (encontrado: '%s')\n", token);

            while (tokentype != ';' && tokentype != EOF)
                tokentype = getNextToken();
            continue;
        }

        strcpy(datatype, token);
        out[0] = '\0';
        
        dcl(); 

        if (tokentype != ';') {
            printf("error: falta ';', se encontró '%s'\n", token);

            while (tokentype != ';' && tokentype != EOF)
                tokentype = getNextToken();
        }

        char type_es[20];
        if (!strcmp(datatype, "int")) strcpy(type_es, "entero");
        else if (!strcmp(datatype, "char")) strcpy(type_es, "caracter");
        else if (!strcmp(datatype, "float")) strcpy(type_es, "flotante");
        else if (!strcmp(datatype, "double")) strcpy(type_es, "doble");
        else if (!strcmp(datatype, "void")) strcpy(type_es, "void");
        else strcpy(type_es, datatype);

        printf("%s es%s %s\n", name, out, type_es);
    }
    return 0;
}

void dcl() {
    int ns = 0; // 1. Contador de punteros ('*')

    while ((tokentype = getNextToken()) == '*')
        ns++;

    // 2. Llamar a dirdcl.
    dirdcl();

    // 3. Añadir "puntero a" al final por cada '*' contado
    while (ns-- > 0)
        strcat(out, " puntero a");
}

void dirdcl() {
    if (tokentype == '(') { 
        dcl();
        if (tokentype != ')')
            printf("error: falta ')'\n");
    } else if (tokentype == NAME) { 
        strcpy(name, token);
    } else {
        printf("error: se esperaba nombre o (dcl)\n");
        return;
    }

    // Bucle para sufijos: () o []
    while ((tokentype = getNextToken()) == PARENS || tokentype == BRACKETS) {
        if (tokentype == PARENS)
            strcat(out, " funcion que no recibe parametros y retorna");
        else { // BRACKETS
            strcat(out, " arreglo");
            strcat(out, token);
            strcat(out, " de");
        }
    }
}

int getNextToken() {
    int c;
    char *p = token;

    while ((c = getchar()) == ' ' || c == '\t')
        ;

    if (c == '(') {
        if ((c = getchar()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        ungetc(c, stdin);
        return tokentype = '('; 
    }

    if (c == '[') {
        *p++ = c;
        while ((*p++ = getchar()) != ']')
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    }

    if (isalpha(c)) {
        *p++ = c;
        while (isalnum(c = getchar()))
            *p++ = c;
        *p = '\0';
        ungetc(c, stdin);

        if (!strcmp(token, "int") ||
            !strcmp(token, "float") ||
            !strcmp(token, "double") ||
            !strcmp(token, "char") ||
            !strcmp(token, "void"))
            return tokentype = TYPE;

        return tokentype = NAME; 
    }

    if (isdigit(c)) {
        *p++ = c;
        while (isdigit(c = getchar()))
            *p++ = c;
        *p = '\0';
        ungetc(c, stdin);
        return tokentype = NUMBER;
    }

    if (c == '\n') {
        return getNextToken();
    }

    return tokentype = c;
}