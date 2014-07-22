
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

static int
findSep(int *a, int l, int r)
{
   if(r < l)
      return -1;
   cout << "===> " << l << " " << r << endl;

   if(l == r) {
      return l;
   }
   if(r == l + 1) {
      if(a[l] > a[r])
         return l;
      else
         return r;
   }

   int mid = (l + r) / 2;
   cout << a[mid] << " " << a[r] << endl;
   if(a[mid] > a[r]) {
      cout << "right" << endl;
      return findSep(a, mid, r);
   } else if(a[mid] < a[l]) {
      cout << "left" << endl;
      return findSep(a, l, mid);
   } else {
      cout << "outch" << endl;
      int x = findSep(a, l, mid);
      int y = findSep(a, mid + 1, r);

      if(x == -1)
         return y;
      if(y == -1)
         return x;
      if(a[x] > a[y])
         return x;
      else
         return y;
   }
}

static int
lcs(int *a, int n)
{
   int len[n];
   int prev[n];

   for(size_t i(0); i < n; ++i) {
      len[i] = 0;
      prev[i] = -1;
   }

   len[0] = 1;
   int really_best = 1;
   int best_end = 0;

   for(size_t i(1); i < n; ++i) {
      int value = a[i];
      // search for the largest subsequence where a[j] <= value
      bool found = false;
      int best_len;
      int best_j;
      for(size_t j(0); j < i; ++j) {
         if(a[j] <= value) {
            if(!found || len[j] > best_len) {
               found = true;
               best_len = len[j];
               best_j = j;
            }
         }
      }
      if(found) {
         prev[i] = prev[best_j];
         len[i] = best_len + 1;
         if(len[i] > really_best) {
            really_best = len[i];
            best_end = i;
         }
      } else {
         len[i] = 1;
         prev[i] = -1;
      }
   }
   cout << best_end << endl;
   return really_best;
}

static int
findBestKTwo(int *a, int *b, int sa, int sb, int k)
{
   if(k >= (sa + sb))
      return -1;
   if(k <= 0)
      return -1;
   int la = 0;
   int lb = 0;
   int ra = sa - 1;
   int rb = sb - 1;

   while(la <= ra && lb <= rb) {
      int mida = (la + ra)/2;
      int midb = (lb + rb)/2;

      int lefta = mida - la + 1;
      int leftb = midb - lb + 1;

      if(k < lefta + leftb) {
         if(a[mida] > b[midb])
            ra = mida - 1;
         else
            rb = midb - 1;
      } else {
         // k > lefta + leftb
         if(a[mida] < b[midb]) {
            k -= lefta;
            la = mida + 1;
         } else {
            k -= leftb;
            lb = midb + 1;
         }
      }
   }
   if(la <= ra) return a[la + k - 1];
   else return b[lb + k - 1];
}

static int
search(int *M, int *a, int i, int L)
{
   int j = 0;
   int k = L-1;

   while(j <= k) {
      int m = (j + k)/2;
      if(a[M[m]] <= a[i]) j = m + 1;
      else k = m - 1;
   }
   return k;
}

static int
lcsBest(int *a, int n)
{
   int m[n];
   int p[n];

   m[0] = 0;
   p[0] = -1;
   int L = 1;

   for(size_t i(1); i < n; ++i) {
      int j = search(m, a, i, L);
      if(j == -1) p[i] = -1;
      else p[i] = m[j];

      if(j == L-1 || a[i] < a[m[j+1]]) {
         m[j+1] = i;
         if(j + 2 > L) L = j + 2;
      }
   }
}

static string
longest_repeating_substring(const string& s)
{
   vector<string> vec;
   vec.push_back("");
   for(int i(s.length()-1); i >= 0; --i) {
      vec.push_back(string(s.c_str() + i, s.c_str() + s.length()));
      cout << vec[vec.size()-1] << endl;
   }

   size_t longest = 0;
   sort(vec.begin(), vec.end());
   for(size_t i(0); i < vec.size(); ++i) {
      string str = vec[i];
      for(size_t j(i+1); j < vec.size(); ++j) {
         string str2 = vec[j];
         bool match = false;
         for(size_t k(0); k < str2.length(); ++k) {

         }
      }
   }

   return string("");
}

static int
findMajority(int *a, int n)
{
   int cur = a[0];
   int maj = a[0];
   int ctn = 1;

   for(size_t i(1); i < n; ++i) {
      if(cur == a[i]) {
         ++ctn;
      } else {
         --ctn;
         if(ctn == 0) {
            cur = a[++i];
            maj = a[i];
            ctn = 1;
         }
      }
   }
   return maj;
}

int
main(int argc, char **argv)
{
   int a[] = {0, 0, 0, 0, 1, 0, 0};
   size_t sa = sizeof(a)/sizeof(int);
   cout << findSep(a, 0, sa -1) << endl;
   int b[] = {1, 2, 0, 2, 3, 4, 5, 1};
   cout << lcs(b, sizeof(b)/sizeof(int)) << endl;
   cout << "==============" << endl;
   int c[] = {1, 2, 3, 4, 5};
   int d[] = {0, 2, 4, 6, 8};
   cout << findBestKTwo(c, d, sizeof(c)/sizeof(int), sizeof(d)/sizeof(int), 1) << endl;
   cout << findBestKTwo(c, d, sizeof(c)/sizeof(int), sizeof(d)/sizeof(int), 2) << endl;
   cout << findBestKTwo(c, d, sizeof(c)/sizeof(int), sizeof(d)/sizeof(int), 3) << endl;
   cout << findBestKTwo(c, d, sizeof(c)/sizeof(int), sizeof(d)/sizeof(int), 4) << endl;
   cout << findBestKTwo(c, d, sizeof(c)/sizeof(int), sizeof(d)/sizeof(int), 5) << endl;
   string s = "banana";
   longest_repeating_substring(s);
   int m[] = {1, 0, 1, 0, 0, 1, 1};
   cout << findMajority(m, 7) << endl;
   return 0;
}
