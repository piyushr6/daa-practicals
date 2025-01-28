#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
using namespace std::chrono;

void insertionSort(int arr[], int n)
{
   int i, key, j;
   for (i = 1; i < n; i++)
   {
      key = arr[i];
      j = i - 1;

      while (j >= 0 && arr[j] > key)
      {
         arr[j + 1] = arr[j];
         j = j - 1;
      }
      arr[j + 1] = key;
   }
}

int main()
{

   int N = sizeof(arr) / sizeof(arr[0]);

   auto start = high_resolution_clock::now();
   insertionSort(arr, N);
   auto stop = high_resolution_clock::now();
   auto duration = duration_cast<microseconds>(stop - start);
   cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
   return 0;
}