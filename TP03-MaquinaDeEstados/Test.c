#include <stdio.h>
/* 
 * Comentario variasLineas colgado 1
 * Comentario variasLineas colgado 2
 * Comentario variasLineas colgado 3
 */

// Comentario simple línea 1
// Comentario simple línea 2 con mas texto

int main() {
    printf("Empieza prueba\n"); // Hago comentario al final de la linea

    // Prueba de strings con comentarios falsos dentro
    char *str1 = "Este es un string con /* un falso comentario */ dentro";
    char *str2 = "String con \\\"comillas con secuencia de escape\\\" y // barras";
    char *str3 = "String con salto de línea\n no debe romper";

    // Prueba de caracteres
    char c1 = '/';
    char c2 = '*';
    char c3 = '\'';
    char c4 = '\\';

    /* Comentarios variasLineas trucho */
    for(int i = 0; i < 10000; i++) {
        // Comentario dentro del for
        printf("Iteración %d\n", i); /* Comentario al final */
    }

    // Comentario antes del return
    return 0; /* Comentario despues de return */
}

/* Comentario variasLineas colgado 4
 * ----------------
 */
/* Repetimos mucho código para hacer el archivo grande */

void funcionEjemplo() {
    // Comentario simple
    char *texto = "Texto con /*comentario falso*/ y // algo mas";
    printf("%s\n", texto);
    /* Comentario variasLineas
       en una funcion */
    for(int j = 0; j < 10000; j++) {
        printf("Loop %d\n", j);
    }
}

/* Constante para que se vea más la diferencia de tiempo con el benchmark*/

#define REPETICIONES 1000

void funcionGrande() {
    for(int k=0; k<REPETICIONES; k++) {
        funcionEjemplo();
    }
}
/* Comentario fin de archivo */
