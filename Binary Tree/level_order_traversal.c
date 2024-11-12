#include <stdio.h>
#include <stdlib.h>

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
  
  
  struct node *queue[100];
  int front = 0 , rear = 0;
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


void levelOrder(struct node *root) {
    if (root == NULL) {
        return;
    }

    struct node *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct node *current = queue[front++];
        printf("%d ", current->data);

        if (current->left != NULL) {
            queue[rear++] = current->left;
        }

        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
}


int main() {
    struct node *root = NULL;
    int n, data;


    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
       
        scanf("%d", &data);
        root = insert(root, data);
    }

    printf("Level Order Traversal: ");
    levelOrder(root);

    return 0;
}





















#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* buildTree() {
    int val;
    scanf("%d", &val);
    if (val == -1) {
        return NULL;
    }

    struct Node* root = createNode(val);

    root->left = buildTree();

    root->right = buildTree();

    return root;
}
void inOrder(struct Node* root) {
    if (root == NULL)
        return;
    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
}
int main() {
    struct Node* root = buildTree();

    inOrder(root);

    return 0;
}








#include <stdio.h>
#include <stdlib.h>

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

struct node* buildTree() {
    int val;
    scanf("%d", &val);
    if (val == -1) {
        return NULL;
    }

    struct node* root = newNode(val);

    root->left = buildTree();

    root->right = buildTree();

    return root;
}
void inOrder(struct node* root) {
    if (root == NULL)
        return;
    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
}
int main() {
    struct Node* root = buildTree();

    inOrder(root);

    return 0;
}
