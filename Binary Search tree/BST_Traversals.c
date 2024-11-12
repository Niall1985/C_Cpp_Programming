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




// Check if is balanced 
#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Helper function to check the height of a subtree
int checkHeight(struct Node* root) {
    if (root == NULL) {
        return 0; // Height of an empty tree is 0
    }

    int leftHeight = checkHeight(root->left);
    int rightHeight = checkHeight(root->right);

    if (leftHeight == -1 || rightHeight == -1) {
        return -1; // Propagate imbalance
    }

    if (abs(leftHeight - rightHeight) > 1) {
        return -1; // If the subtree is unbalanced
    }

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight); // Return the height
}

// Function to check if the tree is balanced
int isBalanced(struct Node* root) {
    return checkHeight(root) != -1;
}

// Main function for testing
int main() {
    // Constructing a balanced BST manually
    struct Node* root = newNode(10);
    root->left = newNode(5);
    root->right = newNode(15);
    root->left->left = newNode(3);
    root->left->right = newNode(7);
    root->right->left = newNode(12);
    root->right->right = newNode(18);

    if (isBalanced(root)) {
        printf("The tree is balanced.\n");
    } else {
        printf("The tree is not balanced.\n");
    }

    return 0;
}
