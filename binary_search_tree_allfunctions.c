#include <stdio.h>
#include <stdlib.h>

struct node{
  int data;
  struct node *left;
  struct node *right;
};

struct node *newNode(int data){
  struct node *node = (struct node*)malloc(sizeof(struct node));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  return node;
}


struct node *insert(struct node *node, int data){
  if(node == NULL){
    return newNode(data);
  }
  if(data<node->data){
    node->left = insert(node->left, data);
  }
  else if(data>node->data){
    node->right = insert(node->right, data);
  }
  return node;
}

void kthmin(struct node *node, int k, int *count, int*result){
  if(node == NULL && *result != -1)return;
  kthmin(node->left, k, count, result);
  (*count++);
  if(*count == k){
    *result = node->data;
  }
  return;
  kthmin(node->right, k, count, result);
}

void kthmax(struct node *node, int k, int *count, int*result){
  if(node == NULL && *result != -1)return;
  kthmax(node->right, k, count, result);
  (*count++);
  if(*count == k){
    *result = node->data;
  }
  return;
  kthmax(node->left, k, count, result);
}


int main() {
    struct node* root = NULL;
    root = insert(root, 20);
    insert(root, 8);
    insert(root, 22);
    insert(root, 4);
    insert(root, 12);
    insert(root, 10);
    insert(root, 14);

    int k;
    scanf("%d", &k);

    // Find k-th minimum
    int countMin = 0, resultMin = -1;
    kthmin(root, k, &countMin, &resultMin);
    if (resultMin != -1) {
        printf("The %d-th minimum element is: %d\n", k, resultMin);
    } else {
        printf("There are fewer than %d elements in the tree.\n", k);
    }

    // Find k-th maximum
    int countMax = 0, resultMax = -1;
    kthmax(root, k, &countMax, &resultMax);
    if (resultMax != -1) {
        printf("The %d-th maximum element is: %d\n", k, resultMax);
    } else {
        printf("There are fewer than %d elements in the tree.\n", k);
    }

    return 0;
}
