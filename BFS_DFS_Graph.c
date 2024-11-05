// You are using GCC
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100
typedef struct Node{
    int vertex;
    struct Node *next;
} Node;

Node *adjList[MAX_NODES];
int visited[MAX_NODES];

Node *createNode(int v){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void addEdge(int u, int v){
    Node* newNode = createNode(v);
    
    if(adjList[u] == NULL){
        adjList[u] = newNode;
    }
    else{
        Node *temp = adjList[u];
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void dfs(int v){
    visited[v] = 1;
    printf("%d ", v);
    
    for(Node *temp = adjList[v] ; temp ; temp = temp->next){
        if(!visited[temp->vertex]){
            dfs(temp->vertex);
        }
    }
}

int main(){
    int n,m,u,v,start;
    
    scanf("%d %d", &n, &m);
    
    for(int i = 0  ; i < n ; i++){
        adjList[i] = NULL;
        visited[i] = 0;
    }
    
    for(int i = 0 ; i < m ; i++){
        scanf("%d %d", &u, &v);
        addEdge(u,v);
    }
    scanf("%d", &start);
    
    dfs(start);
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
