#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Scanner.h"

static Token tokenActual;
static bool hayToken = false;


static void declaracion();
static void match(TokenType esperado);
static void matchLexema(TokenType esperado, const char* lexemaEsperado);
static void errorSintactico(const char* esperado);
static NodoTipo* parseDeclarador();
static NodoTipo* parsePostfijo();
static void imprimirTipo(NodoTipo* tipo, const char* id, const char* tipoBase);

const char* obtenerAliasTipo(const char* tipo);
//static void imprimirTipoRec(NodoTipo* tipo, const char* id, const char* tipoBase);
static void imprimirTipoRec(NodoTipo* n, const char* tipoBaseAlias) ;


/* Gramatica propuesta v1
    Declaracion:
    TipoBase Declarador ';'

TipoBase:
      int 
    | char 
    | float 
    | double 
    | void

Declarador:
      Punteros DeclaradorPostfijo
    | DeclaradorPostfijo      // Para casos sin *

Punteros:
      '*' 
    | '*' Punteros

DeclaradorPostfijo:
      Identificador Postfijo
    | '(' Declarador ')' Postfijo   // <-- necesario para (*pf)()

Postfijo:
      '[' LiteralNumerico ']' Postfijo     // Arreglo
    | '(' ListaParametrosOpt ')' Postfijo  // Función
    | ε

ListaParametrosOpt:
      ε
    | ListaParametros

ListaParametros:
      Parametro
    | Parametro ',' ListaParametros

Parametro:
      TipoBase Declarador    // <-- corregido: C permite int *p, int (*fp)(), etc.


*/




void parser() {
    hayToken = GetNextToken(&tokenActual);

    while (hayToken) {


        char tipoBase[64];
        if (tokenActual.type == KEYWORD) {
            strcpy(tipoBase, tokenActual.lexema);
            match(KEYWORD);
        } else {
            errorSintactico("tipo base");
        }


        NodoTipo* tipo = parseDeclarador();

        NodoTipo* aux = tipo;
        char nombreID[128] = "";
        while (aux && aux->tipo != T_BASE) aux = aux->sig;

        if (!aux || aux->parametros[0] == '\0') {
            errorSintactico("identificador");
        }

        strcpy(nombreID, aux->parametros);

        matchLexema(PUNCTUATOR, ";");

        


        imprimirTipo(tipo, nombreID, tipoBase);

        // liberar
        while (tipo) {
            NodoTipo* tmp = tipo->sig;
            free(tipo);
            tipo = tmp;
        }
    }
}



static NodoTipo* parseDeclarador() {

    ///punero
    if (tokenActual.type == OPERADORES && strcmp(tokenActual.lexema, "*") == 0) {
        matchLexema(OPERADORES, "*");

        NodoTipo* n = malloc(sizeof(NodoTipo));
        n->tipo = T_PUNTERO;
        n->dimensiones = 0;
        n->parametros[0] = '\0';

        n->sig = parseDeclarador();
        return n;
    }

    //(declarador)
    if (tokenActual.type == PUNCTUATOR && strcmp(tokenActual.lexema, "(") == 0) {
        matchLexema(PUNCTUATOR, "(");
        NodoTipo* dentro = parseDeclarador();
        matchLexema(PUNCTUATOR, ")");

        return parsePostfijo(dentro);
    }

    // identificador
    if (tokenActual.type == IDENTIFICADOR) {
        NodoTipo* idNode = malloc(sizeof(NodoTipo));
        idNode->tipo = T_BASE;
        idNode->dimensiones = 0;
        strcpy(idNode->parametros, tokenActual.lexema);
        idNode->sig = NULL;

        match(IDENTIFICADOR);

        return parsePostfijo(idNode);
    }

    errorSintactico("declarador");
    return NULL;
}


