#include "Conversion.h"
#include <stdio.h>

double Celsius (double fahr) {
    return (5.0/9.0) * (fahr - 32);
};

double Fahrenheit (double cels) {
    return (9.0/5.0 * cels) + 32;
};

