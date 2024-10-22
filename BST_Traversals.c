//Preorder to Inorder
//Preorder to Inorder

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

struct node *constructBST(int preorder[], int *index, int key, int min, int max, int size){
  if(*index >= size){
    return NULL;
  }
  struct node *root = NULL;
  if(key>min && key<max){
    root = newNode(key);
    *index = *index + 1;
    
    if(*index<size){
      root->left = constructBST(preorder, index, preorder[*index], min, key, size);
      root->right = constructBST(preorder, index, preorder[*index], key, max, size);
    }
  }
  
  return root;
}

struct node *buildTree(int preorder[], int size){
  int index = 0;
  return constructBST(preorder, &index, preorder[0], INT_MIN, INT_MAX, size);
}

void inorder(struct node *root){
  if(root == NULL){
    return;
  }
  
  inorder(root->left);
  printf("%d ", root->data);
  inorder(root->right);
}

int main(){
  int n;
  scanf("%d", &n);
  int arr[n];
  for(int i = 0 ; i < n ; i++){
    scanf("%d", &arr[i]);
  }
  
  struct node *root = buildTree(arr, n);
  inorder(root);
}


//Postorder to inorder
//Preorder to Inorder

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

struct node *constructBST(int postorder[], int *index, int key, int min, int max, int size){
  if(*index < 0){
    return NULL;
  }
  struct node *root = NULL;
  if(key>min && key<max){
    root = newNode(key);
    *index = *index - 1;
    
    if(*index>=0){
      root->right = constructBST(postorder, index, postorder[*index], key, max, size);
      root->left = constructBST(postorder, index, postorder[*index], min, key, size);
    }
  }
  
  return root;
}

struct node *buildTree(int postorder[], int size){
  int index = size-1;
  return constructBST(postorder, &index, postorder[0], INT_MIN, INT_MAX, size);
}

void inorder(struct node *root){
  if(root == NULL){
    return;
  }
  
  inorder(root->left);
  printf("%d ", root->data);
  inorder(root->right);
}

int main(){
  int n;
  scanf("%d", &n);
  int arr[n];
  for(int i = 0 ; i < n ; i++){
    scanf("%d", &arr[i]);
  }
  
  struct node *root = buildTree(arr, n);
  inorder(root);
}
