#include <stdio.h>

/*
 * Comentario multilinea inicial largo
 * Línea adicional 1
 * Línea adicional 2
 * Fin del comentario inicial
 */

// Comentario simple inicial con texto extendido

// --- PRUEBA DE STRINGS AVANZADA ---
int main() {

    printf("Inicio del test mejorado\n");  // Comentario al final

    // String con comentario falso multilinea
    char *s1 = "Texto con /* comentario falso */ incrustado";

    // String con muchas barras y escapes
    char *s2 = "Ruta: C:\\\\Users\\\\Test // no es comentario";

    // String con comillas continuadas
    char *s3 = "Cadena con \\\"comillas\\\" y /* falso */ // falso";

    // String que continúa en la línea siguiente con '\'
    char *s4 = "Linea 1 de string\
 y linea 2 sin romper comentarios";

    // CHARS DE PRUEBA
    char c1 = '/';
    char c2 = '*';
    char c3 = '\"';
    char c4 = '\\';
    char c5 = '\''; // comilla simple

    /* Comentario multilinea
       con * y / mezclados */// <- el preprocesador debe seguir el multilinea
       /* y con cosas raras *** //// *** /*/**/ */

    // --- PRUEBA DE MACROS ---
    #define FALSO /* esto no es un comentario para el preprocesador del TP */
    #define VERDADERO 123 // este sí es comentario verdadero

    #define CADENA "Texto /* falso */"

    // Comentario antes del for
    for(int i = 0; i < 5000; i++) {
        printf("Iter %d\n", i); // comentario al final
    }

    // Comentario antes del return
    return 0; /* retorno con comentario */
}

/* Comentario colgado al final del main */

// PRUEBA: COMENTARIOS ANIDADOS (ilegales pero buen test)
/*
    Comentario externo
    /*
        Comentario interno (no válido)
     */
    Linea final del comentario externo
*/

// --- FUNCION EXTRA ---
void funcionExtra() {
    // comentario simple
    char *txt = "Cadena // falsa y /* falso */ real";
    printf("%s\n", txt);

    /* comentario multilinea dentro */
    for(int j = 0; j < 4000; j++) {
        printf("Loop extra %d\n", j);
    }
}

/* Prueba de secuencias repetitivas */
#define REP 500

void funcionPesada() {
    for(int k = 0; k < REP; k++) {
        funcionExtra();
    }
}

// Comentario final del archivo
