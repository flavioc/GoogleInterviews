
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <queue>

using namespace std;

typedef struct _graph_node {
   vector<struct _graph_node*> links;
   int val;
   int pos;
} graph_node;

static bool
dfsColor(graph_node **graph, int i, int *colors, int color)
{
   colors[i] = color;

   graph_node *node(graph[i]);
   for(vector<graph_node*>::iterator it(node->links.begin()), end(node->links.end());
         it != end; ++it)
   {
      graph_node *neighbor(*it);

      if(colors[neighbor->pos] == color)
         return false;
      if(colors[neighbor->pos] == -1) {
         if(!dfsColor(graph, neighbor->pos, colors, 1 - color))
            return false;
      }
   }
   return true;
}

static bool
isBipartite(graph_node **graph, size_t size)
{
   int colors[size];
   memset(colors, -1, sizeof(int));

   for(size_t i(0); i < size; ++i) {
      if(colors[i] == -1) {
         if(!dfsColor(graph, i, colors, 0))
            return false;
      }
   }
}

static void
shortestPath(graph_node **graph, size_t size)
{
#define MAX_DISTANCE 99999
   int d[size];
   for(size_t i(0); i < size; ++i)
      d[i] = MAX_DISTANCE;
   priority_queue<pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> >  > queue;

   queue.push(make_pair(0, 0));
   d[0] = 0;

   while(!queue.empty()) {
      pair<int, int> next = queue.top();
      int distance = d[next.first];
      queue.pop();

      if(next.second != distance)
         continue;

      graph_node *node(graph[next.first]);

      for(vector<graph_node*>::iterator it(node->links.begin()), end(node->links.end());
            it != end; ++it)
      {
         graph_node *neighbor(*it);

         int new_distance = distance + 1;
         int old_distance = d[neighbor->pos];

         if(new_distance < old_distance) {
            queue.push(make_pair(neighbor->pos, new_distance));
            d[neighbor->pos] = new_distance;
         }
      }
   }
   for(size_t i(0); i < size; ++i) {
      cout << d[i] << endl;
   }
}

static void
primAlgorithm(graph_node **graph, size_t size)
{
   size_t in_set = 1;
   bool node_in_set[size];
   node_in_set[0] = 1;
   for(size_t i(1); i < size; ++i) {
      node_in_set[i] = 0;
   }

   priority_queue< pair<int, graph_node*> > queue;
   graph_node *node = graph[0];

   for(vector<graph_node*>::iterator it(node->links.begin()), end(node->links.end());
         it != end; ++it)
   {
      queue.push(make_pair(1, *it));
   }

   while(in_set < size && !queue.empty()) {
      pair<int, graph_node*> p = queue.top();
      queue.pop();
      if(node_in_set[p.second->pos]) {
         continue;
      }
      node_in_set[p.second->pos] = 1;
      node = p.second;
      for(vector<graph_node*>::iterator it(node->links.begin()), end(node->links.end());
            it != end; ++it)
      {
         graph_node *other = *it;
         if(!node_in_set[other->pos]) {
            queue.push(make_pair(1, other));
         }
      }
      in_set++;
      cout << "add " << node->val << endl;
   }

   if(in_set < size) {
      cout << "missing nodes" << endl;
   }
}

static void
floyd_warshall(graph_node **graph, size_t n)
{
   int dist[n][n];
   for(size_t i(0); i < n; ++i) {
      for(size_t j(0); j < n; ++j) {
         if(i == j)
            dist[i][j] = 0;
         else
            dist[i][j] = 99999;
      }
   }

   for(size_t i(0); i < n; ++i) {
      graph_node *g(graph[i]);
      for(vector<graph_node*>::iterator it(g->links.begin()), end(g->links.end());
            it != end; ++it)
      {
         graph_node *o(*it);
         if(dist[i][o->pos] > 1)
            dist[i][o->pos] = 1;
      }
   }

   for(size_t k(0); k < n; ++k) {
      for(size_t i(0); i < n; ++i) {
         for(size_t j(0); j < n; ++j) {
            if(dist[i][j] > dist[i][k] + dist[k][j])
               dist[i][j] = dist[i][k] + dist[k][j];
         }
      }
   }
   for(size_t i(0); i < n; ++i) {
      for(size_t j(0); j < n; ++j) {
         cout << dist[i][j] << " ";
      }
      cout << endl;
   }
}

int
main(int argc, char **argv)
{
   graph_node q1;
   graph_node q2;
   graph_node q3;
   graph_node q4;
   graph_node q5;

   q1.pos = 0; q1.val = 1;
   q2.pos = 1; q2.val = 2;
   q3.pos = 2; q3.val = 3;
   q4.pos = 3; q4.val = 4;
   q5.pos = 4; q5.val = 5;

   q1.links.push_back(&q2);
   q2.links.push_back(&q1);

   q2.links.push_back(&q3);
   q3.links.push_back(&q2);

   q3.links.push_back(&q4);
   q4.links.push_back(&q3);

   q4.links.push_back(&q1);
   q1.links.push_back(&q4);

   graph_node *graph[] = {&q1, &q2, &q3, &q4, &q5};
   size_t size = sizeof(graph)/sizeof(graph_node*);

   cout << isBipartite(graph, size) << endl;

   shortestPath(graph, size);
   primAlgorithm(graph, size);
   floyd_warshall(graph, size);

   return 0;
}
