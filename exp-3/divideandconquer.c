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

// Function to find maximum of two numbers
int max(int a, int b)
{
   return (a > b) ? a : b;
}

// Function to find maximum of three numbers
int max3(int a, int b, int c)
{
   return max(a, max(b, c));
}

// Function to find max subarray sum crossing the middle
int maxCrossingSum(int *arr, int low, int mid, int high)
{
   int leftSum = INT_MIN, rightSum = INT_MIN, sum = 0;

   for (int i = mid; i >= low; i--)
   {
      sum += arr[i];
      if (sum > leftSum)
         leftSum = sum;
   }

   sum = 0;
   for (int i = mid + 1; i <= high; i++)
   {
      sum += arr[i];
      if (sum > rightSum)
         rightSum = sum;
   }

   return leftSum + rightSum;
}

// Recursive function to find maximum subarray sum
int maxSubarraySum(int *arr, int low, int high)
{
   if (low == high)
      return arr[low];

   int mid = (low + high) / 2;

   return max3(
       maxSubarraySum(arr, low, mid),
       maxSubarraySum(arr, mid + 1, high),
       maxCrossingSum(arr, low, mid, high));
}

int main()
{
   srand(time(0)); // Seed for randomness
   FILE *outFile = fopen("divideconquer.txt", "w");

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
      int maxSum = maxSubarraySum(numbers, 0, s - 1);
      clock_t stop = clock();
      double duration = (double)(stop - start) / CLOCKS_PER_SEC * 1000000;

      fprintf(outFile, "Size: %d -> Max Sum: %d | Execution Time: %.2f microseconds\n", s, maxSum, duration);
   }

   fclose(outFile);
   printf("Results written to divideconquer.txt\n");
   return 0;
}