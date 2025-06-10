#include "Conversion.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>

void testPuntosCriticos(void);

bool AreNear(double a, double b, double tolerancia) {
    return fabs(a - b) < tolerancia;
}

int main() {
    testPuntosCriticos();

    // printf("Celsius(80) = %.2f\n", Celsius(80));
    // printf("Fahrenheit(80) = %.2f\n", Fahrenheit(80));

    // printf("Celsius(32) = %.2f\n", Celsius(32));

    // printf("Fahrenheit(0) = %.2f\n", Fahrenheit(0));
    // printf("Celsius(0) = %.2f\n", Celsius(0));

    // printf("Fahrenheit(-40) = %.2f\n", Fahrenheit(-40));
    // printf("Celsius(-40) = %.2f\n", Celsius(-40));

    printf("Todos los tests pasaron.\n");
    return 0;
}

void testPuntosCriticos(void) {

    // Valores especificos
    // Prueba 0: 80°F debe ser 26.67°C
    assert(AreNear(Celsius(80), 26.67, 0.01));
    // Prueba 0: 80°C debe ser 176°F
    assert(AreNear(Fahrenheit(80), 176.00, 0.01));

    // Prueba 1: 32°F debe ser 0°C
    assert(AreNear(Celsius(32), 0.00, 0.01));
    // Prueba 2: 0°C debe ser 32°F
    assert(AreNear(Fahrenheit(0), 32.00, 0.01));
    // Prueba 3: 0°F debe ser -17.77...°C
    assert(AreNear(Celsius(0), -17.77, 0.01));
    // Prueba 4: -40°C debe ser -40°F
    assert(AreNear(Fahrenheit(-40), -40.00, 0.01));
    // Prueba 5: -40°F debe ser -40°C
    assert(AreNear(Celsius(-40), -40.00, 0.01));
    
}


