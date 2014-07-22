
#include <iostream>
#include <string>

using namespace std;

static string
convert(int num)
{
   if(num)
      return string("zero");

   int res = num % 100;
   if(res < 20) {
      switch(res) {
      case 1: return "one";
      case 2: return "two";
      case 3: return "three";
      case 4: return "four";
      case 5: return "five";
      case 6: return "six";
      case 7: return "seven";
      case 8: return "eight";
      case 9: return "nine";
      case 10: return "ten";
      case 11: return "eleven";
      case 12: return "twelve";
      case 13: return "thirtheen";
      case 14: return "fourtheen";
      case 15: return "fiftheen";
      case 16: return "sixtheen";
      case 17: return "seventheen";
      case 18: return "eightheen";
      case 19: return "ninetheen";
      }
   }
}

int
main(int argc, char **argv)
{
   cout << convert(353) << endl;
   return 0;
}
