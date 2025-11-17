#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

static Token tokenActual;
static bool hayToken = false;


static void declaracion();
static void match(TokenType esperado);
static void matchLexema(TokenType esperado, const char* lexemaEsperado);
static void errorSintactico(const char* esperado);
static NodoTipo* parseDeclarador();
static NodoTipo* parsePostfijo(NodoTipo* base);
static void imprimirTipo(NodoTipo* tipo, const char* id, const char* tipoBase);

const char* obtenerAliasTipo(const char* tipo);
//static void imprimirTipoRec(NodoTipo* tipo, const char* id, const char* tipoBase);
static void imprimirTipoRec(NodoTipo* n, const char* tipoBaseAlias) ;
static void freeNodoTipo(NodoTipo* n);


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
        freeNodoTipo(tipo);
    }
}



static NodoTipo* parseDeclarador() {

    //Contar prefijos '*' 
    int pointerCount = 0;
    while (tokenActual.type == OPERADORES && strcmp(tokenActual.lexema, "*") == 0) {
        matchLexema(OPERADORES, "*");
        pointerCount++;
    }

    NodoTipo* node = NULL;

    //(declarador)
    if (tokenActual.type == PUNCTUATOR && strcmp(tokenActual.lexema, "(") == 0) {
        matchLexema(PUNCTUATOR, "(");
        node = parseDeclarador();
        matchLexema(PUNCTUATOR, ")");
        node = parsePostfijo(node);
    }

    // identificador
    else if (tokenActual.type == IDENTIFICADOR) {
        NodoTipo* idNode = malloc(sizeof(NodoTipo));
        idNode->tipo = T_BASE;
        idNode->dimensiones = 0;
        strcpy(idNode->parametros, tokenActual.lexema);
        idNode->sig = NULL;

        match(IDENTIFICADOR);

        node = parsePostfijo(idNode);
    }
    else {    
        errorSintactico("declarador");
        return NULL;
    }

    //insertar los punteros
    for (int i = 0; i < pointerCount; ++i) {
        NodoTipo* p = malloc(sizeof(NodoTipo));
        if (!p) { perror("malloc"); exit(EXIT_FAILURE); }
        p->tipo = T_PUNTERO;
        p->dimensiones = 0;
        p->parametros[0] = '\0';

        /* Si node es base directamente, p pasa a ser la nueva cabecera */
        if (node == NULL || node->tipo == T_BASE) {
            p->sig = node;
            node = p;
        } else {
            /* buscar el nodo cuyo siguiente es T_BASE (insertar antes del base) */
            NodoTipo* cur = node;
            while (cur->sig && cur->sig->tipo != T_BASE) cur = cur->sig;
            /* ahora cur->sig es el T_BASE (o NULL). Insertamos p antes de cur->sig */
            p->sig = cur->sig;
            cur->sig = p;
        }
    }

    return node;
}


