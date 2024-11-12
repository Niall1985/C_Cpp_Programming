

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
  int data;
  struct node *left;
  struct node *right;
}node;

node *newNode(int data){
  node *temp = (node*)malloc(sizeof(node));
  temp->data = data;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
}

node *insert(node *root, int data){
  if(root == NULL){
    return newNode(data);
  }
  node *queue[100];
  int front = 0, rear = 0;
  queue[rear++] = root;
  while(front<rear){
    node *current = queue[front++];
    if(current->left == NULL){
      current->left = newNode(data);
      break;
    }
    else{
      queue[rear++] = current->left;
    }
    if(current->right == NULL){
      current->right = newNode(data);
      break;
    }
    else{
      queue[rear++] = current->right;
    }
  }
  return root;
}

void levelOrderTraversal(node *root){
  if(root == NULL){
    return;
  }
  
  node *queue[100];
  int front = 0, rear = 0;
  queue[rear++] = root;
  
  while(front<rear){
    node *current = queue[front++];
    printf("%d ", current->data);
    
    if(current->left != NULL){
      queue[rear++] = current->left;
    }
    
    if(current->right != NULL){
      queue[rear++] = current->right;
    }
  }
  
}



int main(){
  int n, data;
  node *root = NULL;
  scanf("%d", &n);
  for(int i = 0 ; i < n ; i++){
    scanf("%d", &data);
    root = insert(root, data);
  }

  levelOrderTraversal(root);
}
