#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX 10

int minKey(int key[], bool mst[], int V){
  int min = INT_MAX;
  int min_index;
  for(int i = 0 ; i  < V ; i++){
    if(!mst[i] && key[i]<min){
      min = key[i];
      min_index = i;
    }
  }
  return min_index;
}
void printMST(int parent[], int graph[MAX][MAX], int V){
  for(int i = 1 ; i  < V ; i++){
    printf("%d - %d %d\n", parent[i], i, graph[i][parent[i]]);
  }
}
void primMST(int graph[MAX][MAX], int V){
  int parent[MAX];
  int key[MAX];
  bool mstset[MAX];
  for(int i = 0 ; i < V ; i++){
    key[i] = INT_MAX;
    mstset[i] = false;
  }
  key[0] = 0;
  parent[0] = -1;
  
  for(int count = 0 ; count < V-1 ; count++){
    int u = minKey(key, mstset, V);
    mstset[u] = true;
    
  for(int v = 0 ; v < V ; v++)
    if(graph[u][v] && !mstset[v] && graph[u][v]<key[v]){
      parent[v] = u;
      key[v] = graph[u][v];
    }
  
  }
  printMST(parent, graph, V);
}

int main() {
    int V;
    scanf("%d", &V);

    int graph[MAX][MAX];
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            scanf("%d", &graph[i][j]);

    primMST(graph, V);
    return 0;
}
