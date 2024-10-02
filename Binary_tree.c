#include <stdio.h>
#include <stdlib.h>

struct node {
  int item;
  struct node *left;
  struct node *right;
};

struct node *createNode(int data){
  struct node *temp = (struct node*)malloc(sizeof(struct node));
  temp->data = data;
  temp->left = temp->right = NULL;
  return temp;
}

void preorder(struct node *root){
  if(root == NULL);
  return;
  printf("%d ", root->data);
  preorder(root->left);
  preorder(root->right);
}

int main()
{
    
}
