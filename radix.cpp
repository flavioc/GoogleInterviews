
#include <iostream>
#include <cstring>

using namespace std;

static void
radix_sort(int *a, size_t size)
{
   if(size == 0)
      return;

   int largest = a[0];
   for(size_t i(1); i < size; ++i)
      largest = max(largest, a[i]);

   int count[10];
   int output[size];
   int exp = 1;

   while(exp < largest) {
      // do one round
      for(size_t i(0); i < 10; ++i)
         count[i] = 0;
      for(size_t i(0); i < size; ++i)
         count[(a[i]/exp)%10]++;
      for(size_t i(1); i < 10; ++i)
         count[i] += count[i - 1];

      for(int i(size-1); i>= 0; --i) {
         int n = (a[i]/exp)%10;
         int c = count[n] - 1;
         output[c] = a[i];
         count[n] = count[n] - 1;
      }

      for(size_t i(0); i < size; ++i)
         cout << output[i] << " ";
      cout << endl;

      memcpy(a, output, sizeof(int)*size);
      exp *= 10;
   }
}

int
main(int argc, char **argv)
{
   int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
   size_t size = sizeof(arr)/sizeof(int);
   radix_sort(arr, size);
   return 0;
}
