#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_COUNT 1000
#define FILE_NAME "random_numbers.txt"

int main()
{
   FILE *file = fopen(FILE_NAME, "w");
   if (file == NULL)
   {
      printf("Error opening file!\n");
      return 1;
   }

   srand(time(NULL)); // Seed the random number generator

   for (int i = 0; i < NUM_COUNT; i++)
   {
      int random_num = (rand() % 2001) - 1000; // Generates numbers from -1000 to 1000
      fprintf(file, "%d\n", random_num);
   }

   fclose(file);
   printf("Random numbers generated and saved to %s\n", FILE_NAME);
   return 0;
}