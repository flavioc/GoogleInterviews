
#include <iostream>
#include <map>
#include <cmath>
#include <cstring>

using namespace std;

static pair<int, int>
int_division(int a, int b)
{
   int sign = (a * b) < 0 ? -1 : 1;
   int aa = abs(a), bb = abs(b);
   int left = 0, right = aa;
   int mid;

   while(left <= right) {
      mid = (left + right) / 2;
      if(mid*bb == aa)
         return make_pair(mid*sign, 0);
      else if(mid*bb < aa) {
         left = mid + 1;
      } else {
         right = mid - 1;
      }
   }
   --left;
   left *= sign;
   return make_pair(left, sign * (aa - left*bb));
}

static double
square_root(double num)
{
   double left = 0, right = num;
   while(left + 0.0001 < right) {
      double mid = (left + right)/2;
      if(mid * mid > num)
         right = mid;
      else
         left = mid;
   }
   return left;
}

static double
angleClock(int hours, int minutes)
{
   double percHours = (double)hours / 12.0;
   double percMinutes = (double)minutes / 60.0;

   double angleHours = percHours * M_PI * 2.0;
   double angleMinutes = percMinutes * M_PI * 2.0;

   double angle;
   if(angleMinutes > angleHours)
      angle = angleMinutes - angleHours;
   else
      angle = angleHours - angleMinutes;

   if(angle > M_PI)
      return 2.0*M_PI - angle;
   else
      return angle;
}

static int
fastExp(int a, int b)
{
   if(b == 0)
      return 1;
   if(b == 1)
      return a;

   if(b & 0x01) {
      b--;
      int res = fastExp(a, b / 2);
      return res * res * a;
   } else {
      int res = fastExp(a, b/2);
      return res * res;
   }
}

static int
fastExp2(int a, int b)
{
   if(b == 0)
      return 1;
   if(b == 1)
      return a;
   int res = 1;

   while(b > 0) {
      if(b & 0x01) {
         res *= a;
         b--;
      }
      res *= res;
      b >>= 1;
   }
   return res;
}

static int
findZeros(int n)
{
   int r = 0;
   while(n) {
      n /= 5;
      r += n;
   }
   return r;
}

static double
fastPowIter(double x, int y)
{
   if(y == 0)
      return 1.0;
   if(y == 1)
      return x;
   double res = 1.0;
   while(y > 0) {
      if(y & 1) {
         res *= x;
         y--;
      }
      res *= res;
      y /= 2;
   }
   return res;
}

static double
fastPow(double x, int y)
{
   if(y == 0)
      return 1.0;
   if(y == 1)
      return x;
   double t = fastPow(x, y / 2);
   t *= t;
   if(y & 1)
      t *= x;
   return t;
}

static double
fastPowerMain(double x, int y)
{
   if(y < 0) {
      if(x == 0.0)
         return 0.0;
      x = 1.0 / x;
   }
   return fastPow(x, y);
}

struct Rect {
   int x1, y1;
   int x2, y2;
};

static bool
intersects(const Rect& r1, const Rect& r2)
{
   if(r2.x1 > r1.x2)
      return false;
   if(r2.x2 < r1.x1)
      return false;
   if(r1.y2 > r2.y2)
      return false;
   if(r2.y2 > r1.y1)
      return false;
   return true;
}

static int
gcd(int a, int b)
{
   if(a < b)
      swap(a, b);
   while (b) {
      int t = b;
      b = a % b;
      a = t;
   }
   return a;
}

static int
lcm(int n, int m) {
   return n / gcd(n, m) * m;
}

static void
print_subsets0(int *a, size_t i, size_t size, int *visit)
{
   if(i == size) {
      for(size_t i(0); i < size; ++i) {
         if(visit[i])
            cout << a[i] << " ";
      }
      cout << endl;
      return;
   }

   visit[i] = 0;
   print_subsets0(a, i + 1, size, visit);
   visit[i] = 1;
   print_subsets0(a, i + 1, size, visit);
}

static void
print_subsets(int *a, size_t size)
{
   int visit[size];
   memset(visit, 0, sizeof(visit)/sizeof(int));

   print_subsets0(a, 0, size, visit);
}

int
main(int argc, char **argv)
{
   pair<int, int> p(int_division(12, 3));
   cout << p.first << "," << p.second << endl;
   cout << square_root(4) << endl;
   cout << angleClock(10, 10) << endl;
   cout << fastExp(2, 5) << endl;
   cout << fastExp2(2, 6) << endl;
   cout << findZeros(25) << endl;
   int a[] = {1, 2, 3, 4, 5};
   print_subsets(a, sizeof(a)/sizeof(int));
   return 0;
}
