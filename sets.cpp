
#include <iostream>
#include <set>

using namespace std;

static set<int>
set_union(set<int>& a, set<int>& b)
{
   set<int>::iterator ia(a.begin()), ib(b.begin());
   set<int> result;

   while(ia != a.end() && ib != b.end()) {
      if(*ia == *ib) {
         result.insert(*ia);
         ia++;
         ib++;
      } else {
         while(ia != a.end() && *ia < *ib) {
            result.insert(*ia);
            ia++;
         }
         if(ia != a.end()) {
            while(ib != b.end() && *ib < *ia) {
               result.insert(*ib);
               ib++;
            }
         }
      }
   }

   for(; ia != a.end(); ++ia)
      result.insert(*ia);
   for(; ib != b.end(); ++ib)
      result.insert(*ib);

   return result;
}

static set<int>
set_inter(set<int>& a, set<int>& b)
{
   set<int>::iterator ia(a.begin()), ib(b.begin());
   set<int> result;

   while(ia != a.end() && ib != b.end()) {
      if(*ia == *ib) {
         result.insert(*ia);
         ia++;
         ib++;
      } else {
         while(ia != a.end() && *ia < *ib) {
            ia++;
         }
         if(ia != a.end()) {
            while(ib != b.end() && *ib < *ia) {
               ib++;
            }
         } else {
            break;
         }
      }
   }

   return result;
}

int
main(int argc, char **argv)
{
   set<int> a;
   a.insert(1);
   a.insert(2);
   a.insert(3);
   set<int> b;
   b.insert(4);
   b.insert(1);
   b.insert(5);
   set<int> r = set_union(a, b);
   for(set<int>::iterator it(r.begin()), end(r.end()); it != end; ++ it)
      cout << *it << endl;
   r = set_inter(a, b);
   for(set<int>::iterator it(r.begin()), end(r.end()); it != end; ++ it)
      cout << *it << endl;
   return 0;
}
