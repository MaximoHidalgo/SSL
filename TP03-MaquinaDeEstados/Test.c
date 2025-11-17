#include <stdio.h>

/*
 * Bloque de comentario multilinea inicial 1
 * Bloque de comentario multilinea inicial 2
 * Bloque de comentario multilinea inicial 3
 */

// Comentario simple A
// Comentario simple B con más palabras agregadas

int main() {
    printf("Inicio de ejecución\n"); // Comentario al final de línea

    // Strings con secuencias que parecen comentarios pero no lo son
    char *s1 = "Cadena con /* comentario trucho */ incrustado";
    char *s2 = "Cadena con \\\"comillas escapadas\\\" y // barras dobles";
    char *s3 = "Cadena con salto de línea\n que no debe cortar el texto";

    // Caracteres individuales de prueba
    char ch1 = '/';
    char ch2 = '*';
    char ch3 = '\'';
    char ch4 = '\\';

    /* Comentario multilinea de prueba general */
    for(int i = 0; i < 9500; i++) {
        // Comentario simple dentro del for
        printf("Iter %d\n", i); /* Otro comentario al final */
    }

    // Comentario previo al return
    return 0; /* Comentario luego del return */
}

/* Comentario multilínea colgado zona final
 * -------------------------------
 */

/* Repetición de bloques de código para agrandar tamaño del archivo */

void ejemploFuncion() {
    // Otro comentario simple
    char *txt = "Cadena con /*bloque falso*/ y // pseudo comentario";
    printf("%s\n", txt);

    /* Comentario multilinea dentro de una función */
    for(int j = 0; j < 9500; j++) {
        printf("Loop interno %d\n", j);
    }
}

/* Constante para simular procesamiento extendido */

#define CANTIDAD 800

void funcionPesada() {
    for(int k = 0; k < CANTIDAD; k++) {
        ejemploFuncion();
    }
}

/* Comentario final del archivo */
// Último comentario simple del archivo