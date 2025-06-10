#include "Conversion.h"
#include <stdio.h>
typedef double (*PunteroAFuncion)(double);


void PrintTablas();
void PrintTablaCelsius();
void PrintTablaFahrenheit();
void PrintFilas(PunteroAFuncion conv, const char* encabezado1, const char* encabezado2);   
void PrintFila(int valorOriginal, double valorConvertido);


int main() {

    PrintTablas();

    return 0;
}

void PrintTablas () {

    PrintTablaCelsius();
    PrintTablaFahrenheit();
}

void PrintTablaCelsius (){

    printf("\nEsta es la tabla de Fahrenheit a Celsius:\n");

    PrintFilas(Celsius, "Fahrenh:", "Celsius:");

}

void PrintTablaFahrenheit (){

    printf("\nEsta es la tabla de Celsius a Fahrenheit:\n");

    PrintFilas(Fahrenheit, "Celsius:", "Fahrenh:");
}

void PrintFilas(PunteroAFuncion conv, const char* encabezado1, const char* encabezado2) {

    printf("%5s %18s\n", encabezado1, encabezado2);

    const int LOWER = 0;   // límite inferior de la tabla
    const int UPPER = 300; // limite superior
    const int STEP = 20; // tamaño del incremento

    for (int i = LOWER; i <= UPPER; i += STEP) 
        PrintFila(i, conv(i));
}

void PrintFila(int valorOriginal, double valorConvertido) {

    printf("%5d %20.2f\n", valorOriginal, valorConvertido);
}