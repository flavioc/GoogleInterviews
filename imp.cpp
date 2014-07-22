
#include <iostream>
#include <cstdlib>
#include <stdint.h>

using namespace std;

static bool
isPalindrome(int num)
{
   int n = 1;
   int total = 1;
   while(n * 10 < num) {
      n *= 10;
      ++total;
   }

   int half = total/2;
   for(int i(0); i < half; ++i) {
      int significant = num / n;
      int least = num % 10;
      if(significant != least)
         return false;
      num = num % n;
      num = num / 10;
      n /= 100;
   }
   return true;
}

static void
print_bytes(uint32_t n)
{
   for(size_t i(0); i < 32; ++i) {
      if(n&0x80000000)
         cout << "1";
      else
         cout << "0";
      n <<= 1;
   }
   cout << endl;
}

static uint32_t
shift_right(uint32_t r)
{
   return (r >> 1) | ((r & 0x01) << 31);
}

static uint32_t
reverse_bits(uint32_t r)
{
   uint32_t result = 0;
   for(size_t i(0); i < 16; ++i) {
      result |= (r & (1 << i)) << (31 - 2 * i);
      result |= (r & (1 << 31 - i)) >> (31 - 2 * i);
   }
   return result;
}

static int
count_bits(uint32_t r)
{
   int count;
   for(count = 0; r; ++count)
      r &= r - 1;
   return count;
}

#define SIZE 4
static void
floodMatrix(int bits[SIZE][SIZE], int i, int j)
{
   bits[i][j] = 0;
   if(j < (SIZE - 1)) {
      if(bits[i][j+1])
         floodMatrix(bits, i, j + 1);
   }
   if(i > 0) {
      if(bits[i-1][j]) {
         floodMatrix(bits, i - 1, j);
      }
   }
   if(i < (SIZE - 1)) {
      if(bits[i+1][j])
         floodMatrix(bits, i + 1, j);
   }
   if(j > 0) {
      if(bits[i][j-1])
         floodMatrix(bits, i, j - 1);
   }
}

static int
findGroupsOfOne(int bits[4][4])
{
   int total = 0;
   for(size_t i(0); i < SIZE; ++i) {
      for(size_t j(0); j < SIZE; ++j) {
         if(bits[i][j]) {
            floodMatrix(bits, i, j);
            total++;
         }
      }
   }
   return total;
}

static void
generate_array(int *arr, int size)
{
   int out[size * 2];
   int c = 0;
   for(int i = 0; i < size; ++i) {
      int total = 1;
      while(i < size && arr[i] == arr[i + 1]) {
         total++;
         i++;
      }
      out[c++] = total;
      out[c++] = arr[i];
   }
   for(size_t i(0); i < size; ++i)
      cout << arr[i] << " ";
   cout << endl;
   for(size_t i(0); i < c; ++i)
      cout << out[i] << " ";
   cout << endl;
}

static int
hamming_distance(int a, int b)
{
   int res = 0, i, j;
   if(b < a)
      swap(a, b);

   while (a > 0) {
      i = a % 10, j = b % 10;
      if(j != i)
         res++;
      a /= 10;
      b /= 10;
   }

   while(b > 0) {
      res++;
      b /= 10;
   }
   return res;
}

static void
partition_zeros(int *a, size_t size)
{
   size_t c = 0;
   for(size_t i(0); i < size; ++i) {
      if(a[i] == 0) {
         swap(a[i], a[c]);
         c++;
      }
   }
}

static void
product(int *a, size_t size)
{
   int n_zeros = 0;
   int prod = 1;
   for(size_t i(0); i < size; ++i) {
      if(a[i] == 0) {
         n_zeros++;
      } else {
         prod *= a[i];
      }
   }

   if(n_zeros > 1) {
      for(size_t i(0); i < size; ++i)
         a[i] = 0;
   } else if(n_zeros == 1) {
      for(size_t i(0); i < size; ++i) {
         if(a[i] == 0)
            a[i] = prod;
         else
            a[i] = 0;
      }
   } else {
      for(size_t i(0); i < size; ++i) {
         a[i] = prod/a[i];
      }
   }
}

static void
iterateMatrix(int m[SIZE][SIZE])
{
   int size = SIZE;
   int row = 0, col = 0;
   for(int size(SIZE); size > 0; size -= 2) {
      for(; col < row + size; ++col)
         cout << m[row][col] << endl;
      --col;
      ++row;
      int startrow = row;
      for(; row < startrow + (size-1); ++row)
         cout << m[row][col] << endl;
      row--;
      col--;
      int startcol = col;
      for(; col > startcol - (size - 1); --col)
         cout << m[row][col] << endl;
      col++;
      row--;
      for(; row > startcol - (size - 2); --row)
         cout << m[row][col] << endl;
      ++col;
      ++row;
   }
}

static int
multiply_by_7(int num)
{
   return (num << 3) - num;
}

static int
multiply_by_others(int *a, int n)
{
   int ll[n];
   int rr[n];

   int total = 1;
   for(int i(n-1); i >= 0; --i) {
      total *= a[i];
      rr[i] = total;
   }

   total = 1;
   for(int i(0); i < n; ++i) {
      total *= a[i];
      ll[i] = total;
   }

   for(size_t i(0); i < n; ++i) {
      int left = 1;
      int right = 1;
      if(i > 0)
         left = ll[i-1];
      if(i < n-1)
         right = rr[i+1];
      cout << left << " " << right << endl;
   }
   cout << endl;
}

int
main(int argc, char **argv)
{
   cout << isPalindrome(12344321) << endl;
   uint32_t i = 123533434;
   print_bytes(i);
   print_bytes(shift_right(i));
   print_bytes(reverse_bits(i));
   int bitMatrix[4][4] = {{1, 1, 0, 1},
                          {1, 0, 0, 1},
                          {0, 1, 0, 1},
                          {0, 1, 0, 1}};
   cout << findGroupsOfOne(bitMatrix) << endl;
   int a[] = {2, 2, 3, 1, 2, 2};
   generate_array(a, sizeof(a) / sizeof(int));
   cout << hamming_distance(12512, 212) << endl;
   int b[] = {1, 5, 2, 3, 3};
   partition_zeros(b, sizeof(b)/sizeof(int));
   for(size_t i(0); i < sizeof(b)/sizeof(int); ++i)
      cout << b[i] << " ";
   cout << endl;
   product(b, sizeof(b)/sizeof(int));
   for(size_t i(0); i < sizeof(b)/sizeof(int); ++i)
      cout << b[i] << " ";
   cout << endl;
   int matrix[4][4] = {{1, 2, 3, 4},
                          {12, 13, 14, 5},
                          {11, 16, 15, 6},
                          {10, 9, 8, 7}};
   iterateMatrix(matrix);
   cout << multiply_by_7(7) << endl;
   int coiso[] = {1, 2, 3};
   multiply_by_others(coiso, 3);
   return 0;
}
