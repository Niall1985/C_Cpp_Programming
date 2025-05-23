// Q) Problem Statement
// Selsiya needs a program to analyze a binary tree and print only the nodes with odd values. 
// The program begins by prompting for an integer n, indicating the number of nodes in the binary tree.
// Selsiya then provides n integers representing the values of these nodes. 
// The program constructs a level ordered binary tree from the provided values and traverses it in in-order. 
// During traversal, it prints only the values of the nodes that are odd. Additionally, the program ensures that the binary tree contains at least one node with an odd value.

// Input format :
// The first line consists of an integer n, representing the number of nodes in the binary tree.

// The second line consists of n space-separated integers representing the values of the nodes in the binary tree.

// Output format :
// The program prints a single line containing the values of the nodes with odd values, obtained through an in-order traversal of the binary tree. The integers are space-separated.

// Code constraints :
// The input integers should be unique.

// 1 ≤ n ≤ 20

// 1 ≤ Node values ≤ 100

// The binary tree must contain at least one node with an odd value.

// Sample test cases :
// Input 1 :
// 5
// 11 10 9 54 6
// Output 1 :
// 11 9 
// Input 2 :
// 8
// 1 2 3 4 5 6 7 8
// Output 2 :
// 5 1 3 7


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
    struct node *new_node = newNode(data);
    if(root == NULL){
        return new_node;
    }
    
    struct node *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    
    while(front<rear){
        struct node *temp = queue[front++];
        
        if(temp->left == NULL){
            temp->left = new_node;
            break;
        }
        else{
            queue[rear++] = temp->left;
        }
        
        if(temp->right == NULL){
            temp->right = new_node;
            break;
        }
        else{
            queue[rear++] = temp->right;
        }
    }
    
    return root;
}


void inorder(struct node* root){
    if(root == NULL){
        return;
    }
    inorder(root->left);
    if(root->data % 2 != 0){
        printf("%d ", root->data);
    }
    inorder(root->right);
}


int main(){
    int n, data;
    struct node *root = NULL;
    scanf("%d",&n);
    for(int i = 0 ; i < n ; i++){
        scanf("%d",&data);
        root = insert(root, data);
    }
    inorder(root);
    
}




// Q) Problem Statement

// Divu wants a program to analyze a binary tree by traversing it in two different ways. 
// The program begins by prompting for an integer n, indicating the number of nodes in the binary tree. Divu then provides n integers representing the values of these nodes. 
// The program constructs the binary tree from the provided values and performs two types of traversals:

// Forward In-order Traversal: It traverses the binary tree in order, printing each node's value as it visits.
// Reverse In-order Traversal: It traverses the binary tree in order but prints each node's value in reverse order.
// After conducting these traversals, the program prints the results.

// Input format :
// The first line consists of an integer n, representing the number of nodes in the binary tree.

// The second line consists of n space-separated integers representing the values of the nodes in the binary tree.

// Output format :
// The first line prints the in-order traversal of the binary tree, where each node's value is printed as it is visited.

// The second line prints the in-order traversal of the binary tree in reverse, where each node's value is printed in reverse order.

// Refer to the sample output for the formatting specifications.

// Code constraints :
// The input integers should be unique.

// 1 ≤ n ≤ 15

// 1 ≤ Node values ≤ 50

// Sample test cases :
// Input 1 :
// 5
// 9 8 7 6 5
// Output 1 :
// 6 8 5 9 7 
// 7 9 5 8 6 
// Input 2 :
// 8
// 1 2 3 4 5 6 7 8
// Output 2 :
// 8 4 2 5 1 6 3 7 
// 7 3 6 1 5 2 4 8 


    
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
    struct node *new_node = newNode(data);
    if(root == NULL){
        return new_node;
    }
    
    struct node *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    
    while(front<rear){
        struct node *temp = queue[front++];
        
        if(temp->left == NULL){
            temp->left = new_node;
            break;
        }
        else{
            queue[rear++] = temp->left;
        }
        
        if(temp->right == NULL){
            temp->right = new_node;
            break;
        }
        else{
            queue[rear++] = temp->right;
        }
    }
    
    return root;
}


void forwardinorder(struct node* root){
    if(root == NULL){
        return;
    }
    forwardinorder(root->left);
    printf("%d ", root->data);
    forwardinorder(root->right);
}

void reversedinorder(struct node* root){
    if(root == NULL){
        return;
    }
    reversedinorder(root->right);
    printf("%d ", root->data);
    reversedinorder(root->left);
}


int main(){
    int n, data;
    struct node *root = NULL;
    scanf("%d",&n);
    for(int i = 0 ; i < n ; i++){
        scanf("%d",&data);
        root = insert(root, data);
    }
    forwardinorder(root);
    printf("\n");
    reversedinorder(root);
    
}


