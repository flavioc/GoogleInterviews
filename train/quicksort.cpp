
#include <iostream>
#include <assert.h>

using namespace std;

void
quick(int *a, int esquerda, int direita)
{
   int i, j, x, y;
   i = esquerda;
   j = direita;
   x = a[(esquerda + direita) / 2];

   while(i <= j) {
      while(a[i] < x && i < direita)
         i++;
      while(a[j] > x && j > esquerda)
         j--;
      if(i <= j) {
         y = a[i];
         a[i] = a[j];
         a[j] = y;
         i++;
         j--;
      }
   }

   if(j > esquerda) {
      quick(a, esquerda, j);
   }
   if(i < direita) {
      quick(a, i, direita);
   }
}

void
quicksort(int *a, size_t n)
{
   int pivot = a[n/2];
   int *end = a + n;
   int *l = a;
   int *r = a + n - 1;

   while(l <= r) {
      if(*l < pivot && l < end) {
         l++;
         continue;
      }
      if(*r > pivot && r > a) {
         r--;
         continue;
      }

      swap(*l, *r);
      l++;
      r--;
   }
   if(r > a)
      quicksort(a, r - a + 1);
   if(l < (a + n)) 
      quicksort(l, (a + n) - l);
}

int
main(int argc, char **argv)
{
   int array[] = {5, 6, 1, 2};
   size_t n = sizeof(array)/sizeof(int);
   quicksort(array, n);
   for(size_t i(0); i < n; ++i) {
      cout << array[i] << " ";
   }
   cout << endl;
   return 0;
}
