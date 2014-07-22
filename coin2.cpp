
#include <iostream>

using namespace std;

int coins[] = {1, 2, 5, 10, 20, 50, 100};
size_t N = sizeof(coins)/sizeof(int);

static int
findMinCoinsNeeded(int cents, int coins_to_use)
{
   if(cents < 0)
      return -1;
   if(coins_to_use <= 0)
      return -1;

   if(cents == 0)
      return 0;

   int without = findMinCoinsNeeded(cents, coins_to_use-1);

   int with = -1;
   if(cents >= coins[coins_to_use-1])
      with = findMinCoinsNeeded(cents - coins[coins_to_use-1], coins_to_use) + 1;

   if(without == -1)
      return with;
   else if(with == -1)
      return without;
   else
      return min(with, without);
}

static int
findMinCoinsNeeded2(int cents)
{
   int table[cents + 1];

   table[0] = 0;
   for(size_t i(1); i <= cents; ++i)
      table[i] = 99999;

   for(int i(0); i <= cents; ++i) {
      for(int j(0); j < N; ++j) {
         int coin = coins[j];
         if(coin <= i) {
            table[i] = min(table[i], table[i-coin] + 1);
         }
      }
   }

   return table[cents];
}

static int
findWaysOfMakingChange(int cents, int coin_to_use)
{
   if(cents < 0)
      return 0;
   if(coin_to_use <= 0)
      return 0;
   if(cents == 0)
      return 1;

   int without = findWaysOfMakingChange(cents, coin_to_use-1);
   int with = 0;
   int coin = coins[coin_to_use-1];

   if(coin <= cents)
      with = findWaysOfMakingChange(cents - coin, coin_to_use);

   return with + without;
}

static int
findWaysOfMakingChange2(int cents)
{
   int table[cents+1];
   table[0] = 1;
   for(size_t i(1); i <= cents; ++i)
      table[i] = 0;

   for(int i(N-1); i >= 0; --i) {
      int coin = coins[i];
      for(int j(coin); j <= cents; ++j) {
         table[j] += table[j-coin];
      }
   }
   return table[cents];
}

int
main(int argc, char **argv)
{
   int n = 2;
   cout << findMinCoinsNeeded(n, N) << endl;
   cout << findMinCoinsNeeded2(n) << endl;
   cout << findWaysOfMakingChange(n, N) << endl;
   cout << findWaysOfMakingChange2(n) << endl;
   return 0;
}
