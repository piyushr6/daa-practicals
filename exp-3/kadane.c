#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

// Function to read random numbers from file
void readRandomNumbers(int *numbers, int *size, const char *filename)
{
   FILE *inFile = fopen(filename, "r");
   if (!inFile)
   {
      perror("Error opening file");
      exit(EXIT_FAILURE);
   }
   int num, index = 0;
   while (fscanf(inFile, "%d", &num) == 1)
   {
      numbers[index++] = num;
   }
   *size = index;
   fclose(inFile);
}

// Kadane's Algorithm to find max subarray sum (O(n))
int maxSubarraySum(int *arr, int size)
{
   int maxSum = INT_MIN, currSum = 0;
   for (int i = 0; i < size; i++)
   {
      currSum += arr[i];
      if (currSum > maxSum)
         maxSum = currSum;
      if (currSum < 0)
         currSum = 0;
   }
   return maxSum;
}

int main()
{
   srand(time(0)); // Seed for randomness
   FILE *outFile = fopen("kadane.txt", "w");

   if (!outFile)
   {
      perror("Error opening file");
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
   printf("Results written to kadane.txt\n");
   return 0;
}
