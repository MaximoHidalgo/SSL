#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Scanner.h"

static void declaracion();
static void match(TokenType esperado);
static void matchLexema(TokenType esperado, const char* lexemaEsperado);
static void errorSintactico(const char* esperado);
static NodoTipo* parseDeclarador();
static NodoTipo* parsePostfijo(NodoTipo* base);
static void imprimirTipo(NodoTipo* tipo, const char* id, const char* tipoBase);
static Token tokenActual;
static bool hayToken = false;
const char* obtenerAliasTipo(const char* tipo);
static void imprimirTipoRec(NodoTipo* n, const char* tipoBaseAlias) ;
static void freeNodoTipo(NodoTipo* n);



#endif