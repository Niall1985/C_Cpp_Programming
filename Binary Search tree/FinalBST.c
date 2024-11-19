#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
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
  if(data<root->data){
    root->left = insert(root->left, data);
  }
  else if(data>root->data){
    root->right = insert(root->right, data);
  }
  return root;
}

struct node* minValNode(struct node *root){
  struct node *temp = root;
  while(temp && temp->left != NULL){
    temp = temp->left;
  }
  return temp;
}

struct node *deleteNode(struct node *root, int key){
  if(root == NULL){
    return root;
  }
  else if(key < root->data){
    root->left = deleteNode(root->left, key);
  }
  else if(key > root->data){
    root->right = deleteNode(root->right, key);
  }
  else{
    if(root->left == NULL && root->right == NULL){
      free(root);
      return NULL;
    }
    else if(root->left == NULL){
    struct node *temp = root->right;
    free(root);
    return temp;
    }
    else if(root->right == NULL){
      struct node *temp = root->left;
      free(root);
      return temp;
    }
    struct node *temp = minValNode(root->right);
    root->data = temp->data;
    root->right = deleteNode(root->right, temp->data);
  }
  return root;
}

void kthmin(struct node *root, int kth, int *result, int *count){
  if(root == NULL || *result != -1){
    return;
  }  
  kthmin(root->left, kth, result, count);
  (*count)++;
  if(*count == kth){
    *result = root->data;
    return;
  }
  kthmin(root->right, kth, result, count);
}

void inorder(struct node *root){
  if(root == NULL){
    return;
  }
  inorder(root->left);
  printf("%d ", root->data);
  inorder(root->right);
}
void inorderts(struct node *root, int *arr, int *index){
  if(root == NULL){
    return;
  }
  inorderts(root->left, arr, index);
  arr[(*index)++] = root->data;
  inorderts(root->right, arr, index);
}

int printSuccessor(int *arr, int n, int k){
  for(int i = 0 ; i < n ; i++){
    if(arr[i] ==k && i+1 < n){
      return arr[i+1];
    }
  }
  return -1;
}

int main(){
  int n, data;
  struct node *root = NULL;
  scanf("%d", &n);
  for(int i = 0 ; i < n ; i++){
    scanf("%d", &data);
    root = insert(root, data);
  }
  int key;
  int arr[n];
  int index = 0;
  scanf("%d", &key);
  root = deleteNode(root, key);
  inorder(root);
  printf("\n");
  inorderts(root, &arr, &index);
  int result = -1, count = 0;
  kthmin(root, 2, &result, &count);
  if(result != -1){
    printf("%d", result);
  }
  printf("\n");
  int res = printSuccessor(&arr, n, 5);
  if(res != -1){
    printf("Successor of %d is %d", 5, res);
  }
  else{
    printf("-1");
  }
}
