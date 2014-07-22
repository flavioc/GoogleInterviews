
#include <iostream>

using namespace std;

static void
count_sort(int *a, const size_t size)
{
   int c[size];
   int b[size];

   for(size_t i(0); i < size; ++i)
      c[i] = 0;
   for(size_t i(0); i < size; ++i)
      c[a[i]]++;

   for(size_t i(1); i < size; ++i)
      c[i] += c[i-1];
   for(size_t i(0); i < size; ++i) {
      int item = a[i];
      int count = c[item];
      b[count - 1] = item;
      c[item]--;
   }

   for(size_t i(0); i < size; ++i) {
      cout << b[i] << " ";
   }
   cout << endl;
}

int
main(int argc, char **argv)
{
   int a[] = {4, 2, 4, 1, 3, 5, 0};
   size_t size = sizeof(a) / sizeof(int);
   count_sort(a, size);
   return 0;
}
