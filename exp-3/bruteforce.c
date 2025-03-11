#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

// Function to read random numbers from a file
void readRandomNumbers(int *numbers, int *size, const char *filename)
{
   FILE *file = fopen(filename, "r");
   if (!file)
   {
      perror("Error opening file");
      exit(EXIT_FAILURE);
   }
   int num, index = 0;
   while (fscanf(file, "%d", &num) == 1)
   {
      numbers[index++] = num;
   }
   *size = index;
   fclose(file);
}

// Brute Force Algorithm to find max subarray sum (O(n^2))
int maxSubarraySum(int *arr, int size)
{
   int maxSum = INT_MIN;
   for (int i = 0; i < size; i++)
   {
      int sum = 0;
      for (int j = i; j < size; j++)
      {
         sum += arr[j];
         if (sum > maxSum)
            maxSum = sum;
      }
   }
   return maxSum;
}

int main()
{
   srand(time(0));
   FILE *outFile = fopen("brute.txt", "w");
   if (!outFile)
   {
      perror("Error opening output file");
      return EXIT_FAILURE;
   }

   int numbers[1000], size;
   readRandomNumbers(numbers, &size, "random_numbers.txt");

   for (int s = 1; s <= size && s <= 1000; s++)
   {
      clock_t start = clock();
      int maxSum = maxSubarraySum(numbers, s);
      clock_t stop = clock();
      double duration = (double)(stop - start) / CLOCKS_PER_SEC * 1000000;

      fprintf(outFile, "Size: %d -> Max Sum: %d | Execution Time: %.2f microseconds\n", s, maxSum, duration);
   }

   fclose(outFile);
   printf("Results written to brute.txt\n");
   return 0;
}