// Problem Statement



// A city's botanical garden is hosting a special event where they want to arrange a set of flower beds in a hierarchical structure and display them in a specific order to create a visual spiral effect.



// The event organizers have a data structure representing the hierarchy of flower beds, where each node represents a flower bed, and each node can have at most two children representing sub-flower beds. They want to print the arrangement of these flower beds-level by level but in a spiral order: the first level from left to right, the next level from right to left, and so on.

// Input format :
// The input consists of seven space-separated integers representing the flower beds in the following order:

// a - the root flower bed.

// a1 - the left child of the root.

// b - the right child of the root.

// b1 - the left child of a1.

// c - the right child of a1.

// c1 - the left child of b.

// d - the right child of b.

// Output format :
// The output is a single line of integers representing the flower beds displayed in a spiral order, separated by spaces.



// Refer to the sample output for the formatting specifications.

// Code constraints :
// The input consists of 7 integers.

// The binary tree is not empty.

// 1 ≤ elements ≤ 100

// Sample test cases :
// Input 1 :
// 1 2 3 7 6 5 4
// Output 1 :
// 1 2 3 4 5 6 7 
// Input 2 :
// 2 3 4 5 6 7 1
// Output 2 :
// 2 3 4 1 7 6 5 




#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node* left;
    struct Node* right;
};


struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


void spiralOrderTraversal(struct Node* root) {
    if (root == NULL) return;

    struct Node* queue[100]; 
    int front = -1, rear = -1;
    int leftToRight = 1; 

    queue[++rear] = root;
    
    while (front < rear) {
        int levelSize = rear - front;
        int currentLevel[100]; 
        int index = 0;

     
        for (int i = 0; i < levelSize; i++) {
            struct Node* node = queue[++front]; 
            currentLevel[index++] = node->value; 

            if (node->left) queue[++rear] = node->left;
            if (node->right) queue[++rear] = node->right;
        }
        if (leftToRight) {
            for(int i = index - 1; i >= 0; i--) {
                printf("%d ", currentLevel[i]);
            }
        } else {
            for (int i = 0; i < index; i++) {
                printf("%d ", currentLevel[i]);
            }
        }
        leftToRight = !leftToRight;
    }
}

int main() {
    int a, a1, b, b1, c, c1, d;

    scanf("%d %d %d %d %d %d %d", &a, &a1, &b, &b1, &c, &c1, &d);

    struct Node* root = createNode(a);
    root->left = createNode(a1);
    root->right = createNode(b);
    root->left->left = createNode(b1);
    root->left->right = createNode(c);
    root->right->left = createNode(c1);
    root->right->right = createNode(d);

    spiralOrderTraversal(root);

    return 0;
}





// Problem Statement



// Sakshi is given a binary tree and her task is to generate its zig-zag level order traversal. Help her with a suitable program.



// Example 1:

// Input:



// Output:

// 1 3 2 4 5 6 7

// Input format :
// The first line consists of an integer n, representing the number of elements (nodes) in the binary tree.

// The second line contains n space-separated integers representing the values of the nodes in level order.

// Output format :
// The output prints a single line containing the Zig-Zag Level Order Traversal of the Binary Tree.



// Refer to the sample output for the formatting specifications.

// Code constraints :
// In this scenario, the given test cases will fall under the following constraints:

// 1 ≤ n ≤ 20

// 1 ≤ node values ≤ 100

// Sample test cases :
// Input 1 :
// 5
// 18 59 20 83 88
// Output 1 :
// 18 20 59 83 88 
// Input 2 :
// 7
// 1 2 3 4 5 6 7
// Output 2 :
// 1 3 2 4 5 6 7 




#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct node *newNode(int data) {
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

struct node *insert(struct node *root, int data) {
    struct node *new_node = newNode(data);
    if (root == NULL) {
        return new_node;
    }
    
