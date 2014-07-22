
#include <iostream>

using namespace std;

static int coins[] = {1, 2, 5, 10, 20, 50};
static int N = sizeof(coins)/sizeof(int);

static int
findMinCoins(const int cents)
{
   if(cents == 0)
      return 0;

   int best = 1000;
   for(size_t i(0); i < N; ++i) {
      const int c = coins[i];
      if(cents >= c) {
         const int new_result(findMinCoins(cents - c) + 1);

         if(new_result < best)
            best = new_result;
      }
   }
   return best;
}

static int
findMinCoinsDynamic(const int cents)
{
   int table[cents+1];
   table[0] = 0;
   for(size_t m(1); m <= cents; ++m) {
      table[m] = 99999;
      for(size_t i(0); i < N; ++i) {
         const int c = coins[i];
         if(m >= c) {
            table[m] = min(table[m], table[m-c]+1);
         }
      }
   }
   return table[cents];
}

int
main(int argc, char **argv)
{
   cout << findMinCoinsDynamic(7) << endl;
   return 0;
}
