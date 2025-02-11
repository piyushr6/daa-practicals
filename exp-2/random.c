#include <stdio.h>
#include <stdlib.h>

int main()
{
   FILE *fptr;

   // r1.txt - 100000 random numbers
   fptr = fopen("r1.txt", "w");

   for (int i = 0; i < 100000; i++)
   {
      int random_number = rand() % (10000 + 1);
      fprintf(fptr, "%d\n", random_number);
   }
   fclose(fptr);
}