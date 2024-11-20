//bfs implementation
#include <stdio.h>
#include <stdbool.h>
#define MAX 10

void bfs(int graph[MAX][MAX], int V, int src){
  int queue[MAX], front = 0, rear = 0;
  bool visited[MAX] = {false};
  
  queue[++rear] = src;
  visited[src] = true;
  
  while (front<rear){
    int current = queue[front++];
    printf("%d ", current);
    for(int i = 0 ; i < V  i++){
      if(graph[i][src] = 1 && !visited[i]){
        visited[i] = true;
        queue[++rear] = i;
      }
    }
  }
}

// dfs implementation
#include <stdio.h>
#include <stdbool.h>

#define MAX 100
void dfs(int graph[MAX][MAX], int V, bool visited[], int level[], int src, int currentLevel){
  visited[src] = true;
  level[src] = currentLevel;
  printf("%d ", src);
  for(int i = 0 ; i < V ; i++){
    if(graph[src][i] && !visited[i]){
      dfs(graph, V, visited, level, i, currentLevel+1);
    }
  }
}

int main(){
  int V, E;
  scanf("%d %d", &V, &E);
  int graph[MAX][MAX] = {0};
  for(int i = 0 ; i < E ; i++){
    int u,v;
    scanf("%d %d", &u, &v);
    graph[u][v] = 1;
    graph[v][u] = 1;
  }
  bool visited[MAX] = { false };
  int level[MAX];
  for(int i = 0 ; i < V ; i++){
    level[i] = -1;
  }
  int src;
  scanf("%d", &src);
  dfs(graph, V, visited, level, src, 0);
  printf("\n");
  for(int i = 0 ; i < V ; i++){
    if(visited[i]){
      printf("%d - %d\n", i, level[i]);
    }
  }
}
