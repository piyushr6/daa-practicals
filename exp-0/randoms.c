#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fptr;

    // r1.txt - 10000 random numbers
    fptr = fopen("r1.txt", "w");

    for (int i = 0; i < 10000; i++)
    {
        int random_number = rand() % (100 + 1);
        fprintf(fptr, "%d\n", random_number);
    }
    fclose(fptr);

    // r2.txt - 20000 random numbers
    fptr = fopen("r2.txt", "w");

    for (int i = 0; i < 20000; i++)
    {
        int random_number = rand() % (100 + 1);
        fprintf(fptr, "%d\n", random_number);
    }
    fclose(fptr);

    // r3.txt - 30000 random numbers
    fptr = fopen("r3.txt", "w");

    for (int i = 0; i < 30000; i++)
    {
        int random_number = rand() % (100 + 1);
        fprintf(fptr, "%d\n", random_number);
    }
    fclose(fptr);

    // r4.txt - 40000 random numbers
    fptr = fopen("r4.txt", "w");

    for (int i = 0; i < 40000; i++)
    {
        int random_number = rand() % (100 + 1);
        fprintf(fptr, "%d\n", random_number);
    }
    fclose(fptr);

    // r5.txt - 50000 random numbers
    fptr = fopen("r5.txt", "w");

    for (int i = 0; i < 50000; i++)
    {
        int random_number = rand() % (100 + 1);
        fprintf(fptr, "%d\n", random_number);
    }
    fclose(fptr);

    // r6.txt - 60000 random numbers
    fptr = fopen("r6.txt", "w");

    for (int i = 0; i < 60000; i++)
    {
        int random_number = rand() % (100 + 1);
        fprintf(fptr, "%d\n", random_number);
    }
    fclose(fptr);

    // r7.txt - 70000 random numbers
    fptr = fopen("r7.txt", "w");

    for (int i = 0; i < 70000; i++)
    {
        int random_number = rand() % (100 + 1);
        fprintf(fptr, "%d\n", random_number);
    }
    fclose(fptr);

    // r8.txt - 80000 random numbers
    fptr = fopen("r8.txt", "w");

    for (int i = 0; i < 80000; i++)
    {
        int random_number = rand() % (100 + 1);
        fprintf(fptr, "%d\n", random_number);
    }
    fclose(fptr);

    // r9.txt - 90000 random numbers
    fptr = fopen("r9.txt", "w");

    for (int i = 0; i < 90000; i++)
    {
        int random_number = rand() % (100 + 1);
        fprintf(fptr, "%d\n", random_number);
    }
    fclose(fptr);

    // r10.txt - 100000 random numbers
    fptr = fopen("r10.txt", "w");

    for (int i = 0; i < 100000; i++)
    {
        int random_number = rand() % (100 + 1);
        fprintf(fptr, "%d\n", random_number);
    }
    fclose(fptr);
}