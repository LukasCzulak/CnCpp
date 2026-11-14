#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#define PI 3.14159265359

    // === Recursion and meth ===
    int factorial(int n);
    double fast_pow(double base, int exp);
    double my_cos(double x);
    double my_sin(double x);

    // === pointers ===
    void swap_int(int *a, int *b);
    void polar_to_cartesian(double r, double angle, double *out_x, double *out_y);

    // === strings ===
    int my_strlen(const char *str);
    void to_upper(char *str);

    // === sorting ===
    void swap_str(char *s1, char *s2);
    void sort_leaderboard(char names[][16], int *speeds, int count);

#ifdef __cplusplus
}
#endif