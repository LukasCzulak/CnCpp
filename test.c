#include <stdio.h>
#include <math.h>
#include "physics.h"

int main(int argc, char *argv[])
{
    printf("Tests\n");

    // Factorial & fast exp
    printf("[1] factorial(5) = %d (Expected: 120)\n", factorial(5));
    printf("[2] fast_pow(2.0, 10) = %.1f (Expected: 1024.0)\n", fast_pow(2.0, 10));
    printf("[3] fast_pow(1.000001, 1000000) = %.4f (Expected: 2.7183)\n\n", fast_pow(1.000001, 1000000));

    // cosine
    printf("[4] my_cos(0.0) = %.4f (Expected: 1.0000)\n", my_cos(0.0));
    printf("[5] my_cos(3.14159) = %.4f (Expected: -1.0000)\n\n", my_cos(3.14159));

    // swap
    int x = 42, y = 69;
    swap_int(&x, &y);
    printf("[6] After swap_int: x = %d, y = %d (Expected: 69, 42)\n\n", x, y);

    // strings
    char planet[] = "mars";
    printf("[7] my_strlen(\"mars\") = %d (Expected: 4)\n", my_strlen(planet));
    to_upper(planet);
    printf("[8] to_upper -> \"%s\" (Expected: \"MARS\")\n\n", planet);

    return 0;
}