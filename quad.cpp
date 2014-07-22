
#include <iostream>

using namespace std;

typedef enum {
   MIXED,
   WHITE,
   BLACK
} Type;

typedef struct _quad {
   Type typ;
   struct _quad *c1, *c2, *c3, *c4;
} quad;

static quad*
merge_quad(quad *q1, quad *q2)
{
   if(q1->typ == BLACK) {
      return q1;
   }
   if(q2->typ == BLACK) {
      return q2;
   }

   if(q1->typ == WHITE && q2->typ == WHITE)
      return q1;

   if(q1->typ == MIXED && q2->typ == MIXED) {
      quad *n = new quad;
      n->typ = MIXED;
      n->c1 = merge_quad(q1->c1, q2->c1);
      n->c2 = merge_quad(q1->c2, q2->c2);
      n->c3 = merge_quad(q1->c3, q2->c3);
      n->c4 = merge_quad(q1->c4, q2->c4);
      return n;
   }
}

static void
print_quad(quad *q, int tab)
{
   for(int i(0); i < tab; ++i)
      printf(" ");
   if(q->typ == WHITE)
      printf("WHITE");
   if(q->typ == BLACK)
      printf("BLACK");
   if(q->typ == MIXED) {
      printf("MIXED");
   }
   printf("\n");
   if(q->typ == MIXED) {
      print_quad(q->c1, tab + 1);
      print_quad(q->c2, tab + 1);
      print_quad(q->c3, tab + 1);
      print_quad(q->c4, tab + 1);
   }
}

int
main(int argc, char **argv)
{
   // build first
   quad q1, q2, q3, q4;
   q1.typ = WHITE;
   q2.typ = BLACK;
   q3.typ = MIXED;
   q4.typ = WHITE;

   quad q5, q6, q7, q8;
   q5.typ = q6.typ = q7.typ = q8.typ = WHITE;
   q3.c1 = &q5;
   q3.c2 = &q6;
   q3.c3 = &q7;
   q3.c4 = &q8;

   quad a1, a2, a3, a4;
   a1.typ = a2.typ = a3.typ = a4.typ = BLACK;

   quad w1, w2, w3, w4;
   w1.typ = BLACK;
   w2.typ = WHITE;
   w3.typ = MIXED;
   w4.typ = WHITE;

   w3.c1 = &a1;
   w3.c2 = &a2;
   w3.c3 = &a3;
   w3.c4 = &a4;

   quad one = {MIXED, &q1, &q2, &q3, &q4};
   quad two = {MIXED, &w1, &w2, &w3, &w4};

   quad *merged = merge_quad(&one, &two);

   print_quad(merged, 0);

   return 0;
}
