#include "Conversion.h"
#include <stdio.h>
typedef double (*conversion_fn)(double);


int PrintTablas(void);
int PrintTablaCelsius(void);
int PrintTablaFahrenheit(void);
int PrintFilas(conversion_fn conv, const char* encabezado1, const char* encabezado2);   
int PrintFila(int valorOriginal, double valorConvertido);


int main() {

    PrintTablas();
    
    return 0;
}

int PrintTablas () {

    PrintTablaCelsius();
    PrintTablaFahrenheit();

    return 0;
}

int PrintTablaCelsius (){

    printf("\nEsta es la tabla de Fahrenheit a Celsius:\n");

    PrintFilas(Celsius, "Fahrenh:", "Celsius:");

    return 0;
}

int PrintTablaFahrenheit (){

    printf("\nEsta es la tabla de Celsius a Fahrenheit:\n");

    PrintFilas(Fahrenheit, "Celsius:", "Fahrenh:");

    return 0;
}

int PrintFilas(conversion_fn conv, const char* encabezado1, const char* encabezado2) {

    printf("%5s %18s\n", encabezado1, encabezado2);

    const int LOWER = 0;   // límite inferior de la tabla
    const int UPPER = 300; // limite superior
    const int STEP = 20; // tamaño del incremento

    for (int i = LOWER; i <= UPPER; i += STEP) {
        double convertido = conv((double)i);
        PrintFila(i, convertido);
    }

    return 0;
}

int PrintFila(int valorOriginal, double valorConvertido) {

    printf("%5d %20.2f\n", valorOriginal, valorConvertido);

    return 0;
}