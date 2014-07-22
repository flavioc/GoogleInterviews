
#include <iostream>
#include <cstring>

using namespace std;

char *str = NULL;

static int parse_a(int, int);
static int parse_b(int, int);
static int parse_c(int, int);

static int
parse_a(int pos, int size)
{
   if(pos == size)
      return -1;

   if(str[pos] == 'a') {
      pos++;
      pos = parse_b(pos, size);
      if(pos == -1)
         return -1;
      return parse_c(pos, size);
   } else 
      return -1;
}

static int
parse_b(int pos, int size)
{
   if(pos == size)
      return -1;

   if(str[pos] == 'c') {
      pos++;
      if(pos < size) {
         if(str[pos] == 'd') {
            pos++;
            return pos;
         } else
            return pos;
      } else
         return pos;
   } else
      return -1;
}

static int
parse_c(int pos, int size)
{
   if(pos == size)
      return -1;

   if(str[pos] == 'd') {
      pos++;
      if(pos == size)
         return -1;
      if(str[pos] == 'f')
         return pos + 1;
      else
         return -1;
   } else if(str[pos] == 'e') {
      pos++;
      if(pos == size)
         return -1;
      if(str[pos] == 'g')
         return pos + 1;
      else
         return -1;
   } else {
      return -1;
   }
}

int
main(int argc, char **argv)
{
   str = "acddf";
   cout << parse_a(0, strlen(str)) << endl;
   return 0;
}
