#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
using namespace std::chrono;

void swap(int *xp, int *yp)
{
   int temp = *xp;
   *xp = *yp;
   *yp = temp;
}

void selectionSort(int arr[], int n)
{
   int i, j, min_idx;

   for (i = 0; i < n - 1; i++)
   {
      min_idx = i;
      for (j = i + 1; j < n; j++)
         if (arr[j] < arr[min_idx])
            min_idx = j;

      swap(&arr[min_idx], &arr[i]);
   }
}

int main()
{
   int N = sizeof(arr) / sizeof(arr[0]);

   auto start = high_resolution_clock::now();
   insertionSort(arr, N);
   auto stop = high_resolution_clock::now();
   auto duration = duration_cast<milliseconds>(stop - start);
   cout << "Time taken by function: " << duration.count() << " miliseconds" << endl;
   return 0;
}