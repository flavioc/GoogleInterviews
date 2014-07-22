
#include <iostream>

using namespace std;

class list
{
   public:

      list *next;
      int val;

      static list* reverse(list *head)
      {
         list *tail(head);

         while(tail->next != NULL) {
            tail = tail->next;
         }

         list *cur(head), *next(NULL);
         while(cur != tail) {
            next = cur->next;
            cur->next = tail->next;
            tail->next = cur;
            cur = next;
         }
         return tail;
      }

      static list* append_reverse(list *head)
      {
         list *cur(head);
         list *rev(NULL);
         while(cur->next != NULL) {
            list *n(new list(cur->val, rev));
            rev = n;
            cur = cur->next;
         }
         cur->next = rev;
         return head;
      }

      static list* sort(list *head)
      {
         bool swapped = false;
         bool counted = false;
         int total(0);
         while(true) {
            list *cur(head);
            int i(0);
            while(cur->next != NULL && ((counted && i <= total) || !counted)) {
               list *next(cur->next);
               if(cur->val > next->val) {
                  int tmp;
                  tmp = cur->val;
                  cur->val = next->val;
                  next->val = tmp;
                  swapped = true;
               }
               i++;
               cur = cur->next;
            }
            if(!swapped)
               return head;
            if(!counted) {
               total = i - 1;
               counted = true;
            } else
               total--;
            swapped = false;
         }
      }

      static void remove(list *node)
      {
         if(node == NULL || node->next == NULL)
            return;
         node->val = node->next->val;
         node->next = node->next->next;
         delete node->next;
      }

      void print(void)
      {
         list *ptr(this);
         while(ptr != NULL) {
            cout << ptr->val << " ";
            ptr = ptr->next;
         }
         cout << endl;
      }

      static list * fromEnd(list *head, int n)
      {
         list *cur(head);
         list *last(NULL);
         int left(n);
         while(cur != NULL) {
            if(left == 0) {
               if(last == NULL)
                  last = head;
               else
                  last = last->next;
            } else {
               left--;
            }
            cur = cur->next;
         }

         return last;
      }

      void printReverse(void)
      {
         if(next != NULL)
            next->printReverse();
         cout << val << endl;
      }

      static int findCycle(list *head) {
         if(head == NULL)
            return 0;
         list *ptr1 = head;
         list *ptr2 = head;
         ptr2 = ptr2->next;
         while(ptr2 && ptr2 != ptr1) {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
            if(ptr2)
               ptr2 = ptr2->next;
         }
         int size = 0;
         if(ptr2 && ptr2 == ptr1) {
            size = 1;
            ptr1 = ptr1->next;
            while(ptr1 != ptr2) {
               size++;
               ptr1 = ptr1->next;
            }
         }
         return size;
      }

      explicit list(const int _val, list *_next):
         next(_next), val(_val)
      {}
};

int
main(int argc, char **argv)
{
   list *l1(NULL);
   list *l2(new list(5, l1));
   list *l3(new list(15, l2));
   list *l4(new list(20, l3));
   list *l5(new list(2, l4));
   list *l6(new list(10, l5));

   //list *rev(list::append_reverse(l6));
   //list *rev(list::sort(l6));

   //list::remove(l3);
   //l6->print();
   //l6->printReverse();
   cout << list::fromEnd(l6, 1)->val << endl;
   return 0;
}
