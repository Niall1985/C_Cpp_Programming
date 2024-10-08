#include <stdio.h>
#include <stdlib.h>

struct node{
  int data;
  struct node *left;
  struct node *right;
};

struct node *newNode(int data){
  struct node *temp = (struct node*)malloc(sizeof(struct node));
  temp->data = data;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
}

struct node *insert(struct node *root, int data){
  if(root == NULL){
    return newNode(data);
  }
  struct node *queue[100];
  int front = 0, rear = 0;
  queue[rear++] = root;
  
  while(front<rear){
    struct node *current = queue[front++];
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

void levelordertraversal(struct node *root){
  if(root==NULL){
    return;
  }
  struct node *queue[100];
  int rear = 0, front = 0, sum = 0;
  queue[rear++] = root;
  while(front<rear){
    struct node *current = queue[front++];
    if(current->right != NULL){
      sum += current->right->data;
      queue[rear++] = current->right;
    }
    
    if(current->left != NULL){
      queue[rear++] = current->left;
    }
  }
  printf("Sum: %d", sum);
}


int main(){
  int n, data;
  struct node *root = NULL;
  scanf("%d", &n);
  for(int i = 0 ; i < n ; i++){
    scanf("%d", &data);
    root = insert(root, data);
  }
  levelordertraversal(root);
}
