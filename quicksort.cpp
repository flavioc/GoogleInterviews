
#include <iostream>

using namespace std;

static void
quicksort(int *arr, int left, int right)
{
   if(left == right)
      return;

   if(right < left)
      return;

   int piv = left + (right - left)/2;
   int pivot = arr[piv];
   int sleft = left;

   swap(arr[left], arr[piv]);
   left++;
   for(int i(left); i <= right; ++i) {
      if(arr[i] <= pivot) {
         swap(arr[i], arr[left]);
         left++;
      }
   }
   left--;
   swap(arr[left], arr[sleft]);

   quicksort(arr, sleft, left - 1);
   quicksort(arr, left + 1, right);
}

int
main(int argc, char **argv)
{
   int arr[] = {2, 1, 65, 21, 13};
   const size_t size = sizeof(arr)/sizeof(int);
   quicksort(arr, 0, size - 1);
   for(size_t i(0); i < size; ++i)
      cout << arr[i] << " ";
   cout << endl;
   return 0;
}
