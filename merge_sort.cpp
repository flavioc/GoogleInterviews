
#include <iostream>
#include <cstring>

using namespace std;

static void
merge_sort(int *a, int n)
{
   if(n == 0)
      return;
   if(n == 1)
      return;
   if(n == 2) {
      if(a[0] > a[1])
         swap(a[0], a[1]);
      return;
   }

   int middle = n / 2;
   int *l = a;
   int *r = a + middle;
   int *lend = l + middle;
   int *rend = r + (n - middle);

   merge_sort(l, middle);
   merge_sort(r, n - middle);

   int aux[n];
   int i(0);

   // merge step
   for(; i < n; ++i) {
      if(l < lend && r < rend) {
         if(*l < *r) {
            aux[i] = *l;
            l++;
         } else {
            aux[i] = *r;
            r++;
         }
      } else if(l < lend) {
         memcpy(aux + i, l, sizeof(int)*(lend - l));
         l = lend;
         break;
      } else if(r < rend) {
         memcpy(aux + i, r, sizeof(int)*(rend - r));
         r = rend;
         break;
      }
   }
   for(size_t i(0); i < n; ++i)
      cout << aux[i] << " ";
   cout << endl;
   memcpy(a, aux, sizeof(int)*n);
}

static void
bottom_up_merge_sort(int *a, int n)
{
   if(n == 0 || n == 1)
      return;

   // swap pairs
   for(size_t i(0); i < n; i += 2) {
      if(i + 1 < n) {
         if(a[i] > a[i+1])
            swap(a[i], a[i+1]);
      }
   }
   for(size_t i(0); i < n; ++i)
      cout << a[i] << " ";
   cout << endl;
   
   int piece_size = 2;
   int aux[n];
   while (n > piece_size) {
      for(size_t i(0); i < n; i += 2 * piece_size) {
         int piece1 = i;
         int piece2 = i + piece_size;
         int piece1_end = piece2;
         int piece2_end = i + 2 * piece_size;
         if(piece2_end > n)
            piece2_end = n;
         // merge piece1 with piece2
         int pos = 0;
         for(; piece1 < piece1_end && piece2 < piece2_end; ++pos) {
            if(a[piece1] < a[piece2]) {
               aux[pos] = a[piece1];
               piece1++;
            } else {
               aux[pos] = a[piece2];
               piece2++;
            }
         }

         if(piece1 < piece1_end) {
            memcpy(aux + pos, a + piece1, sizeof(int) * (piece1_end - piece1));
            pos += piece1_end - piece1;
         }
         if(piece2 < piece2_end) {
            memcpy(aux + pos, a + piece2, sizeof(int) * (piece2_end - piece2));
            pos += piece2_end - piece2;
         }
         memcpy(a + i, aux, sizeof(int) * pos);
         for(size_t j(0); j < n; ++j)
            cout << a[j] << " ";
         cout << endl;
      }

      piece_size *= 2;
   }
}

int
main(int argc, char **argv)
{
   int a[] = {30, 2, 1, 4, 9, 3};
   bottom_up_merge_sort(a, sizeof(a)/sizeof(int));
   for(size_t i(0); i < sizeof(a)/sizeof(int); ++i)
      cout << a[i] << " ";
   cout << endl;
   return 0;
}
