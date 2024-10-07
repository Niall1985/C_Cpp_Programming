#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct node* newNode(int data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

struct node* insertLevelOrder(struct node* root, int data) {
    struct node* new_node = newNode(data);

    if (root == NULL) {
        return new_node;
    }

    struct node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct node* temp = queue[front++];

        if (temp->left == NULL) {
            temp->left = new_node;
            break;
        } else {
            queue[rear++] = temp->left;
        }

        if (temp->right == NULL) {
            temp->right = new_node;
            break;
        } else {
            queue[rear++] = temp->right;
        }
    }
    return root;
}

void inorderTraversal(struct node* root) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

int main() {
    struct node* root = NULL;
    int data;

    while (1) {
        scanf("%d", &data);
        if (data <= 0) {  
            break;
        }
        root = insertLevelOrder(root, data);
    }

    inorderTraversal(root);
    
    return 0;
}
