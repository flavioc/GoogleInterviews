
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <set>

using namespace std;

static int
findMaxSum(int *v, int n)
{
   int sum[n+1], i;
   sum[0] = 0;
   sum[1] = v[0];
   for(i = 2; i <= n; ++i) {
      sum[i] = max(sum[i-2]+v[i-1], sum[i-1]);
   }
}

static void
findLongest(int *a, int max, int i, int len, int size, int *longest, int *visited, int *set)
{
   if(*longest != 0 && len + (size - i) < *longest)
      return;

   if(i == size) {
      if(len > *longest) {
         memcpy(set, visited, sizeof(int)*size);
         *longest = len;
      }
      return;
   }

   // do not include
   visited[i] = 0;
   findLongest(a, max, i+1, len, size, longest, visited, set);
   // include
   if(a[i] > max) {
      visited[i] = 1;
      findLongest(a, a[i], i + 1, len + 1, size, longest, visited, set);
   }
}

static void
findLongestIncreasing(int *a, int n)
{
   int longest = 0;
   int visited[n];
   int set[n];
   for(size_t i(0); i < n; ++i)
      visited[i] = 0;

   findLongest(a, -9999, 0, 0, n, &longest, visited, set);
   for(size_t i(0); i < n; ++i) {
      if(set[i])
         cout << a[i] << " ";
   }
   cout << endl;
}

static void
longest_dyn(int *a, int n)
{
   int len[n];
   int next[n];

   len[0] = 1;
   next[0] = -1;

   for(int i(1); i < n; ++i) {
      bool found = false;
      int best = 0;
      int nexti = 0;
      for(int j(0); j < i; ++j) {
         if(a[j] < a[i]) {
            if(!found) {
               found = true;
               best = len[j];
               nexti = j;
            } else {
               if(best < len[j]) {
                  best = len[j];
                  nexti = j;
               }
            }
         }
      }
      if(found) {
         next[i] = nexti;
         len[i] = best + 1;
      } else {
         next[i] = -1;
         len[i] = 1;
      }
   }

   int best = len[0];
   int index = 0;
   for(int i = 1; i < n; ++i) {
      if(best < len[i]) {
         best = len[i];
         index = i;
      }
   }
   for(int i(0); i < best; ++i) {
      cout << a[index] << " ";
      if(next[index] != -1) {
         index = next[index];
      }
   }
   cout << endl;
}

static int
find_largest(int *x, int *lens, int size, int item)
{
   // find largest which x[lens[j]] < item
   int l = 0, r = size;

   while (l <= r) {
      int m = (l + r)/2;
      if(x[lens[m]] <= item)
         l = m + 1;
      else r = m - 1;
   }
   return r;
}

void
lis(int *x, int n)
{
   int lens[n];
   int preds[n];
   int longest = 1;

   lens[longest - 1] = 0;
   preds[longest - 1] = -1;

   for(int i(1); i < n; ++i) {
      // find largest positive j <= L
      cout << "Try " << i << " " << x[i] << " (longest: " << longest << ")" << endl;
      int j = find_largest(x, lens, longest-1, x[i]);
      if(j == -1) {
         cout << "Not found" << endl;
         preds[i] = -1;
      } else {
         cout << "found " << j << " len " << lens[j] << endl;
         preds[i] = lens[j];

         if(j == longest-1 || x[i] < x[lens[j+1]]) {
            lens[j+1] = i;
            if(j + 2 > longest) {
               cout << "new long " << longest << endl;
               longest = j + 2;
            }
         }
      }
   }
   int lis[longest];
   n = longest - 1;
   int p = lens[n];
   while(n >= 0) {
      lis[n] = x[p];
      p = preds[p];
      n--;
   }

   cout << "result " << longest << endl;
   for(int i(0); i < longest; ++i) {
      cout << lis[i] << " ";
   }
   cout << endl;

}

int
main(int argc, char **argv)
{
   int a[] = {1, 5, 3, 6};
   findLongestIncreasing(a, sizeof(a)/sizeof(int));
   longest_dyn(a, sizeof(a)/sizeof(int));
   lis(a, sizeof(a)/sizeof(int));
   return 0;
}
