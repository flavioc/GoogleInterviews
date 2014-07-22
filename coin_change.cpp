
#include <iostream>

using namespace std;

int coins[] = {1, 2, 5, 10, 20, 50};
int NUM_COINS = sizeof(coins)/sizeof(int);

int
ways(int cents)
{
   int ways[cents+1];
   ways[0] = 1;
   for(size_t i(1); i <= cents; ++i)
      ways[i] = 0;

   for (int i = NUM_COINS-1 ; i >= 0 ; i--)
      for (int am = coins[i] ; am <= cents ; am++)
         ways[am] += ways[am-coins[i]];
   return ways[cents];
}

int
waysRec(int cents, int N)
{
   if(cents == 0)
      return 1;
   if(cents < 0)
      return 0;

   if(N <= 0 && cents >= 1)
      return 0;

   return waysRec(cents, N - 1) + waysRec(cents - coins[N-1], N);
}

int
main(int argc, char **argv)
{
   cout << ways(4) << endl;
   cout << waysRec(4, NUM_COINS) << endl;
   return 0;
}
