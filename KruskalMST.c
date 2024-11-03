#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int src, dest, weight;
} Edge;

typedef struct {
  int parent, rank;
} Subset;

int compareEdges(const void *a, const void *b){
  Edge *edgeA = (Edge*)a;
  Edge *edgeB = (Edge*)b;
  return edgeA->weight - edgeB->weight;
}

int find(Subset subsets[], int i){
  if(subsets[i].parent != i){
    subsets[i].parent = find(subsets, subsets[i].parent);
  }
  return subsets[i].parent;
}

void unionEdges(Subset subsets[], int x, int y){
  int rootX = find(subsets, x);
  int rootY = find(subsets, y);
  
  if(subsets[rootX].rank < subsets[rootY].rank){
    subsets[rootX].parent = rootY;
  }
  else if(subsets[rootX].rank > subsets[rootY].rank){
    subsets[rootY].parent = rootX;
  }
  else{
    subsets[rootY].parent = rootX;
    subsets[rootX].rank++;
  }
}


void kruskalMST(Edge edges[], int V, int E){
  qsort(edges, E, sizeof(Edge), compareEdges);
  Subset subsets[200];
  for(int v = 0 ; v < V ; v++){
    subsets[v].parent = v;
    subsets[v].rank = 0;
  }
  int mstweight = 0;
  int edgeCount = 0;
  for(int i = 0 ; i < E && edgeCount < V-1 ; i++){
    int u = edges[i].src;
    int v = edges[i].dest;
    int weight = edges[i].weight;
    int rootU = find(subsets, u);
    int rootV = find(subsets, v);
    if(rootU != rootV){
      printf("%d - %d %d\n", u, v, weight);
      mstweight += weight;
      unionEdges(subsets, rootU, rootV);
      edgeCount++;
    }
  }
   printf("Total cost for installation: %d\n", mstweight);
}

int main(){
  int V, E;
  scanf("%d %d", &V, &E);
  Edge edges[100];
  for(int i = 0 ; i < E ; i++){
    scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
  }
  kruskalMST(edges, V, E);
}
