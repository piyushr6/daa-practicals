#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define INF 99999

// Structure to represent an edge
typedef struct
{
   int src, dest, weight;
} Edge;

// Structure to represent a graph
typedef struct
{
   int V, E;
   Edge *edges;
} Graph;

// Utility function to create a graph
Graph *createGraph(int V, int E)
{
   Graph *graph = (Graph *)malloc(sizeof(Graph));
   graph->V = V;
   graph->E = E;
   graph->edges = (Edge *)malloc(E * sizeof(Edge));
   return graph;
}

// Function to generate a connected tree with V vertices and V-1 edges
void generateTree(int V, Graph *graph)
{
   srand(time(0));
   for (int i = 0; i < V - 1; i++)
   {
      graph->edges[i].src = i;
      graph->edges[i].dest = i + 1;
      graph->edges[i].weight = (rand() % 20) + 1;
   }
}

// Function to print the input tree
void printGraph(Graph *graph)
{
   printf("\n==== Input Tree ====\n");
   printf("Edges in the Input Tree:\n");
   for (int i = 0; i < graph->E; i++)
      printf("%d -- %d == %d\n", graph->edges[i].src, graph->edges[i].dest, graph->edges[i].weight);
   printf("\n====================\n");
}

// Disjoint Set (Union-Find) with path compression
typedef struct
{
   int *parent, *rank;
} DisjointSet;

DisjointSet *createSet(int n)
{
   DisjointSet *ds = (DisjointSet *)malloc(sizeof(DisjointSet));
   ds->parent = (int *)malloc(n * sizeof(int));
   ds->rank = (int *)malloc(n * sizeof(int));
   for (int i = 0; i < n; i++)
   {
      ds->parent[i] = i;
      ds->rank[i] = 0;
   }
   return ds;
}

int find(DisjointSet *ds, int i)
{
   if (ds->parent[i] != i)
      ds->parent[i] = find(ds, ds->parent[i]);
   return ds->parent[i];
}

void unionSets(DisjointSet *ds, int x, int y)
{
   int xroot = find(ds, x);
   int yroot = find(ds, y);
   if (ds->rank[xroot] < ds->rank[yroot])
      ds->parent[xroot] = yroot;
   else if (ds->rank[xroot] > ds->rank[yroot])
      ds->parent[yroot] = xroot;
   else
   {
      ds->parent[yroot] = xroot;
      ds->rank[xroot]++;
   }
}

int compareEdges(const void *a, const void *b)
{
   return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

// Kruskal's Algorithm
void kruskalMST(Graph *graph, FILE *fp)
{
   clock_t start = clock();
   printf("\n==== Kruskal's MST ====\n");

   int V = graph->V;
   Edge result[V - 1];
   int e = 0, i = 0;
   qsort(graph->edges, graph->E, sizeof(graph->edges[0]), compareEdges);

   DisjointSet *ds = createSet(V);

   for (i = 0; e < V - 1 && i < graph->E; i++)
   {
      Edge nextEdge = graph->edges[i];
      int x = find(ds, nextEdge.src);
      int y = find(ds, nextEdge.dest);
      if (x != y)
      {
         result[e++] = nextEdge;
         unionSets(ds, x, y);
      }
   }

   printf("\nEdges in MST:\n");
   int totalWeight = 0;
   for (i = 0; i < e; i++)
   {
      printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
      totalWeight += result[i].weight;
   }

   // Printing MST Path
   printf("Tree Path: ");
   for (i = 0; i < e; i++)
   {
      printf("%d--", result[i].src);
   }
   printf("%d\n", result[e - 1].dest);

   printf("Minimum Weight = %d\n", totalWeight);
   printf("\n========================\n");

   clock_t end = clock();
   fprintf(fp, "%d, %lf\n", V, (double)(end - start) * 1000000 / CLOCKS_PER_SEC);

   free(ds->parent);
   free(ds->rank);
   free(ds);
}

// Prim's Algorithm
void primMST(Graph *graph, FILE *fp)
{
   clock_t start = clock();
   printf("\n==== Prim's MST ====\n");

   int V = graph->V;
   int parent[V], key[V], mstSet[V];

   for (int i = 0; i < V; i++)
   {
      key[i] = INF;
      mstSet[i] = 0;
   }

   key[0] = 0;
   parent[0] = -1;

   for (int count = 0; count < V - 1; count++)
   {
      int min = INF, min_index;
      for (int v = 0; v < V; v++)
      {
         if (mstSet[v] == 0 && key[v] < min)
         {
            min = key[v];
            min_index = v;
         }
      }

      mstSet[min_index] = 1;

      for (int i = 0; i < graph->E; i++)
      {
         Edge edge = graph->edges[i];
         if (edge.src == min_index && mstSet[edge.dest] == 0 && edge.weight < key[edge.dest])
         {
            parent[edge.dest] = min_index;
            key[edge.dest] = edge.weight;
         }
      }
   }

   // Printing MST
   printf("\nEdges in MST:\n");
   int totalWeight = 0;
   for (int i = 1; i < V; i++)
   {
      printf("%d -- %d == %d\n", parent[i], i, key[i]);
      totalWeight += key[i];
   }

   // Printing MST Path
   printf("Tree Path: ");
   for (int i = 1; i < V; i++)
   {
      printf("%d--", parent[i]);
   }
   printf("%d\n", V - 1);

   printf("Minimum Weight = %d\n", totalWeight);
   printf("\n========================\n");

   clock_t end = clock();
   fprintf(fp, "%d, %lf\n", V, (double)(end - start) * 1000000 / CLOCKS_PER_SEC);
}

int main()
{
   int sizes[] = {8, 15, 20};
   FILE *fp = fopen("execution_times.csv", "w");
   fprintf(fp, "Input Size, Execution Time (microseconds)\n");

   for (int s = 0; s < 3; s++)
   {
      int V = sizes[s];
      Graph *g = createGraph(V, V - 1);
      generateTree(V, g);
      printGraph(g);
      kruskalMST(g, fp);
      primMST(g, fp);
      free(g->edges);
      free(g);
   }

   fclose(fp);
   return 0;
}