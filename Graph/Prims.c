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


/*
Algorithm:

Function 1: minkey function
1. initialize a dist array to store the minimum weighted edges
2. initialize a mstSet array to check if the vertex being processed doesn't exist in the current tree
3. intialize a min variable to infinity and set a variable called minIndex
4. run a for loop from 0 to < V and check if the node i being processed doesn't already exist in the graph and the weight is less than min
5. if the conditions are satisfied, then set min = dis[i] abd set the value of i to minIndex and return it

Function 2: PrimsMST function
1. initialize a graph matrix and pass the total number of vertices V to the function
2. intialize a parent array to track the parent of each node, set a key array and set a boolean mstSet array to check if the node being processed doesn't already exist in the graph
3. run a for loop from 0 to V-1 and set all the keys to INT_MAX and set all mstSet values to false
4. set key[0] to 0 and parent[0] to -1
5. run another for loop from 0 to < V-1 and find the minimum weighet edge that has not been processed before, set mstSet to true once that edge has been found
6. run a nested forloop from 0 to < V and check if an edge exists from u to v (graph[u][v]) and check is the edge node doesn't already exist in the graph and check if graph[u][v]<key[v]
7. if all good then, parent[v] = u and key[v] = graph[u][v]
*/
