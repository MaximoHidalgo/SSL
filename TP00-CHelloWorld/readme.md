 # TP N°0 "Hello, World!" en C
 
 ### Autor de la resolución:

    ◦ MaximoHidalgo

    ◦ 176.585-1

    ◦ Hidalgo

    ◦ Máximo Juan Manuel

  

  ### Enunciado:

    3.1. Objetivos

      • Demostrar capacidad para editar, compilar, y ejecutar programas C mediante el desarrollo de un programa simple.

      • Tener un primer contacto con las herramientas necesarias para abordar la resolución de los trabajos posteriores.

      • Creación de repositorio personal git.
    
      • Armado de equipo de trabajo.

### Respuestas de la consigna 3.b.i.:

    A) Compilador seleccionado: MinGW GCC.

    B) Versión del compilador: GCC (Rev2, Built by MSYS2 project) 14.2.0

    C) Versión del estándar de C: por defecto es C17, pero puedo forzarlo a compilar en el estándar C23. 

### ¿Como verifico el estándar de C?
*una forma para verificar el estándar de C:*

    1. crear un archivo nuevo.
    2. Escribir el código: 
```c
#include <stdio.h>

int main() {
#ifdef __STDC_VERSION__
    printf("C version: %ld\n", __STDC_VERSION__);
#else
    printf("C89 (no __STDC_VERSION__ defined)\n");
#endif
    return 0;
}
```
    3.Compilar y ejecutar el código 
    4.Por consola te escupirá la versión del estándar de C en la que se encuentre, por ejemplo: "C version: 201710"
    5.tiene el formato AAAAMM, o sea que se lee 201710: octubre (10) del año 2017 y eso corresponde al estándar C17.
    6.Con esto verificamos que el estándar es C17.

### ¿Si queremos un estándar de C en especial?
*una forma para forzar el estándar de C:*

    1.Usando el mismo programa que antes, desde la terminal donde está tu archivo fuente escribimos: 
    "gcc -std=c23 version.c -o programa"
    2.Luego ejecutamos en la terminal el programa escribiendo: ./programa
    3.Ya que usamos el programa que nos decía la versión del estándar, nos debería mostrar por consola: C version: 202000.
    4.Con esto podemos verificar que forzamos al programa a compilar en el estándar C2X, que corresponde al estándar C23.
    5.Si queremos otro estándar de C, simplemente cambiamos la parte de:
    "-std=c23" a "-std=c11" o al estándar que prefiramos y repetimos los demás pasos.

