#include <bits/stdc++.h>
using namespace std;

// Function to read random numbers from file
void readRandomNumbers(vector<int> &numbers, const string &filename)
{
   ifstream inFile(filename);
   if (!inFile)
   {
      cerr << "Error opening file!" << endl;
      exit(1);
   }
   int num;
   while (inFile >> num)
   {
      numbers.push_back(num);
   }
   inFile.close();
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
int maxCrossingSum(vector<int> &arr, int low, int mid, int high)
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
int maxSubarraySum(vector<int> &arr, int low, int high)
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
   ofstream outFile("divideconquer.txt");

   if (!outFile)
   {
      cerr << "Error opening file!" << endl;
      return 1;
   }

   vector<int> numbers;
   readRandomNumbers(numbers, "random_numbers.txt");

   for (int size = 1; size <= 1000; size++)
   {
      vector<int> arr(numbers.begin(), numbers.begin() + size);

      auto start = chrono::high_resolution_clock::now();
      int maxSum = maxSubarraySum(arr, 0, size - 1);
      auto stop = chrono::high_resolution_clock::now();
      auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

      outFile << "Size: " << size << " -> Max Sum: " << maxSum << " | Execution Time: " << duration.count() << " microseconds" << endl;
   }

   outFile.close();
   cout << "Results written to divideconquer.txt" << endl;
   return 0;
}