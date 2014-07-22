
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

static int
count(int *a, size_t size, int x)
{
   int l = 0, r = size - 1;
   int mid;
   bool found = false;

   while(l <= r) {
      mid = (l + r) / 2;
      if(a[mid] == x) {
         found = true;
         break;
      } else if(a[mid] > x) {
         r = mid - 1;
      } else {
         l = mid + 1;
      }
   }

   if(found) {
      int total = 1; // include mid
      // find left
      for(int i(mid-1); i >= 0; --i) {
         if(a[i] == x)
            total++;
      }
      for(int i(mid+1); i < size; ++i) {
         if(a[i] == x)
            total++;
      }
      return total;
   }
   return 0;
}

static void
largestSubarray(int *a, size_t size)
{
   size_t bestLen(1);
   size_t bestStart(0);
   size_t current_len(1);
   size_t current_start(0);

   for(size_t i(1); i < size; ++i) {
      if(a[i] < a[i-1]) {
         current_len = 1;
         current_start = i;
      } else {
         ++current_len;
         if(current_len > bestLen) {
            bestLen = current_len;
            bestStart = current_start;
         }
      }
   }

   cout << "largest start " << bestStart << " len " << bestLen << endl;
}

#if 0
static void
findSep(int *a, size_t size)
{
   // return index of the start of the second sorted subarray
   // 1 2 3 4 1 2
   // returns 4
   int l = 0, r = size - 1;

   while(l < r) {
      int mid = (left + right) / 2;
      if(a[mid] > a[r]) {
         l = mid + 1;
      } else if(a[mid] < a[l]) {
         r = mid - 1;
      } else if(a[mid] == a[l]) {

      }
   }
}

static void
findIntCircular(int *a, size_t size)
{


}
#endif

static void
findPairsSmallerThan(int *a, int n, int t)
{
   for(size_t i(0); i < n && a[i] < t; ++i) {
      for(size_t j(i + 1); j < n && a[i]+a[j] < t; ++j) {
         cout << "(" << a[i] << ", " << a[j] << ")" << endl;
      }
   }
}

static void
findPairsEqualTo(int *a, int n, int t)
{
   int l = 0, r = n - 1;
   int k;

   while(l < r) {
      k = a[l] + a[r];
      if(k == t) {
         cout << "(" << a[l] << ", " << a[r] << ")" << endl;
         l++;
      } else if(k > t) {
         r--;
      } else {
         l++;
      }
   }
}

static void
mergeArrays(int *a, int *b, int n)
{
   // size b is 2*n
   int left_a = n;
   int left_b = n;
   int pos_a = 0;
   int pos_b = n;
   int pos = 0;

   memcpy(b + n, b, sizeof(int) * n);

   while(pos_a < n && pos_b < 2*n) {
      int va = a[pos_a];
      int vb = b[pos_b];

      if(va < vb) {
         b[pos++] = va;
         pos_a++;
      } else {
         b[pos++] = vb;
         pos_b++;
      }
   }
   // copy remaining
   if(pos_a < n) {
      // need copy remaining a's
      memcpy(b + pos, a + pos_a, sizeof(int) * (n - pos_a));
   } else if(pos_b < 2*n) {
      memcpy(b + pos, b + pos_b, sizeof(int) * (2*n - pos_b));
   }

   for(size_t i(0); i < 2 * n; ++i) {
      cout << b[i] << " ";
   }
   cout << endl;
}

