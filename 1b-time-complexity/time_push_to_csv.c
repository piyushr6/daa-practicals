#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

double get_time(LARGE_INTEGER start, LARGE_INTEGER end, LARGE_INTEGER freq)
{
   return (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
}

double insertion_sort(int array[], int n)
{
   LARGE_INTEGER start, end, freq;
   QueryPerformanceFrequency(&freq);
   QueryPerformanceCounter(&start);

   for (int i = 1; i < n; i++)
   {
      int key = array[i];
      int j = i - 1;
      while (j >= 0 && array[j] > key)
      {
         array[j + 1] = array[j];
         j--;
      }
      array[j + 1] = key;
   }

   QueryPerformanceCounter(&end);
   return get_time(start, end, freq);
}

double selection_sort(int array[], int n)
{
   LARGE_INTEGER start, end, freq;
   QueryPerformanceFrequency(&freq);
   QueryPerformanceCounter(&start);

   for (int i = 0; i < n - 1; i++)
   {
      int minimum = i;
      for (int j = i + 1; j < n; j++)
      {
         if (array[j] < array[minimum])
         {
            minimum = j;
         }
      }
      int temp = array[i];
      array[i] = array[minimum];
      array[minimum] = temp;
   }

   QueryPerformanceCounter(&end);
   return get_time(start, end, freq);
}

int main()
{
   int sizes[1000];
   int size = 0; // Start from 0
   for (int i = 0; i < 1000; i++)
   {
      sizes[i] = size;
      size += 200; // Step size changed to 200
   }

   FILE *fptrIS = fopen("insertion_sort.csv", "w");
   FILE *fptrSS = fopen("selection_sort.csv", "w");
   if (!fptrIS || !fptrSS)
   {
      printf("Error opening file!\n");
      return 1;
   }
   fprintf(fptrIS, "array_size,best_time,worst_time,avg_time\n");
   fprintf(fptrSS, "array_size,best_time,worst_time,avg_time\n");

   // Open the random number file
   FILE *randFile = fopen("r1.txt", "r");
   if (!randFile)
   {
      printf("Error opening r1.txt!\n");
      return 1;
   }

   for (int j = 0; j < 1000; j++)
   {
      int test_size = sizes[j];

      int *best = (int *)malloc(test_size * sizeof(int));
      int *worst = (int *)malloc(test_size * sizeof(int));
      int *avg = (int *)malloc(test_size * sizeof(int));
      if (!best || !worst || !avg)
      {
         printf("Memory allocation failed!\n");
         return 1;
      }

      // Initialize arrays
      for (int m = 0; m < test_size; m++)
         best[m] = m;
      for (int n = 0; n < test_size; n++)
         worst[n] = test_size - n - 1;
      for (int o = 0; o < test_size; o++)
         fscanf(randFile, "%d", &avg[o]); // Read from file

      // Create copies for selection sort
      int *best_copy = (int *)malloc(test_size * sizeof(int));
      int *worst_copy = (int *)malloc(test_size * sizeof(int));
      int *avg_copy = (int *)malloc(test_size * sizeof(int));
      if (!best_copy || !worst_copy || !avg_copy)
      {
         printf("Memory allocation failed!\n");
         return 1;
      }

      // Copy the arrays
      for (int p = 0; p < test_size; p++)
         best_copy[p] = best[p];
      for (int q = 0; q < test_size; q++)
         worst_copy[q] = worst[q];
      for (int r = 0; r < test_size; r++)
         avg_copy[r] = avg[r];

      // Measure sorting times
      double IS_time_best = insertion_sort(best, test_size);
      double IS_time_worst = insertion_sort(worst, test_size);
      double IS_time_avg = insertion_sort(avg, test_size);

      double SS_time_best = selection_sort(best_copy, test_size);
      double SS_time_worst = selection_sort(worst_copy, test_size);
      double SS_time_avg = selection_sort(avg_copy, test_size);

      // Write results to CSV
      fprintf(fptrIS, "%d,%f,%f,%f\n", test_size, IS_time_best, IS_time_worst, IS_time_avg);
      fprintf(fptrSS, "%d,%f,%f,%f\n", test_size, SS_time_best, SS_time_worst, SS_time_avg);

      printf("Processed size: %d\n", test_size);

      // Free allocated memory
      free(best);
      free(worst);
      free(avg);
      free(best_copy);
      free(worst_copy);
      free(avg_copy);
   }

   fclose(fptrIS);
   fclose(fptrSS);
   fclose(randFile);

   return 0;
}