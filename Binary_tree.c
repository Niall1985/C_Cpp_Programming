#include <stdio.h>
#include <stdlib.h>

struct node {
  int item;
  struct node *left;
  struct node *right;
};

struct node *createNode(int data){
  struct node *temp = (struct node*)malloc(sizeof(struct node));
  temp->item = data;
  temp->left = temp->right = NULL;
  return temp;
}

void preorder(struct node *root){
  if(root == NULL)
  return;
  printf("%d ", root->item);
  preorder(root->left);
  preorder(root->right);
}


void inorder(struct node *root){
  if(root==NULL)
  return;
  inorder(root->left);
  printf("%d ",root->item);
  inorder(root->right);
}

void postorder(struct node *root){
  if(root==NULL)
  return;
  postorder(root->left);
  postorder(root->right);
  printf("%d ",root->item);
}

int main()
{
    struct node *root = createNode(1);
    root->left= createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    printf("preorder\n");
    preorder(root);
    printf("\n");
    printf("Inorder\n");
    inorder(root);
    printf("\n");
    printf("Postorder\n");
    postorder(root);
    printf("\n");
}

// input:

//     1
//    / \
//   2   3
//  / \
// 4   5

// output:

// preorder
// 1 2 4 5 3 
// Inorder
// 4 2 5 1 3 
// Postorder
// 4 5 2 3 1


#include <stdio.h>
#include <stdlib.h>

struct node {
  int item;
  struct node *left;
  struct node *right;
};

struct node *createNode(int data){
  struct node *temp = (struct node*)malloc(sizeof(struct node));
  temp->item = data;
  temp->left = temp->right = NULL;
  return temp;
}

void preorder(struct node *root){
  if(root == NULL)
  return;
  printf("%d ", root->item);
  preorder(root->left);
  preorder(root->right);
}


void inorder(struct node *root){
  if(root==NULL)
  return;
  inorder(root->left);
  printf("%d ",root->item);
  inorder(root->right);
}

void postorder(struct node *root){
  if(root==NULL)
  return;
  postorder(root->left);
  postorder(root->right);
  printf("%d ",root->item);
}


struct node* createTree(){
  int data;
  scanf("%d",&data);
  if(data == -1){
    return NULL;
  }
  struct node *newNode = createNode(data);
  newNode->left = createTree();
  newNode->right = createTree();
  return newNode;
}
int main()
{
    struct node *root = NULL;
    root = createTree();    
    printf("preorder\n");
    preorder(root);
    printf("\n");
    printf("Inorder\n");
    inorder(root);
    printf("\n");
    printf("Postorder\n");
    postorder(root);
    printf("\n");
}


// 1 2 4 -1 -1 5 -1 -1 3 -1 -1
//         1
//        / \
//       2   3
//      / \
//     4   5
// preorder
// 1 2 4 5 3 

// Inorder
// 4 2 5 1 3 

// Postorder
// 4 5 2 3 1
