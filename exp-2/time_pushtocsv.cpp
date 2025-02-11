#include <bits/stdc++.h>
using namespace std;

void generateRandomFile(const string &filename, long size)
{
   ofstream fout(filename);
   if (!fout)
   {
      cerr << "Error opening file for writing!" << endl;
      return;
   }

   random_device rd;
   mt19937 gen(rd());
   uniform_int_distribution<long> dist(1, 1e6);

   for (long i = 0; i < size; i++)
   {
      fout << dist(gen) << "\n";
   }
   fout.close();
}

vector<long> readRandomFile(const string &filename, long size)
{
   ifstream fin(filename);
   if (!fin)
   {
      cerr << "Error opening file for reading!" << endl;
      return {};
   }

   vector<long> arr(size);
   for (long i = 0; i < size && fin >> arr[i]; i++)
      ;
   fin.close();
   return arr;
}

void merge(vector<long> &arr, int s, int e)
{
   int mid = s + (e - s) / 2;
   int i, j, k;
   int n1 = mid - s + 1;
   int n2 = e - mid;
   int left[n1];
   int right[n2];
   for (i = 0; i < n1; i++)
   {
      left[i] = arr[s + i];
   }
   for (j = 0; j < n2; j++)
   {
      right[j] = arr[mid + 1 + j];
   }
   i = 0;
   j = 0;
   k = s;
   while (i < n1 && j < n2)
   {
      if (left[i] < right[j])
      {
         arr[k] = left[i];
         i++;
      }
      else
      {
         arr[k] = right[j];
         j++;
      }
   }
   while (i < n1)
   {
      arr[k++] = left[i++];
   }
   while (j < n2)
   {
      arr[k++] = right[j++];
   }
}

void mergesort(vector<long> &a, int s, int e)
{
   if (s >= e)
   {
      return;
   }
   int mid = s + (e - s) / 2;
   mergesort(a, s, mid);
   mergesort(a, mid + 1, e);
   merge(a, s, e);
}

void mergeSort(vector<long> &a)
{
   mergesort(a, 0, a.size());
}

int partition(vector<long> &arr, int low, int high)
{
   int mid = low + (high - low) / 2;
   if (arr[mid] < arr[low])
      swap(arr[mid], arr[low]);
   if (arr[high] < arr[low])
      swap(arr[high], arr[low]);
   if (arr[mid] < arr[high])
      swap(arr[mid], arr[high]);

   long pivot = arr[high];
   int i = (low - 1);

   for (int j = low; j <= high - 1; j++)
   {
      if (arr[j] <= pivot)
      {
         i++;
         swap(arr[i], arr[j]);
      }
   }
   swap(arr[i + 1], arr[high]);
   return (i + 1);
}

void quicksort(vector<long> &a, int s, int e)
{
   while (s < e)
   {
      if (e - s < 10)
      {
         for (int i = s + 1; i <= e; i++)
         {
            long key = a[i];
            int j = i - 1;
            while (j >= s && a[j] > key)
            {
               a[j + 1] = a[j];
               j--;
            }
            a[j + 1] = key;
         }
         return;
      }

      int p = partition(a, s, e);
      if (p - s < e - p)
      {
         quicksort(a, s, p - 1);
         s = p + 1;
      }
      else
      {
         quicksort(a, p + 1, e);
         e = p - 1;
      }
   }
}

void quickSort(vector<long> &a)
{
   quicksort(a, 0, a.size() - 1);
}

void get(vector<long> a, ofstream &fout)
{
   using namespace std::chrono;

   vector<long> b = a;

   auto t0 = high_resolution_clock::now();
   mergeSort(a);
   auto t1 = high_resolution_clock::now();
   auto merge_avg = duration_cast<nanoseconds>(t1 - t0);

   auto t2 = high_resolution_clock::now();
   quickSort(b);
   auto t3 = high_resolution_clock::now();
   auto quick_avg = duration_cast<nanoseconds>(t3 - t2);

   auto t4 = high_resolution_clock::now();
   mergeSort(a);
   auto t5 = high_resolution_clock::now();
   auto merge_bst = duration_cast<nanoseconds>(t5 - t4);

   auto t6 = high_resolution_clock::now();
   quickSort(b);
   auto t7 = high_resolution_clock::now();
   auto quick_bst = duration_cast<nanoseconds>(t7 - t6);

   reverse(a.begin(), a.end());
   reverse(b.begin(), b.end());

   auto t8 = high_resolution_clock::now();
   mergeSort(a);
   auto t9 = high_resolution_clock::now();
   auto merge_worst = duration_cast<nanoseconds>(t9 - t8);

   auto t10 = high_resolution_clock::now();
   quickSort(b);
   auto t11 = high_resolution_clock::now();
   auto quick_worst = duration_cast<nanoseconds>(t11 - t10);

   fout << a.size() << ","
        << quick_bst.count() << ","
        << merge_bst.count() << ","
        << quick_avg.count() << ","
        << merge_avg.count() << ","
        << quick_worst.count() << ","
        << merge_worst.count() << endl;
}

int main()
{
   const string filename = "random.txt";
   const long dataSize = 100000;
   generateRandomFile(filename, dataSize);
   ofstream fout("exp2.csv");
   fout << "size,quick bst,merge bst,quick avg,merge avg,quick worst,merge worst" << endl;
   for (int i = 100; i < 100000; i += 100)
   {
      cout << "Processing size: " << i << endl;
      vector<long> a = readRandomFile(filename, i);
      get(a, fout);
   }
   fout.close();
}