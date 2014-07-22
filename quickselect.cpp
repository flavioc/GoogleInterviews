
#include <iostream>

using namespace std;

// find k-largest number

int array[] = {5, 1, 6, 2, 4, 10, 20, 3};

int
findKSmallest(int *a, int n, int k)
{
   // assert(k < n);
   cout << "find " << n << " k: " << k << endl;
   if(n == 1) {
      if(k == 0)
         return a[0];
      else
         return -1;
   }

   if(n == 2) {
      if(k == 0) {
         // find smallest number
         if(a[0] < a[1])
            return a[0];
         else
            return a[1];
      } else if(k == 1) {
         if(a[0] < a[1])
            return a[1];
         else
            return a[0];
      } else
         return -1;
   }

   int middle = n/2;
   int pivot = a[middle];
   cout << "pivot " << pivot << endl;

   int *l = a;
   int *r = a + n-1;
   while(l < r) {
      if(*l < pivot) {
         ++l;
         continue;
      }
      if(*r > pivot) {
         r--;
         continue;
      }
      swap(*l, *r);
      l++;
      r--;
   }
   int sizeL = (l - a);
   int sizeR = n - sizeL - 1;
   cout << "sizes " << sizeL << " " << sizeR << endl;
   if(sizeL == k)
      return pivot;
   else if(k < sizeL) {
      return findKSmallest(a, sizeL, k);
   else
      return findKSmallest(r + 1, sizeR, k - (sizeL + 1));
}

int
main(int argc, char **argv)
{
   cout << findKSmallest(array, sizeof(array)/sizeof(int), 7) << endl;
}
