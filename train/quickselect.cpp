
#include <iostream>

using namespace std;

int array[] = {6, 2, 4, 10, 25634, 14, 230};

static double
findKSmallest(int *a, int n, int k)
{
   int pivot = a[n/2];
   int *l = a;
   int *r = a + n - 1;

   while(l < r) {
      if(*l < pivot) {
         l++;
         continue;
      }
      if(*r > pivot) {
         r--;
         continue;
      }

      // need to swap
      swap(*l, *r);
      l++;
      r--;
   }

   int Lsize = l - a;
   int Rsize = n - (Lsize + 1);

   if(k == Lsize)
      return *l;
   else if(k < Lsize)
      return findKSmallest(a, Lsize, k);
   else
      return findKSmallest(r + 1, Rsize, k - (Lsize + 1));
}

static double
findMedian(int *a, int n)
{
   if(n % 2 == 0) {
      int one = findKSmallest(a, n, n / 2);
      int two = findKSmallest(a, n, (n/2) + 1);
      cout << one << " " << two << endl;
      return (one + two) / 2.0;
   } else {
      int one = findKSmallest(a, n, n / 2);
      return (double)one;
   }
}

int
main(int argc, char **argv)
{
   double med = findMedian(array, sizeof(array)/sizeof(int));
   cout << med << endl;
   return 0;
}
