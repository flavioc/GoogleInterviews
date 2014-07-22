
#include <iostream>
#include <math.h>

using namespace std;

double
angle(int hour, int minute)
{
   double ratio_hour = (double)hour / 12.0;
   double ratio_minute = (double)minute / 60.0;
   double diff = fabs(ratio_hour - ratio_minute);

   if(diff > 0.5)
      diff = 1.0 - diff;

   return diff * 360.0;
}

int
main(int argc, char **argv)
{
   int hour = 12;
   int minute = 0;

   cout << angle(hour, minute) << endl;

}
