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

// Brute Force Algorithm to find max subarray sum (O(n^2))
int maxSubarraySum(vector<int> &arr)
{
   int maxSum = INT_MIN;
   for (size_t i = 0; i < arr.size(); i++)
   {
      int sum = 0;
      for (size_t j = i; j < arr.size(); j++)
      {
         sum += arr[j];
         maxSum = max(maxSum, sum);
      }
   }
   return maxSum;
}

int main()
{
   srand(time(0)); // Seed for randomness
   ofstream outFile("brute.txt");

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
      int maxSum = maxSubarraySum(arr);
      auto stop = chrono::high_resolution_clock::now();
      auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

      outFile << "Size: " << size << " -> Max Sum: " << maxSum << " | Execution Time: " << duration.count() << " microseconds" << endl;
   }

   outFile.close();
   cout << "Results written to brute.txt" << endl;
   return 0;
}