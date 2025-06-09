#include "Conversion.h"
#include <stdio.h>

int main(){
    ImprimirLasTablas
}

ImprimirLasTablas
    ImprimirFaC
    ImprimirCaF

ImprimirFaC
ImprimirCaF



/* Ejercicio de ejemplo
 imprime la tabla Fahrenheit-Celsius para fahr = 0, 20, ..., 300 */

int main()
{
    int fahr, celsius;
    int lower, upper, step;
    lower = 0;   //límite inferior de la tabla de temperaturas
    upper = 300; //límite superior
    step = 20; //tamaño del incremento

    fahr = lower;
    while (fahr <= upper)
    {
        celsius = 5 * (fahr - 32) / 9;
        printf ("%3d %6d\n", fahr, celsius);
        fahr = fahr + step;
    }
    return 0;
}


/* Ejercicio 1-3. Modifique el programa de conversión 
de temperaturas de modo que escriba un encabezado sobre la tabla COMPLETO
 imprime la tabla Fahrenheit-Celsius para fahr = 0, 
20, ..., 300; versión de punto flotante */

int main()
{
    float fahr, celsius;
    int lower, upper, step;
    lower = 0;   // límite superior de la tabla de temperaturas
    upper = 300; // límite superior
    step = 20;   // tamaño del incremento

    printf("Esta es la tabla de Fahrenheit-Celsius:\n");

    fahr = lower;
    while (fahr <= upper)
    {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
    return 0;
}


/* Ejercicio 1-4. Escriba un programa que imprima la 
tabla correspondiente Celsius a Fahrenheit. COMPLETO
 imprime la tabla Celsius-Fahrenheit para celsius = 0, 20, ..., 300;
  versión de punto flotante */

int main()
{
    float fahr, celsius;
    int lower, upper, step;
    lower = 0;   // límite superior de la tabla de temperaturas
    upper = 300; // límite superior
    step = 20;   // tamaño del incremento

    printf("Esta es la tabla de Celsius-Fahrenheit:\n");

    celsius = lower;
    while (celsius <= upper)
    {
        fahr = ( celsius / (5.0 / 9.0) ) + 32.0;
        printf("%3.0f %6.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
    return 0;
}


/* Ejercicio de ejemplo de for
 imprime la tabla Fahrenheit-Celsius */

int main()
{
    int fahr;
    for (fahr = 0; fahr <= 300; fahr = fahr + 20)
    {
        printf("%3d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));
    }
    return 0;
}


/* Ejercicio 1-5. Modifique el programa de conversión de 
temperaturas de manera que escriba la tabla en orden 
inverso, esto es, desde 300 grados hasta 0. COMPLETO
 imprime la tabla Fahrenheit-Celsius en orden inverso*/

int main()
{
    int fahr;
    for (fahr = 300; fahr >= 0; fahr = fahr - 20)
    {
        printf("%3d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));
    }
    return 0;
}



// Ejemplo con Constantes simbolicas, o sea definiendoles 
un nombre - texto de reemplazo
#define LOWER 0   // límite inferior de la tabla
#define UPPER 300 // limite superior
#define STEP 20   // tamaño del incremento

/*imprime la tabla Fahrenheit-Celsius*/

int main(){
   int fahr;
   for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP){
       printf("%3d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));
   }
   return 0;
}

