
#include <iostream>
#include <list>

using namespace std;

class obj
{
   public:

      list<int> ls1;
      list<int> ls2;

      class iterator
      {
         private:
            bool in_first;
            list<int>::iterator it;
            list<int>* ls1;
            list<int>* ls2;

         public:

            int operator*(void) const { return *it; }

            void operator++(int) {
               if(in_first) {
                  it++;
                  if(it == ls1->end()) {
                     it = ls2->begin();
                     in_first = false;
                  }
               } else {
                  it++;
               }
            }

            bool operator==(const iterator& other) const {
               if(in_first != other.in_first)
                  return false;
               return it == other.it;
            }

            bool operator!=(const iterator &other) const
            {
               return !operator==(other);
            }

            explicit iterator(list<int>* l1, list<int>* l2): ls1(l1), ls2(l2) {
               in_first = true;
               it = ls1->begin();
               if(it == ls1->end())
                  it = ls2->begin();
            }

            explicit iterator(bool a, list<int>* l1, list<int>* l2):
               in_first(false), ls1(l1), ls2(l2)
            {
               in_first = false;
               it = ls2->end();
            }
      };

      iterator begin(void) { return iterator(&ls1, &ls2); }
      iterator end(void) { return iterator(false, &ls1, &ls2); }

      void add1(int a) { ls1.push_back(a); }
      void add2(int b) { ls2.push_back(b); }

      explicit obj(void) {}
};

int
main(void)
{
   obj a;
   a.add1(2);
   a.add2(4);
   a.add1(3);
   a.add2(10);
   for(obj::iterator it(a.begin()), end(a.end()); it != end; it++) {
      cout << *it << endl;
   }
   return 0;
}
