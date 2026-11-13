#include "physics.h"
#include <math.h>

int factorial(int n)
{
    if (n <= 1)
    {
        return 1;
    }
    return n * factorial(n - 1);
}

double fast_pow(double base, int exp)
{
    if (exp <= 0)
        return 1.0;
    else if (exp % 2 == 1)
        return base * fast_pow(base, exp - 1);
    else
    {
        double half = fast_pow(base, exp / 2);
        return half * half;
    }
}

double my_cos(double x)
{
    while (x > PI)
        x -= 2.0 * PI;
    while (x < -PI)
        x += 2.0 * PI;

    int PRECISION = 5;
    double sum = 0.0;
    int sign = 1;

    for (int k = 0; k <= PRECISION; ++k)
    {
        double term = fast_pow(x, 2 * k) / factorial(2 * k);
        sum += sign * term;
        sign = -sign;
    }
    return sum;
}

double my_sin(double x)
{
    return my_cos(x - PI / 2.0);
}

void swap_int(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void polar_to_cartesian(double r, double angle, double *out_x, double *out_y)
{
    *out_x = r * my_cos(angle);
    *out_y = r * my_sin(angle);
}

int my_strlen(const char *str)
{
    int len = 0;

    while (*str != '\0')
    {
        ++len;
        ++str;
    }
    return len;
}

void to_upper(char *str)
{
    while (*str != '\0')
    {
        if (*str >= 'a' && *str <= 'z')
        {
            *str = *str - 32;
        }
        ++str;
    }
}

void swap_str(char *s1, char *s2)
{
    for (int i = 0; i < 16; ++i)
    {
        char temp = *(s1 + i);
        *(s1 + i) = *(s2 + i);
        *(s2 + i) = temp;
    }
}

void sort_leaderboard(char names[][16], int *speeds, int count)
{
    for (int i = 0; i < count - 1; ++i)
    {
        for (int j = 0; j < count - i - 1; ++j)
        {
            if (*(speeds + j) < *(speeds + j + 1))
            {
                swap_int(speeds + j, speeds + j + 1);
                swap_str(names[j], names[j + 1]);
            }
        }
    }
}
