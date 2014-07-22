
#include <iostream>

using namespace std;

static void
makeHeap(int *a, int size)
{
   if(size == 0)
      return;

   // find last level
   int k = 2;

   while(k - 1 < size)
      k <<= 1;
   // go back one level
   k >>= 1;
   int pos = k - 1;

   do {
      k >>= 1;
      pos = k - 1;
      for(int i(0); i < k; ++i) {
         int lpos = ((pos + i) << 1) + 1;
         if(lpos < size) {
            int left(a[lpos]);
            if(left < a[pos + i])
               swap(a[pos + i], a[lpos]);
            int rpos = lpos + 1;
            if(rpos < size) {
               int right(a[rpos]);
               if(right < a[pos + i])
                  swap(a[pos + i], a[rpos]);
            }
         }
      }
   } while (pos > 0);
}

int
main(int argc, char **argv)
{
   int array[] = {1, 4, 20, 6, 10, 3, 40};
   makeHeap(array, sizeof(array)/sizeof(int));
   for(int i(0); i < sizeof(array)/sizeof(int); ++i)
      cout << array[i] << " ";
   cout << endl;
   return 0;
}
