
#include <iostream>
#include <set>

using namespace std;

#define SIZE 4
int matrix[SIZE][SIZE] = {{1, 2, 3, 4}, // 10
                    {5, 6, 7, 8}, // 26
                    {9, 10, 1, 2}, // 22
                    {13, 1, 1, 1}}; // 16
int sums[SIZE][SIZE];

static void
preprocess_matrix()
{
   sums[0][0] = matrix[0][0];
   for(size_t i(1); i < SIZE; ++i)
      sums[0][i] = sums[0][i-1] + matrix[0][i];
   for(size_t i(1); i < SIZE; ++i)
      sums[i][0] = sums[i-1][0] + matrix[i][0];

   for(size_t i(1); i < SIZE; ++i) {
      for(size_t j(1); j < SIZE; ++j) {
         int sumtop = sums[i-1][j-1];
         int sumleft = sums[i][j-1];
         int sumright = sums[i-1][j];
         sums[i][j] = sumleft + sumright - sumtop + matrix[i][j];
      }
   }
}

static int
sumArea(int x1, int y1, int x2, int y2)
{
   int sumall = sums[x2][y2];
   int sumleft = 0;
   if(y1 > 0)
      sumleft = sums[x2][y1-1];
   int sumright = 0;
   if(x1 > 0)
      sumright = sums[x1-1][y2];
   int sumcorner = 0;
   if(x1 > 0 && y1 > 0)
      sumcorner = sums[x1-1][y1-1];
   return (sumall - (sumright + sumleft)) + sumcorner;
}

static void
window_min(int *a, int N, int K)
{
   if(K > N)
      return;
   size_t i;
   int res[N];
   set<int> min_queue;
   size_t last;

   for(i = 0; i < K; ++i) {
      if(min_queue.empty()) {
         min_queue.insert(a[i]);
      } else {
         set<int>::iterator up = min_queue.upper_bound(a[i]);
         min_queue.erase(up, min_queue.end());
         min_queue.insert(a[i]);
      }
      
      res[i] = *(min_queue.begin());
      cout << res[i] << endl;
   }
   for(size_t start = 0; i < N; ++i, start++) {
      min_queue.erase(a[start]);
      set<int>::iterator up = min_queue.upper_bound(a[i]);
      min_queue.erase(up, min_queue.end());
      min_queue.insert(a[i]);
      res[i] = *(min_queue.begin());
      cout << res[i] << endl;
   }
}

static void
dyn_max(int *a, size_t N, size_t W)
{
   int LR[N], RL[N];

   for(size_t i(1); i <= N; ++i) {
      if(i % W == 1)
         LR[i] = a[i];
      else
         LR[i] = max(LR[i - 1], a[i]);
   }

   for(size_t i(N); i >= 1; --i) {
      if(i == N)
         RL[i] = a[i];
      else if(i % W == 0)
         RL[i] = a[i];
      else
         RL[i] = max(RL[i + 1], a[i]);
   }

   int max_val[N];
   for(size_t i(0); i <= N - W + 1; ++i)
      max_val[i] = max(RL[i], LR[i + W - 1]);

   for(size_t i(0); i <= N - W + 1; ++i)
      cout << max_val[i] << " ";
   cout << endl;
}

static void
phoneString(int number, char *digits, size_t size)
{
   if(number == 0) {
      for(size_t i(0); i < size; ++i) {
         cout << digits[i];
      }
      cout << endl;
      return;
   }
   int n = number % 10;
   number /= 10;
   static char ds2[3] = {'a', 'b', 'c'};
   static char ds3[3] = {'d', 'e', 'f'};
   static char ds4[3] = {'g', 'h', 'i'};
   static char ds5[3] = {'j', 'k', 'l'};
   static char ds6[3] = {'m', 'n', 'o'};
   static char ds7[4] = {'p', 'q', 'r', 's'};
   static char ds8[3] = {'t', 'u', 'v'};
   static char ds9[4] = {'w', 'x', 'y', 'z'};
   static char ds0[1] = {' '};
   static char *ds[] = {ds0, NULL, ds2, ds3, ds4, ds5, ds6, ds7, ds8, ds9};

   char *d = ds[n];
   size_t sdigits = 0;
   if(n == 9 || n == 7)
      sdigits = 4;
   else if(n == 0)
      sdigits = 1;
   else
      sdigits = 3;

   switch(n) {
      case 1: phoneString(number, digits, size); break;
      default:
      {
                 for(size_t i(0); i < sdigits; ++i) {
                    digits[size] = d[i];
                    phoneString(number, digits, size + 1);
                 }
                 break;
      }
   }
}

static void
phone(int number)
{
   char digits[255];
   phoneString(number, digits, 0);
}

static int
findLargestOne(int matrix[5][5], int rows, int cols)
{
#define POS(i, j) i][j
   int best = 0;

   for(size_t i(0); i < rows; ++i) {
      for(size_t j(0); j < cols; ++j) {
         if(matrix[POS(i, j)] == 0)
            matrix[POS(i, j)] = 0;
         else if(matrix[POS(i, j)] == 1) {
            int corner = 0;
            int left = 0;
            int top = 0;
            if(i > 0) {
               top = matrix[POS(i - 1, j)];
               if(j > 0)
                  corner = matrix[POS(i - 1, j - 1)];
            }
            if(j > 0) {
               left = matrix[POS(i, j - 1)];
            }
            if(left == 0 && top == 0)
               matrix[POS(i, j)] = 1;
            else if(left == 0 && top > 0)
               matrix[POS(i, j)] = top + 1;
            else if(left > 0 && top == 0)
               matrix[POS(i, j)] = left + 1;
            else 
               matrix[POS(i, j)] = top + left - corner + 1;
            if(matrix[POS(i, j)] > best)
               best = matrix[POS(i, j)];
         }
      }
   }
   cout << "best is " << best << endl;
}

int
main(int argc, char **argv)
{
   preprocess_matrix();
   for(size_t i(0); i < SIZE; ++i) {
      for(size_t j(0); j < SIZE; ++j) {
         cout << sums[i][j] << " ";
      }
      cout << endl;
   }
   cout << sumArea(1, 1, 2, 2) << endl;
   int a[] = {1, 3, 6, 2, 5, 3, 1, 0};
   size_t size_a = sizeof(a) / sizeof(int);
   window_min(a, size_a, 3);
   dyn_max(a, size_a, 3);
   phone(232971220);

   int dmatrix[5][5] = {{1, 1, 0, 1, 1},
                        {1, 1, 0, 0, 0},
                        {0, 0, 1, 1, 1},
                        {0, 0, 1, 1, 1},
                        {0, 0, 0, 0, 1}};
   findLargestOne(dmatrix, 5, 5);
   for(size_t i(0); i < 5; ++i) {
      for(size_t j(0); j < 5; ++j) {
         cout << dmatrix[i][j] << " ";
      }
      cout << endl;
   }
   return 0;
}
