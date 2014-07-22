
#include <iostream>

using namespace std;

static int
trailingZeros(int n)
{
   int x = 5;
   int total = 0;
   while(n / x > 0) {
      total += n / x;
      x *= 5;
   }
   return total;
}

int
main(int argc, char **argv)
{
   cout << trailingZeros(23) << endl;
   cout << trailingZeros(101) << endl;
   cout << trailingZeros(1000) << endl;
   cout << trailingZeros(4617) << endl;
   return 0;
}
