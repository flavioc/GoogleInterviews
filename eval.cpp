
#include <iostream>

using namespace std;

class expr
{
   public:

      virtual int eval(void) = 0;
};

class constant: public expr
{
   private:

      int val;
   public:

      int eval(void) { return val; }

      explicit constant(const int v): val(v) {}
};

class pluse: public expr
{
   private:

      expr *a, *b;

   public:

      int eval(void) {
         return a->eval() + b->eval();
      }

      explicit pluse(expr* _a, expr* _b):
         a(_a), b(_b)
      {
      }
};

int
main(int argc, char **argv)
{
   constant p(1);
   constant q(2);
   pluse r(&p, &q);
   pluse s(&r, &r);

   cout << s.eval() << endl;
   return 0;
}