    struct node *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct node *temp = queue[front++];
        
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

void zigzagTraversal(struct node *root) {
    if (root == NULL) return;

    struct node *stack1[100], *stack2[100]; 
    int top1 = -1, top2 = -1;

  
    stack1[++top1] = root;


    while (top1 >= 0 || top2 >= 0) {
    
        while (top1 >= 0) {
            struct node *temp = stack1[top1--];
            printf("%d ", temp->data);

            if (temp->left) {
                stack2[++top2] = temp->left;
            }
            if (temp->right) {
                stack2[++top2] = temp->right;
            }
        }

        while (top2 >= 0) {
            struct node *temp = stack2[top2--];
            printf("%d ", temp->data);

            if (temp->right) {
                stack1[++top1] = temp->right;
            }
            if (temp->left) {
                stack1[++top1] = temp->left;
            }
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

  
    zigzagTraversal(root);
    printf("\n");

    return 0;
}



// Binary Tree Maximum Path Sum



// A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. A node can only appear in the sequence at most once. Note that the path does not need to pass through the root.



// The path sum of a path is the sum of the node's values in the path.

// Given the root of a binary tree, return the maximum path sum of any non-empty path.



// Example1:

// Input Format: Enter the value for the Root, Left subtree, Right subtree 

// The first line of the input is the root node.

// 7

// Left subtree 7:5

// Left subtree 5:-1

// Right subtree 5:-1

// Right subtree 7:8

// Left subtree 8:9

// Left subtree 9:-1

// Right subtree 9:-1

// Right subtree 8:1

// Left subtree 1:-1

// Right subtree 1:-1

// Output:

// Maximum Path Sum 29

// Binary Tree

//     7

//    / \

//    5  8

//   / \  \

//  -1  -1  1

//      / \

//     -1 -1



// Example2:

// Input: Enter the value for the Root, Left subtree, Right subtree 

// The first line of the input is the root node.

//  -10

// Left subtree -10:9

// Left subtree 9:-1

// Right subtree 9:-1

// Right subtree -10:20

// Left subtree 20:15

// Left subtree 15:-1

// Right subtree 15:-1

// Right subtree 20:7

// Left subtree 7:-1

// Right subtree 7:-1

// Output: 

// Maximum Path Sum 42

// Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 = 42.

// Binary Tree

//    -10

//   /  \

//   9   20

//     /  \

//    15   7



// Note: Root value (or -1 for null)

// Input format :
// The first line of the input consists of the root node.

// The following inputs consist of the Left subtree and right subtree.



// Note: if there is no child node input -1 for null.

// Output format :
// The output displays the Maximum Path Sum.

// Code constraints :
// The number of nodes in the tree is in the range [1, 3 * 104].

// -1000 <= Node.val <= 1000

// Sample test cases :
// Input 1 :
// 7 5 -1 -1 8 9 -1 -1 1 -1 -1
// Output 1 :
// Maximum Path Sum 29
// Input 2 :
// -10 9 -1 -1 20 15 -1 -1 7 -1 -1
// Output 2 :
// Maximum Path Sum 42

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Definition for a binary tree node
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Function prototypes
TreeNode* createNode(int val);
TreeNode* buildTree();
int maxPathSum(TreeNode* root, int* maxSum);
int findMaxPath(TreeNode* node, int* maxSum);

int main() {
    TreeNode* root = buildTree();
    int maxSum = INT_MIN;
    maxPathSum(root, &maxSum);
    printf("Maximum Path Sum %d\n", maxSum);
    return 0;
}

// Create a new tree node
TreeNode* createNode(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Build the tree from input
TreeNode* buildTree() {
    int rootValue;
    scanf("%d", &rootValue);
    if (rootValue == -1) {
        return NULL;
    }

    TreeNode* root = createNode(rootValue);
    root->left = buildTree();
    root->right = buildTree();

    return root;
}

// Compute the maximum path sum in the binary tree
int maxPathSum(TreeNode* root, int* maxSum) {
    if (root == NULL) {
        return 0;
    }

    int leftSum = findMaxPath(root->left, maxSum);
    int rightSum = findMaxPath(root->right, maxSum);

    int currentPathSum = root->val + (leftSum > 0 ? leftSum : 0) + (rightSum > 0 ? rightSum : 0);

    if (currentPathSum > *maxSum) {
        *maxSum = currentPathSum;
    }

    return root->val + (leftSum > rightSum ? leftSum : rightSum);
}

// Recursive function to find the maximum path sum starting from a given node
int findMaxPath(TreeNode* node, int* maxSum) {
    if (node == NULL) {
        return 0;
    }

    int leftSum = findMaxPath(node->left, maxSum);
    int rightSum = findMaxPath(node->right, maxSum);

    int currentPathSum = node->val + (leftSum > 0 ? leftSum : 0) + (rightSum > 0 ? rightSum : 0);

    if (currentPathSum > *maxSum) {
        *maxSum = currentPathSum;
    }

    return node->val + (leftSum > rightSum ? leftSum : rightSum);
}


//***********************************************************************************************************************************************************************

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

struct node *insertLevelOrder(int arr[], struct node *root, int i, int n){
  if(i<n){
    struct node *temp = newNode(arr[i]);
    root = temp;
    root->left = insertLevelOrder(arr, root->left, 2*i + 1, n);
    root->right = insertLevelOrder(arr, root->right, 2*i + 2, n);
  }
  return root;
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
  struct node *root = NULL;
  int n;
  scanf("%d", &n);
  int arr[n];
  for(int i = 0 ; i < n ; i++){
    scanf("%d", &arr[i]);
  }
  root = insertLevelOrder(arr, root, 0, n);
  inorder(root);
}
