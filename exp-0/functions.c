#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f1(int n)
{
    return n;
}

double f2(int n)
{
    return n * n * n;
}

double f3(int n)
{
    return exp(n);
}

double f4(int n)
{
    return pow(2, n);
}

double f5(int n)
{
    return pow(2, log10(n));
}

double f6(int n)
{
    return sqrt(log10(n));
}

double f7(int n)
{
    return n * log10(n);
}

double f8(int n)
{
    return n * pow(2, n);
}

double f9(int n)
{
    return pow(2, pow(2, n + 1));
}

double f10(int n)
{
    return log(n);
}

int main()
{
    // f1
    printf("Function 1 : n\n");
    for (int i = 1; i <= 100; i++)
    {
        printf("%.1f ", f1(i));
    }
    printf("\n");

    // f2
    printf("Function 2 : n^3\n");
    for (int i = 1; i <= 100; i++)
    {
        printf("%.1f ", f2(i));
    }
    printf("\n");

    // f3
    printf("Function 3 : e^n\n");
    for (int i = 1; i <= 100; i++)
    {
        printf("%.1f ", f3(i));
    }
    printf("\n");

    // f4
    printf("Function 4 : 2^n\n");
    for (int i = 1; i <= 100; i++)
    {
        printf("%.1f ", f4(i));
    }
    printf("\n");

    // f5
    printf("Function 5 : 2^logn\n");
    for (int i = 1; i <= 100; i++)
    {
        printf("%.1f ", f5(i));
    }
    printf("\n");

    // f6
    printf("Function 6 : sqrt(log n)\n");
    for (int i = 1; i <= 100; i++)
    {
        printf("%.1f ", f6(i));
    }
    printf("\n");

    // f7
    printf("Function 7 : n * log n\n");
    for (int i = 1; i <= 100; i++)
    {
        printf("%.1f ", f7(i));
    }
    printf("\n");

    // f8
    printf("Function 8 : n* 2^n\n");
    for (int i = 1; i <= 100; i++)
    {
        printf("%.1f ", f8(i));
    }
    printf("\n");

    // f9
    printf("Function 9 : 2^(2^n+1)\n");
    for (int i = 1; i <= 100; i++)
    {
        printf("%.1f ", f9(i));
    }
    printf("\n");

    // f10
    printf("Function 10 : log n\n");
    for (int i = 1; i <= 100; i++)
    {
        printf("%.1f ", f10(i));
    }
}