#include <queue>
#include <stack>
#include <iostream>

using namespace std;

class newstack
{
   public:

      queue<int> q1;
      queue<int> q2;
      bool use_one;

      void push(int n) {
         if(use_one)
            q1.push(n);
         else
            q2.push(n);
      }

      int pop(void) {
         int el;
         if(use_one) {
            while(!q1.empty()) {
               int n(q1.front());
               q1.pop();
               if(q1.empty()) {
                  use_one = false;
                  return n;
               } else {
                  q2.push(n);
               }
            }
         } else {
            while(!q2.empty()) {
               int n(q2.front());
               q2.pop();
               if(q2.empty()) {
                  use_one = true;
                  return n;
               } else {
                  q1.push(n);
               }
            }
         }
      }

      explicit newstack(void): use_one(true) {}
};

class newqueue
{
   public:

      stack<int> s1;

      void push(int n) {
         s1.push(n);
      }

      int pop(void) {
         stack<int> s2;
         int ret(0);
         while(!s1.empty()) {
            int top(s1.top());
            s1.pop();
            if(s1.empty()) {
               ret = top;
            } else {
               s2.push(top);
            }
         }
         while(!s2.empty()) {
            int top(s2.top());
            s2.pop();
            s1.push(top);
         }
         return ret;
      }
};


int main(int argc, char **argv)
{
   newstack s;
   s.push(1);
   s.push(2);
   s.push(3);
   cout << s.pop() << endl;
   s.push(4);
   cout << s.pop() << endl;
   s.push(5);
   cout << s.pop() << endl;
   cout << s.pop() << endl;
   cout << s.pop() << endl;
   newqueue q;
   q.push(1);
   q.push(2);
   q.push(3);
   cout << q.pop() << endl;
   cout << q.pop() << endl;
   cout << q.pop() << endl;
   return 0;
}