static void
findSmallestWindow(int *a, int na, int *b, int nb, int *c, int nc)
{
   int pa = 0;
   int pb = 0;
   int pc = 0;
   int best_start = 0;
   int best_len = na + nb + nc;

   do {
      int av = a[pa], bv = b[pb], cv = c[pc];
      int start = min(av, min(bv, cv));
      int end = max(av, max(bv, cv));
      int len = end - start + 1;
      if(len < best_len) {
         best_len = len;
         best_start = start;
      }
      int *best_pos = NULL;
      int *size_best = NULL;
      int *other1_pos = NULL;
      int *other1_size = NULL;
      int *other1_val = NULL;
      int *other2_pos = NULL;
      int *other2_size = NULL;
      int *other2_val = NULL;

      if(start == av) {
         best_pos = &pa;
         size_best = &na;
         other1_pos = &pb;
         other1_size = &nb;
         other1_val = &bv;
         other2_pos = &pc;
         other2_size = &nc;
         other2_val = &cv;
      } else if(start == bv) {
         best_pos = &pb;
         size_best = &nb;
         other1_pos = &pa;
         other1_size = &na;
         other1_val = &av;
         other2_pos = &pc;
         other2_size = &nc;
         other2_val = &cv;
      } else if(start == cv) {
         best_pos = &pc;
         size_best = &nc;
         other1_pos = &pb;
         other1_size = &nb;
         other1_val = &bv;
         other2_pos = &pa;
         other2_size = &na;
         other2_val = &av;
      }

      if(*best_pos < *size_best - 1) {
         *best_pos = *best_pos + 1;
      } else {
         if(*other1_val < *other2_pos) {
            // other1 best
            if(*other1_pos < *other1_size-1) {
               *other1_pos = *other1_pos + 1;
            } else {
               *other2_pos = *other2_pos + 1;
            }
         } else {
            // other2 best
            if(*other2_pos < *other2_size - 1) {
               *other2_pos = *other2_pos + 1;
            } else {
               *other1_pos = *other1_pos + 1;
            }
         }
      }


   } while(!(pa == na - 1 && pb == nb - 1 && pc == nc - 1));
}

static int
findKSmallest(int *a, int *b, int na, int nb, int k)
{
   if(k >= na + nb)
      return -1;
   if(k < 0)
      return -1;

   int la = 0, ra = na - 1;
   int lb = 0, rb = nb - 1;

   while(la <= ra && lb <= rb) {
      cout << " ==== " << endl;
      cout << "a " << la << " " << ra << endl;
      cout << "b " << lb << " " << rb << endl;

      int mida = (la + ra)/2;
      int midb = (lb + rb)/2;

      int before_a = mida - la;
      int before_b = midb - lb;

      if(before_a + before_b > k) {
         if(a[mida] > b[midb])
            ra = mida - 1;
         else
            rb = midb - 1;
      } else {
         if(a[mida] < b[midb]) {
            la = mida + 1;
            k -= before_a;
         } else {
            lb = midb + 1;
            k -= before_b;
         }
      }
   }
   cout << " ==== " << k << endl;
   cout << "a " << la << " " << ra << endl;
   cout << "b " << lb << " " << rb << endl;

   if(la <= ra) return a[la + k - 1];
   else return b[lb + k - 1];
}

int
main(int argc, char **argv)
{
   int array[] = {1, 2, 3, 1, 2};
   cout << count(array, sizeof(array)/sizeof(int), 1) << endl;
   largestSubarray(array, sizeof(array)/sizeof(int));
   int x[] = {1, 2, 3, 4, 5, 6};
   findPairsSmallerThan(x, 6, 5);
   int a[] = {1, 3, 6};
   int b[] = {0, 4, 5, 100, 100, 100};
   mergeArrays(a, b, 3);
   cout << findKSmallest(a, b, 3, sizeof(b)/sizeof(int), 0) << endl;
   cout << findKSmallest(a, b, 3, sizeof(b)/sizeof(int), 1) << endl;
   cout << findKSmallest(a, b, 3, sizeof(b)/sizeof(int), 2) << endl;
   cout << findKSmallest(a, b, 3, sizeof(b)/sizeof(int), 3) << endl;
   cout << findKSmallest(a, b, 3, sizeof(b)/sizeof(int), 4) << endl;
   cout << findKSmallest(a, b, 3, sizeof(b)/sizeof(int), 5) << endl;
   return 0;
}
