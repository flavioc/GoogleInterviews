
#include <iostream>

using namespace std;

typedef struct _btree {
   struct _btree *left;
   struct _btree *right;
   int val;
   struct _btree *parent;
} btree;

static bool
verifyBST(btree *node, int &minimum, int &maximum) {
   maximum = node->val;
   minimum = node->val;
   if(node->left) {
      int lmin, lmax;
      if(!verifyBST(node->left, lmin, lmax))
         return false;
      if(lmin > node->val || lmax > node->val)
         return false;
      minimum = lmin;
   }
   if(node->right) {
      int rmin, rmax;
      if(!verifyBST(node->right, rmin, rmax))
         return false;
      if(node->val > rmax || node->val > rmin)
         return false;
      maximum = rmax;
   }
   return true;
}

static void
print_tree(btree *t, int tab = 0)
{
   if(!t)
      return;
   for(int i(0); i < tab; ++i)
      printf(" ");
   cout << t->val << endl;
   print_tree(t->left, tab + 1);
   print_tree(t->right, tab + 1);
}

static btree*
create_from_array(int *a, int left, int right)
{
   if(right < left)
      return NULL;

   int middle = left + (right - left) / 2;

   btree *b = new btree;
   b->val = a[middle];
   b->parent = NULL;
   b->left = create_from_array(a, left, middle - 1);
   b->right = create_from_array(a, middle + 1, right);
   if(b->left)
      b->left->parent = b;
   if(b->right)
      b->right->parent = b;
   return b;
}

static btree*
build_orders0(int *inorder, int *preorder, int& pre_order_index, int left, int right)
{
   if(left > right)
      return NULL;

   btree *n = new btree;
   n->val = preorder[pre_order_index++];

   int pos = 0;
   for(int i(left); i <= right; ++i) {
      if(inorder[i] == n->val) {
         pos = i;
         break;
      }
   }

   n->left = build_orders0(inorder, preorder, pre_order_index, left, pos-1);
   n->right = build_orders0(inorder, preorder, pre_order_index, pos+1, right);
   return n;
}

static btree*
build_orders(int *inorder, int *preorder, int size)
{
   if(size == 0)
      return NULL;

   int pre_order_index = 0;
   return build_orders0(inorder, preorder, pre_order_index, 0, size - 1);
}

static btree*
next_largest(btree *b)
{
   if(b->left) {
      b = b->left;
      while(b->right)
         b = b->right;
      return b;
   } else {
      btree *parent = b->parent;
      while(parent) {
         if(parent->right == b) {
            return parent;
         } else {
            b = parent;
            parent = b->parent;
         }
      }
      // every node was visited
      return NULL;
   }
}

static btree*
next_smallest(btree *b)
{
   if(b->right) {
      b = b->right;
      while(b->left)
         b = b->left;
      return b;
   } else {
      btree *parent = b->parent;
      while(parent) {
         if(parent->left == b)
            return parent;
         else {
            b = parent;
            parent = b->parent;
         }
      }
      return NULL;
   }
}

static void
find_pairs_sum(btree *b, int sum)
{
   if(b == NULL)
      return;

   btree *largest = b;
   while(largest->right)
      largest = largest->right;

   btree *smallest = b;
   while(smallest->left)
      smallest = smallest->left;

   while(largest && smallest && largest->val >= smallest->val) {
      int gives = largest->val + smallest->val;

      if(gives == sum) {
         printf("%d %d\n", largest->val, smallest->val);
         btree * nlargest = next_largest(largest);
         if(nlargest->val == largest->val)
            largest = nlargest;
         else
            smallest = next_smallest(smallest);
      } else if(gives > sum) {
         largest = next_largest(largest);
      } else if(gives < sum) {
         smallest = next_smallest(smallest);
      }
   }
}

static void
ordered_two_trees(btree *b1, btree *b2)
{
   btree *smallest1 = b1;
   btree *smallest2 = b2;
   if(b1) {
      while(smallest1->left)
         smallest1 = smallest1->left;
   }

   if(b2) {
      while(smallest2->left)
         smallest2 = smallest2->left;
   }

   while(smallest1 && smallest2) {
      if(smallest1->val <= smallest2->val) {
         cout << smallest1->val << endl;
         smallest1 = next_smallest(smallest1);
      } else {
         cout << smallest2->val << endl;
         smallest2 = next_smallest(smallest2);
      }
   }

   btree *missing = NULL;
   if(smallest1)
      missing = smallest1;
   else
      missing = smallest2;
   while(missing) {
      cout << missing->val << endl;
      missing = next_smallest(missing);
   }
}

int
main(int argc, char **argv)
{
   btree one = {NULL, NULL, 1};
   btree one2 = {NULL, NULL, 2};
   btree four = {NULL, NULL, 4};
   btree three = {&one2, &four, 3};
   btree two = {&one, &three, 2};
   one.parent = &two;
   one2.parent = &three;
   four.parent = &three;
   int max, min;
   print_tree(&two);
   int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
   btree *b = create_from_array(arr, 0, sizeof(arr)/sizeof(int) - 1);
   print_tree(b);

   find_pairs_sum(b, 10);

   int inorder[] = {4, 2, 5, 1, 6, 3};
   int preorder[] = {1, 2, 4, 5, 3, 6};
   btree *x = build_orders(inorder, preorder, sizeof(inorder)/sizeof(int));
   print_tree(x);

   cout << "===========> " << endl;
   print_tree(b);
   print_tree(&two);
   ordered_two_trees(b, &two);
   return 0;
}
