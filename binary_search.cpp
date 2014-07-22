
#include <iostream>

using namespace std;

static int
findBinary(int *arr, size_t left, size_t right, int item)
{
   if(left > right)
      return -1;
   if(item > arr[right])
      return -1;
   if(item < arr[left])
      return -1;

   size_t range = right - left;
   size_t middle = left + range/2;
   int mid = arr[middle];

   if(mid == item)
      return middle;
   if(range == 1)
      return -1;

   if(item > mid)
      return findBinary(arr, middle, right, item);
   else
      return findBinary(arr, left, middle, item);
}

int
main(int argc, char **argv)
{
   int arr[5] = {1, 2, 2, 4, 5};
   const size_t size_arr(sizeof(arr)/sizeof(int));
   cout << findBinary(arr, 0, size_arr - 1, 3) << endl;
   return 0;
}
