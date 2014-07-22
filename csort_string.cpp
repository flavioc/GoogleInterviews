
#include <iostream>
#include <cstring>

using namespace std;

static void
count_sort(char *str, size_t len)
{
   if(len == 0)
      return;
   if(len == 1)
      return;

   char min = str[0];
   char max = str[0];
   for(size_t i(1); i < len; ++i) {
      if(str[i] < min)
         min = str[i];
      if(str[i] > max)
         max = str[i];
   }

   const char range = max - min + 1;
   int count[range];
   for(size_t i(0); i < range; ++i)
      count[i] = 0;
   for(size_t i(0); i < len; ++i)
      count[str[i] - min]++;
   for(size_t i(1); i < range; ++i) {
      count[i] += count[i - 1];
      cout << count[i] << " ";
   }
   cout << endl;

   char out[len + 1];
   out[len] = '\0';

   for(int i(len - 1); i >= 0; --i) {
      int key = str[i]-min;
      int c = count[key] - 1;
      out[c] = str[i];
      count[key] = c;
   }

   printf("%s\n", out);
}

int
main(int argc, char **argv)
{
   char *str = "fsdjfioahj";
   count_sort(str, strlen(str));
   return 0;
}
