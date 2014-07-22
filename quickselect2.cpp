
#include <iostream>
#include <assert.h>

using namespace std;

static int
quickselect(int *arr, int left, int right, int nth)
{
   if(right < left)
      return -1;

   cout << "qselect " << left << " " << right << endl;
   assert(nth >= left);
   assert(nth <= right);
   if(right == left)
      return arr[right];

   int middle = left + (right - left)/2;
   int mid = arr[middle];
   cout << "mid " << mid << endl;
   const int ol = left, oright = right;

   swap(arr[ol], arr[middle]);
   left++;

   for(int i(ol + 1); i <= oright; ++i) {
      if(arr[i] <= mid) {
         swap(arr[i], arr[left]);
         left++;
      }
   }
   swap(arr[left-1], arr[ol]);

   cout << "left " << left << endl;
   cout << "right " << right << endl;
   if(left-1 == nth) {
      return arr[nth];
   } else if(nth < left) {
      return quickselect(arr, ol, left-1, nth);
   } else 
      return quickselect(arr, left, oright, nth);
}

static int
newQuickselect(int *arr, int left, int right, int nth)
{
   if(left > right)
      return -1;
   if(left == right)
      return arr[nth];

   int pivpos = left + (right - left)/2;
   int pivot = arr[pivpos];
   const int sleft = left;
   swap(arr[sleft], arr[pivpos]);
   left++;
   for(int i(sleft + 1); i <= right; ++i) {
      if(arr[i] <= pivot) {
         swap(arr[i], arr[left]);
         left++;
      }
   }
   left--;
   swap(arr[sleft], arr[left]);

   if(left == nth)
      return arr[nth];
   else if(nth < left)
      return newQuickselect(arr, sleft, left - 1, nth);
   else
      return newQuickselect(arr, left + 1, right, nth);
}

int
main(int argc, char **argv)
{
   int arr[] = {5, 7, 1, 2, 20};
   const size_t size = sizeof(arr)/sizeof(int);
   cout << newQuickselect(arr, 0, size - 1, 4) << endl;
   return 0;
}