static NodoTipo* parsePostfijo(NodoTipo* base) {

    while (1) {

        /* arreglo: [LiteralNumerico?] (dim == 0 => tamaño indefinido) */
        if (tokenActual.type == PUNCTUATOR && strcmp(tokenActual.lexema, "[") == 0) {

            matchLexema(PUNCTUATOR, "[");

            int dim = 0;
            if (tokenActual.type == LITERAL_NUMERICO) {
                dim = atoi(tokenActual.lexema);
                match(LITERAL_NUMERICO);
            }

            matchLexema(PUNCTUATOR, "]");

            NodoTipo* n = malloc(sizeof(NodoTipo));
            if (!n) { perror("malloc"); exit(EXIT_FAILURE); }
            n->tipo = T_ARREGLO;
            n->dimensiones = dim; 
            n->parametros[0] = '\0';
            if (base && base->tipo == T_PUNTERO) {
                NodoTipo* p = base;
                NodoTipo* tail = p;
                while (tail->sig && tail->sig->tipo == T_PUNTERO) tail = tail->sig;
                NodoTipo* B = tail->sig;
                n->sig = B;
                tail->sig = n;
                base = p;
            } else {
                /* comportamiento normal: arreglo envuelve base */
                n->sig = base;
                base = n;
            }

            continue;
        }

        /* funcion: ( [ListaParametros] ) */
        if (tokenActual.type == PUNCTUATOR && strcmp(tokenActual.lexema, "(") == 0) {

            matchLexema(PUNCTUATOR, "(");

            char params[256] = "";
            params[0] = '\0';

            if (!(tokenActual.type == PUNCTUATOR && strcmp(tokenActual.lexema, ")") == 0)) {

                while (1) {
                    if (tokenActual.type != KEYWORD)
                        errorSintactico("tipo de parametro");

                    char t[64];
                    strcpy(t, tokenActual.lexema);
                    match(KEYWORD);

                    NodoTipo* paramTipo = parseDeclarador();

                    char id[64] = "";
                    if (paramTipo) {
                        NodoTipo* aux = paramTipo;
                        while (aux && aux->tipo != T_BASE) aux = aux->sig;
                        if (aux && aux->parametros[0] != '\0') {
                            strcpy(id, aux->parametros);
                            id[sizeof(id)-1] = '\0';
                        }
                    }

                    /* formar la representación textual del parametro */
                    char temp[128];
                    if (id[0])
                        snprintf(temp, sizeof(temp), "%s %s", t, id);
                    else
                        snprintf(temp, sizeof(temp), "%s", t);

                    if (params[0]) strncat(params, ", ", sizeof(params)-strlen(params)-1);
                    strncat(params, temp, sizeof(params)-strlen(params)-1);

                    freeNodoTipo(paramTipo);

                    if (tokenActual.type == PUNCTUATOR && strcmp(tokenActual.lexema, ",") == 0) {
                        matchLexema(PUNCTUATOR, ",");
                        continue;
                    } else {
                        break;
                    }
                }
            }

            matchLexema(PUNCTUATOR, ")");

            NodoTipo* n = malloc(sizeof(NodoTipo));
            if (!n) { perror("malloc"); exit(EXIT_FAILURE); }
            n->tipo = T_FUNCION;
            /* copiar params de forma segura */
            strcpy(n->parametros, params);
            n->dimensiones = 0;
            if (base && base->tipo == T_PUNTERO) {
                NodoTipo* p = base;
                NodoTipo* tail = p;
                while (tail->sig && tail->sig->tipo == T_PUNTERO) tail = tail->sig;
                NodoTipo* B = tail->sig;
                n->sig = B;
                tail->sig = n;
                base = p;
            } else {
                n->sig = base;
                base = n;
            }

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
    fprintf(stderr, "Error sintactico: esperaba %s, encontre '%s'\n",
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
    if (strcmp(tipo, "void") == 0) return "void";
    return tipo; 
}



static void imprimirTipoRec(NodoTipo* n, const char* tipoBaseAlias) {

    if (n == NULL || n->tipo == T_BASE) {
        printf("%s", tipoBaseAlias);
        return;
    }

    switch (n->tipo) {
        case T_PUNTERO:
            /* prefijo */
            printf("puntero a ");
            imprimirTipoRec(n->sig, tipoBaseAlias);
            break;

        case T_ARREGLO:
            /* prefijo; dim==0 => tamano indefinido */
            if (n->dimensiones == 0)
                printf("arreglo de tamano indefinido de ");
            else
                printf("arreglo de %d elementos de ", n->dimensiones);
            imprimirTipoRec(n->sig, tipoBaseAlias);
            break;

        case T_FUNCION:
            /* prefijo: funcion ... y retorna <tipo interno> */
            if (n->parametros[0] == '\0')
                printf("funcion que no recibe parametros y retorna ");
            else
                printf("funcion que recibe (%s) y retorna ", n->parametros);
            imprimirTipoRec(n->sig, tipoBaseAlias);
            break;

        default:
            imprimirTipoRec(n->sig, tipoBaseAlias);
            break;
    }
}

static void freeNodoTipo(NodoTipo* n) {
    while (n) {
        NodoTipo* tmp = n->sig;
        free(n);
        n = tmp;
    }
}