
#include <iostream>

using namespace std;

static void
generate_brackets0(int n, char *typs, int i, int total, bool print)
{
   if(n == 0) {
      if(!print)
         return;
      for(size_t j(0); j < total; ++j) {
         cout << (char)typs[j];
      }
      cout << endl;
      return;
   }

   size_t rest = n - 1;
   for(size_t j(0); j <= rest; ++j) {
      typs[i] = '(';
      typs[i + 1 + 2 * j] = ')';

      generate_brackets0(j, typs, i + 1, total, j == rest);
      generate_brackets0(rest-j, typs, i + 1 + 2 * j + 1, total, j > 0);
   }
}

static void
generate_brackets(int n)
{
   char typs[2*n];

   generate_brackets0(n, typs, 0, 2 * n, true);
}

int
main(int argc, char **argv)
{
   generate_brackets(3);
   return 0;
}
