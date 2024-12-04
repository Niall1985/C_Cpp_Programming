//level order insertion

#include <stdio.h>
#include <stdlib.h>

// Structure of a Binary Tree Node
struct Node {
    int data;
    struct Node *left, *right;
};

// Function to create a new Node
struct Node* newNode(int v) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = v;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to traverse the binary tree in in-order and print only nodes with odd values
void printInorderOdd(struct Node* node) {
    if (node == NULL)
        return;

    // Traverse left subtree
    printInorderOdd(node->left);

    // Print the node's value if it's odd
    if (node->data % 2 != 0)
        printf("%d ", node->data);

    // Traverse right subtree
    printInorderOdd(node->right);
}

// Function to insert nodes in level order
struct Node* insertLevelOrder(int arr[], struct Node* root, int i, int n) {
    // Base case for recursion
    if (i < n) {
        struct Node* temp = newNode(arr[i]);
        root = temp;

        // Insert left child
        root->left = insertLevelOrder(arr, root->left, 2 * i + 1, n);

        // Insert right child
        root->right = insertLevelOrder(arr, root->right, 2 * i + 2, n);
    }
    return root;
}

int main() {
    int n;
    scanf("%d", &n);
    
    int arr[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    struct Node* root = NULL;
    root = insertLevelOrder(arr, root, 0, n);

    // Function call to traverse in in-order and print only nodes with odd values
    printInorderOdd(root);
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




