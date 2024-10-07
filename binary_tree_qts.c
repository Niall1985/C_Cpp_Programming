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
