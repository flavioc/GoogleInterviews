
#include <iostream>

using namespace std;

static int
max_subarray(int *a, size_t size)
{
   int max_ending_here = 0;
   int max_so_far = 0;
   size_t best_start = 0;
   size_t best_len = 0;
   size_t current_start = 0;
   for(size_t i(0); i < size; ++i) {
      if(max_ending_here + a[i] <= 0) {
         max_ending_here = 0;
         current_start = i + 1;
      } else {
         max_ending_here = max_ending_here + a[i];
         if(max_ending_here > max_so_far) {
            max_so_far = max_ending_here;
            best_start = current_start;
            best_len = i - current_start + 1;
         }
      }
   }
   cout << best_start << " " << best_len << endl;
   return max_so_far;
}

int
main(int argc, char **argv)
{
   int a[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
   size_t size_a = sizeof(a) / sizeof(int);

   cout << max_subarray(a, size_a) << endl;
   return 0;
}
