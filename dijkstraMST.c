#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX 100

int minDistance(int dist[], bool sptSet[], int V){
  int min = INT_MAX, minIndex;
  for(int v = 0 ; v < V ; v++){
    if(!sptSet[v] && dist[v]<min){
      min = dist[v];
      minIndex = v;
    }
  }
  return minIndex;
}

void printSolution(int dist[], int V) {
    printf("Vertex \tDistance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t %d\n", i, dist[i]);
    }
}
void dijkstrasMST(int graph[MAX][MAX], int V, int src){
  int dist[MAX];
  bool sptSet[MAX];
  for(int i = 0 ; i < V ; i++){
    dist[i] = INT_MAX;
    sptSet[i] = false;
  }
  dist[src] = 0;
  for(int count = 0 ; count < V-1 ; count++){
    int u = minDistance(dist, sptSet, V);
    sptSet[u] = true;
    
    for(int v = 0 ; v < V ; v++){
      if(!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u]+graph[u][v] < dist[v]){
        dist[v] = dist[u] + graph[u][v];
        }
    }
  }
  printSolution(dist, V);
}



int main() {
    int V; // Number of vertices
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    int graph[MAX][MAX];

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    int src;
    printf("Enter source vertex: ");
    scanf("%d", &src);

    dijkstrasMST(graph, V, src);

    return 0;
}




/*
Function 1: minDistance
Objective: Find the vertex with the minimum distance value from the set of vertices that have not been included in the Shortest Path Tree (SPT) yet.

Algorithm:
Initialize min to a very large value (INT_MAX).
For each vertex v in the graph:
If sptSet[v] is false (i.e., the vertex v is not in the SPT) and dist[v] is less than min, update min to dist[v] and minIndex to v.
Return minIndex, which is the vertex with the minimum distance that hasn’t been added to the SPT.

Function 2: printSolution
Objective: Print the shortest distance from the source vertex to all other vertices.

Algorithm:
Print a header row that labels the output as Vertex and Distance from Source.
For each vertex i from 0 to V - 1:
Print the vertex number i and its corresponding distance dist[i].

Function 3: dijkstrasMST
Objective: Implement Dijkstra's algorithm to calculate the shortest paths from a source vertex to all other vertices in a weighted graph represented by an adjacency matrix.

Algorithm:
Initialize arrays dist and sptSet for all vertices:
Set dist[i] to INT_MAX for each vertex i.
Set sptSet[i] to false for each vertex i.
Set dist[src] to 0, as the distance from the source to itself is zero.
Repeat the following steps V - 1 times (where V is the total number of vertices):
Use minDistance to find the vertex u with the minimum dist value that hasn’t been processed.
Mark u as processed by setting sptSet[u] to true.
For each adjacent vertex v of u:
If v is not in the SPT, there is an edge from u to v, and the distance to u is not INT_MAX, then:
Check if the total distance from src to v through u is less than dist[v].
If it is, update dist[v] to the new distance.
After finishing all iterations, call printSolution to display the shortest distances.
*/
