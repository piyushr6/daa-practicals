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

// Kadane's Algorithm to find max subarray sum (O(n))
int maxSubarraySum(vector<int> &arr)
{
   int maxSum = INT_MIN, currSum = 0;
   for (int num : arr)
   {
      currSum += num;
      maxSum = max(maxSum, currSum);
      if (currSum < 0)
         currSum = 0;
   }
   return maxSum;
}

int main()
{
   srand(time(0));                 // Seed for randomness
   ofstream outFile("kadane.txt"); // Open file to write results

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
   cout << "Results written to kadane.txt" << endl;
   return 0;
}