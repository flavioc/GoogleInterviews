
#include <iostream>

using namespace std;

int
main(int argc, char **argv)
{
   int arr[] = {1, 2, 3, 4,
                5, 6, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16};
   int size = 4;
   // first pass
   for(size_t i(0); i < size; ++i) {
      for(size_t j(0); j < i + 1; ++j) {
         int x = i - j;
         int y = j;
         cout << arr[x * size + y] << endl;
      }
   }
   cout << endl;
   // second pass
   for(size_t i(size - 1); i > 0; --i) {
      for(size_t j(0); j < i; ++j) {
         int x = (size - 1) - j;
         int y = size - i + j;
         cout << arr[x * size + y] << endl;
      }
   }
   return 0;
}
