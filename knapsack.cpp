
#include <iostream>

using namespace std;

int nitems[] = {1, 1, 1, 1, 1};
int weights[] = {1, 2, 3, 4, 5};
int values[] = {20, 2, 50, 1, 40};
int N = sizeof(weights)/sizeof(int);

static void
dynamic_knapsack(const int maxweight, int *weight, int *value)
{
   int K[N + 1][maxweight + 1];

   for(size_t i(0); i <= N; ++i) {
      for(size_t w(0); w <= maxweight; ++w) {
         if(i == 0 || w == 0)
            K[i][w] = 0;
         else if(weights[i-1] <= w)
            K[i][w] = max(values[i-1] + K[i-1][w - weights[i-1]], K[i-1][w]);
         else
            K[i][w] = K[i-1][w];
      }
   }

   for(size_t i(0); i <= N; ++i) {
      cout << i << " items ";
      for(size_t m(0); m <= maxweight; ++m) {
         cout << K[i][m] << " ";
      }
      cout << endl;
   }

   *value = K[N][maxweight];
}

static void
knapsack(const int maxweight, int *weight, int *value)
{
   int best_value = 0;
   int best_weight = 0;

   for(size_t i(0); i < N; ++i) {
      int w = weights[i];
      int v = values[i];
      int it = nitems[i];
      if(it > 0 && maxweight >= w && it > 0) {
         int thisweight, thisvalue;
         nitems[i]--;
         knapsack(maxweight - w, &thisweight, &thisvalue);
         nitems[i]++;
         thisweight += w;
         thisvalue += v;
         if(thisvalue > best_value) {
            best_value = thisvalue;
            best_weight = thisweight;
         }
      }
   }

   *weight = best_weight;
   *value = best_value;
}

int
main(int argc, char **argv)
{
   int weight, value;
   knapsack(4, &weight, &value);
   cout << weight << " " << value << endl;
   dynamic_knapsack(4, &weight, &value);
   cout << weight << " " << value << endl;
}
