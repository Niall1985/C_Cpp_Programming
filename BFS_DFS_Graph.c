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
