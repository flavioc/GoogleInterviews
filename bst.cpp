
#include <iostream>
#include <assert.h>

using namespace std;

class bstnode
{
   public:

      int val;
      bstnode *left, *right, *parent;

      static void print(bstnode *v, int tab = 0)
      {
         for(int i(0); i < tab; ++i)
            cout << "\t";
         cout << v->val << "(";
         if(v->parent)
            cout << v->parent->val;
         cout << ")" << endl;
         if(v->left)
            print(v->left, tab + 1);
         if(v->right)
            print(v->right, tab + 1);
      }

      static bool checkValid2(bstnode *n, int min, int max, bool useMin, bool useMax)
      {
         if(useMin && n->val < min)
            return false;
         if(useMax && n->val > max)
            return false;
         if(n->left) {
            if(!checkValid2(n->left, min, n->val, useMin, true))
               return false;
         }
         if(n->right) {
            if(!checkValid2(n->right, n->val, max, true, useMax))
               return false;
         }
         return true;
      }

      static bool checkValid(bstnode *n, int& maximum)
      {
         maximum = n->val;
         int temp;
         if(n->left) {
            if(!checkValid(n->left, temp))
               return false;
            if(n->val < temp)
               return false;
         }
         if(n->right) {
            if(!checkValid(n->right, temp))
               return false;
            if(n->val > temp)
               return false;
            maximum = temp;
         }
         return true;
      }

      class iterator
      {
         public:

            bstnode *curNode;

            inline int operator*(void) const { return curNode->val; }

            void operator++(int) {
               if(curNode == NULL)
                  return;
               if(curNode->right) {
                  curNode = curNode->right;
                  while(curNode->left)
                     curNode = curNode->left;
               } else {
                  while(true) {
                     bstnode *par = curNode->parent;
                     if(par == NULL) {
                        curNode = NULL;
                        return;
                     }
                     if(par->right == curNode)
                        curNode = par; // go up
                     else {
                        curNode = par; // do inner node
                        return;
                     }
                  }
               }
            }

            inline bool operator==(const iterator& other) const {
               return curNode == other.curNode;
            }

            inline bool operator!=(const iterator& other) const {
               return !operator==(other);
            }

            explicit iterator(bstnode *root): curNode(root) {
               while(curNode->left)
                  curNode = curNode->left;
            }

            explicit iterator(bool end): curNode(NULL) {}
      };

      inline iterator begin(void) { return iterator(this); }
      inline iterator end(void) { return iterator(false); }

      void setParent(bstnode *p) { parent = p; }

      explicit bstnode(const int _v, bstnode *_l = NULL, bstnode *_r = NULL):
         val(_v), left(_l), right(_r), parent(NULL)
      {
         if(left)
            left->setParent(this);
         if(right)
            right->setParent(this);
      }
};

static bstnode*
create_from_sorted_array(int *array, int n)
{
   assert(n >= 0);
   if(n == 0)
      return NULL;

   int middle = n/2;
   int el = array[middle];

   bstnode *left(create_from_sorted_array(array, middle));
   bstnode *right(create_from_sorted_array(array + middle + 1, n - middle - 1));

   return new bstnode(el, left, right);
}

static void
create_inorder_preorder(int *preorder, int *inorder, int n)
{
}

int
main(int argc, char **argv)
{
   bstnode *n1(new bstnode(1));
   bstnode *n2(new bstnode(3));
   bstnode *n3(new bstnode(2, n1, n2));
   bstnode *n4(new bstnode(5));
   bstnode *n5(new bstnode(7));
   bstnode *n6(new bstnode(6, n4, n5));
   bstnode *n7(new bstnode(4, n3, n6));
   bstnode *root(n7);
   int i;

   cout << bstnode::checkValid2(root, 0, 0, false, false) << endl;
   bstnode::print(root);

   for(bstnode::iterator it(root->begin()), end(root->end()); it != end; it++) {
      cout << *it << endl;
   }

   int vals[] = {1, 2, 3, 4, 5, 6, 7, 8};
   bstnode *ar(create_from_sorted_array(vals, sizeof(vals)/sizeof(int)));
   bstnode::print(ar);
   return 0;
}