static NodoTipo* parsePostfijo(NodoTipo* base) {

    while (1) {

        //arreglo
        if (tokenActual.type == PUNCTUATOR && strcmp(tokenActual.lexema, "[") == 0) {

            matchLexema(PUNCTUATOR, "[");

            int dim = 0;
            if (tokenActual.type == LITERAL_NUMERICO) {
                dim = atoi(tokenActual.lexema);
                match(LITERAL_NUMERICO);
            }

            matchLexema(PUNCTUATOR, "]");

            NodoTipo* n = malloc(sizeof(NodoTipo));
            n->tipo = T_ARREGLO;
            n->dimensiones = dim;
            n->parametros[0] = '\0';
            n->sig = base;
            base = n;
            continue;
        }

        // funcion
        if (tokenActual.type == PUNCTUATOR && strcmp(tokenActual.lexema, "(") == 0) {

            matchLexema(PUNCTUATOR, "(");

            char params[256] = "";
            params[0] = '\0';

            if (!(tokenActual.type == PUNCTUATOR && strcmp(tokenActual.lexema, ")") == 0)) {

                while (1) {
                    // parametros
                    if (tokenActual.type != KEYWORD)
                        errorSintactico("tipo de parámetro");

                    char t[64];
                    strcpy(t, tokenActual.lexema);
                    match(KEYWORD);
                    parseDeclarador();

                    

                    char id[64] = "";
                    if (tokenActual.type == IDENTIFICADOR) {
                        strcpy(id, tokenActual.lexema);
                        match(IDENTIFICADOR);
                    }

                    char temp[128];
                    if (id[0])
                        snprintf(temp, sizeof(temp), "%s %s", t, id);
                    else
                        snprintf(temp, sizeof(temp), "%s", t);

                    if (params[0]) strcat(params, ", ");
                    strcat(params, temp);

                    if (tokenActual.type == PUNCTUATOR && strcmp(tokenActual.lexema, ",") == 0)
                        matchLexema(PUNCTUATOR, ",");
                    else
                        break;
                }
            }

            matchLexema(PUNCTUATOR, ")");

            NodoTipo* n = malloc(sizeof(NodoTipo));
            n->tipo = T_FUNCION;
            strcpy(n->parametros, params);
            n->dimensiones = 0;
            n->sig = base;

            base = n;
            continue;
        }

        break;
    }

    return base;
}



static void match(TokenType t) {
    if (!hayToken) errorSintactico("token inesperado EOF");

    if (tokenActual.type == t) {
        hayToken = GetNextToken(&tokenActual);
    } else {
        errorSintactico("token");
    }
}

static void matchLexema(TokenType t, const char* lex) {
    if (tokenActual.type == t && strcmp(tokenActual.lexema, lex) == 0) {
        hayToken = GetNextToken(&tokenActual);
    } else {
        errorSintactico(lex);
    }
}



static void errorSintactico(const char* msg) {
    fprintf(stderr, "Error sintáctico: esperaba %s, encontré '%s'\n",
            msg,
            hayToken ? tokenActual.lexema : "EOF");
    exit(EXIT_FAILURE);
}




static void imprimirTipo(NodoTipo* tipo, const char* id, const char* base) {
    printf("%s es ", id);
    const char* tipoBaseAlias = obtenerAliasTipo(base); 
    //imprimirTipoRec(tipo, id, base);
    imprimirTipoRec(tipo, tipoBaseAlias);
    printf("\n");
}





const char* obtenerAliasTipo(const char* tipo) {
    if (strcmp(tipo, "int") == 0) return "entero";
    if (strcmp(tipo, "char") == 0) return "caracter";
    if (strcmp(tipo, "float") == 0) return "flotante";
    if (strcmp(tipo, "double") == 0) return "doble";
    if (strcmp(tipo, "void") == 0) return "vacío";
    return tipo; 
}



static void imprimirTipoRec(NodoTipo* n, const char* tipoBaseAlias) {

    if (n == NULL || n->tipo == T_BASE) {
        printf("%s", tipoBaseAlias);
        return;
    }
    

    if (n->tipo == T_PUNTERO) {
        printf(" puntero a ");
        imprimirTipoRec(n->sig, tipoBaseAlias);
        return; 
    }
    

    imprimirTipoRec(n->sig, tipoBaseAlias); 


    switch (n->tipo) {

        case T_ARREGLO:
            printf(" arreglo de %d elementos de", n->dimensiones);
            break;

        case T_FUNCION:
            if (n->parametros[0] == '\0')
                printf(" función que no recibe parámetros y retorna");
            else
                printf(" función que recibe (%s) y retorna", n->parametros);
            break;
    }
}