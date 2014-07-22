
#include <iostream>

using namespace std;

typedef struct _list {
   struct _list *next;
   int data;
} list;

static void
print_list(list *l)
{
   cout << "[";
   while(l) {
      cout << l->data;
      l = l->next;
      if(l)
         cout << ", ";
   }
   cout << "]" << endl;
}

static list*
reverse_list(list *l)
{
   list *current_tail = NULL;

   while(l) {
      list *n = l->next;
      l->next = current_tail;
      current_tail = l;
      l = n;
   }
   return current_tail;
}

static list*
append_reverse_n(list *l, int n)
{
   if(!l)
      return NULL;

   list *current_tail = NULL;
   list *p = l;
   list *pp = NULL;
   while(p && n > 0) {
      list *node = new list;
      node->data = p->data;
      node->next = current_tail;
      current_tail = node;
      pp = p;
      p = p->next;
      --n;
   }

   if(n > 0)
      return NULL;

   // find tail
   if(!p)
      p = pp;
   while(p->next) {
      p = p->next;
   }
   // p is now the tail
   p->next = current_tail;
   return l;
}

static list*
sort_list(list *l)
{
   for(list *p = l; p; p = p->next) {
      list *n = p->next;
      for(list *n = p->next; n; n = n->next) {
         if(n->data < p->data)
            swap(n->data, p->data);
      }
   }
   return l;
}

static void
print_in_reverse(list *l)
{
   if(l->next)
      print_in_reverse(l->next);
   cout << l->data << endl;
}

static int
find_nth_item_from_end(list *l, int n)
{
   if(n == 0)
      return -1;

   list *p = l;
   while(n > 0 && p) {
      n--;
      p = p->next;
   }
   if(n > 0)
      return -1;
   list *elp = l;
   while(p) {
      elp = elp->next;
      p = p->next;
   }
   return elp->data;
}

static int
loop_length(list *l)
{
   if(!l)
      return -1;
   if(!l->next)
      return -1;
   list *slow = l;
   list *fast = l->next;
   bool loop_found = false;

   while(slow && fast && fast->next) {
      if(slow == fast) {
         loop_found = true;
         break;
      }
      slow = slow->next;
      fast = fast->next->next;
   }

   if(loop_found) {
      list *p = slow;
      int size = 1;
      p = p->next;
      while(p != slow) {
         size++;
         p = p->next;
      }
      return size;
   } else {
      return -1;
   }

}

static void
loops(void)
{
   list l1 = {NULL, 1};
   list l2 = {NULL, 2};
   list l3 = {NULL, 3};
   list l4 = {&l1, 4};

   l1.next = &l2;
   l2.next = &l3;
   l3.next = &l1;

   cout << loop_length(&l4) << endl;
}

int
main(int argc, char **argv)
{
   list l1 = {NULL, 1};
   list l2 = {&l1, 2};
   list l3 = {&l2, 3};
   print_list(&l3);
   list *n = append_reverse_n(&l3, 3);
   //list *n = reverse_list(&l3);
   print_list(n);
   list *x = sort_list(n);
   print_list(x);
   //print_in_reverse(x);
   //cout << find_nth_item_from_end(x, 3) << endl;
   loops();
   return 0;
}
