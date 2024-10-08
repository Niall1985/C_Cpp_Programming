#include <stdio.h>
#include <stdlib.h>

struct node{
  int data;
  struct node *left;
  struct node *right;
};

struct node *newNode(int data){
  struct node *temp = (struct node*)malloc(sizeof(struct node));
  temp->data=data;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
}

struct node *insert(struct node *root, int data){
  if(root == NULL){
    return newNode(data);
  }
  
  if(data<root->data){
    root->left = insert(root->left, data);
  }
  else if(data>root->data){
    root->right = insert(root->right, data);
  }
  return root;
}

struct node *minValueNode(struct node *root){
  struct node *current = root;
  while(current && current->left != NULL){
    current = current->left;
  }
  return current;
}


struct node *delete(struct node *root, int key){
  if(root==NULL){ //basecase to check if the tree is empty
    return root;
  }
  if(key<root->data){ //iterate down the left side to find the element we want to delete
    root->left = delete(root->left, key);
  }
  else if(key>root->data){ //iterate down the right side to find the element we want to delete
    root->right = delete(root->right, key);
  }
  else{
    if(root->left == NULL && root->right == NULL){ //the node has no childer
      free(root);
      return NULL;
    }
    else if(root->left == NULL){ //the node has only children to the right
      struct node *temp = root->right;
      free(root);
      return temp;
    }
    else if(root->right == NULL){ //the node has only children to the left
      struct node *temp = root->left;
      free(root);
      return temp;
    }
    
    struct node *temp = minValueNode(root->right); //the node has both children
    root->data = temp->data;
    root->right = delete(root->right, temp->data);
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
    int n, data, key;
    struct node *root = NULL;
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++){
        scanf("%d", &data);
        root = insert(root, data);
    }
    scanf("%d", &key);
    root=delete(root, key);
    inorder(root);
}





// You are using GCC
#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *left, *right;
};

struct node *newNode(int data){
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

struct node *insert(struct node *root, int data){
    if(root == NULL){
        return newNode(data);
    }
    
    if(data<root->data){
        root->left = insert(root->left, data);
    }
    else if(data>root->data){
        root->right = insert(root->right, data);
    }
    return root;
}

void kthmin(struct node *root, int k, int *count, int *result){
    if(root == NULL || *result != -1){
        return;
    }
    
    kthmin(root->left, k, count, result);
    (*count)++;
    if(*count == k){
        *result = root->data;
        return;
    }
    kthmin(root->right, k, count, result);
}

int main() {
    int data;
    struct node *root = NULL;
    
    while (1) {  
        scanf("%d", &data);
        if (data == -1) {  
            break;
        }
        root = insert(root, data);
    }

    int k;
    scanf("%d", &k);

    int count = 0;
    int result = -1;
    kthmin(root, k, &count, &result);

    if (result != -1) {
        printf("%d\n", result);
    }

    return 0;
}







//Q) Find the successor of a target element
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

void inorder(struct node *node, int *arr, int *index){
  if(node==NULL){
    return;
  }
  
  inorder(node->left, arr, index);
  arr[(*index)++] = node->data;
  inorder(node->right, arr, index);
}

int printSuccessor(int *arr, int n, int k){
  for(int i = 0 ; i  < n ; i++){
    if(arr[i] == k && i+1 < n){
      return arr[i+1];
    }
  }
  return -1;
}

int main(){
  int n, data, key;
  struct node *root = NULL;
  scanf("%d", &n);
  int arr[n];
  int index = 0;
  for(int i = 0 ; i < n ; i++){
    scanf("%d", &data);
    root= insert(root, data);
  }
  scanf("%d", &key);
  inorder(root, &arr, &index);
  int res = printSuccessor(&arr, n, key);
  
  if(res != -1){
    printf("Successor of %d is %d", key, res);
  }
  else{
    printf("Nahbro");
  }
}

//****************************************************************************************************************************************************************************







// Q)Problem Statement
// John is learning about Binary Search Trees (BST) in his computer science class. He wants to create a program that allows users to delete a node with a given value from a BST and print the remaining nodes.
// Implement a function to help him delete a node with a given value from a BST.

// Input format :
// The first line of input consists of an integer N, representing the number of nodes in the BST.

// The second line consists of N space-separated integers, representing the values of the BST nodes.

// The third line consists of an integer V, which is the value to delete from the BST.

// Output format :
// The output prints the space-separated values in the BST in an in-order traversal, after the deletion of the specified value.

// If the specified value is not available in the tree, print the given input values in-order traversal.



// Refer to the sample output for the formatting specifications.

// Code constraints :
// The given test cases will fall under the following constraints:

// 1 ≤ N ≤ 10

// 1 ≤ node values ≤ 100

// 1 ≤ V ≤ 100

// The input values are unique integers.

// Sample test cases :
// Input 1 :
// 5
// 10 5 15 2 7
// 15
// Output 1 :
// 2 5 7 10 
// Input 2 :
// 7
// 50 30 70 20 40 60 80
// 50
// Output 2 :
// 20 30 40 60 70 80 
// Input 3 :
// 3
// 4 7 6
// 8
// Output 3 :
// 4 6 7 


#include <stdio.h>
#include<stdlib.h>

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

struct node *insert(struct node *temp, int data){
    if(temp == NULL){
        return newNode(data);
    }
    if(data<temp->data){
        temp->left = insert(temp->left,data);
    }
    else if(data>temp->data){
        temp->right = insert(temp->right,data);
    }
    return temp;
}

struct node *minValueNode(struct node *node) {
    struct node *current = node;
  
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}


struct node *deleteNode(struct node *temp, int key){
    if(temp == NULL){
        return temp;
    }
    
    if(key < temp->data){
        temp->left = deleteNode(temp->left, key);
    }
    else if(key>temp->data){
        temp->right = deleteNode(temp->right, key);
    }
    else{
        if(temp->left == NULL && temp->right == NULL){
            free(temp);
            return NULL;
        }
        
        if(temp->left == NULL){
            struct node *root = temp->right;
            free(temp);
            return root;
        }
        else if(temp->right == NULL){
            struct node *root = temp->left;
            free(temp);
            return root;
        }
        
        struct node *root = minValueNode(temp->right);
            temp->data = root->data;
            temp->right = deleteNode(temp->right, root->data);
        }
    return temp;
}

void inorder(struct node *temp){
    if(temp == NULL){
        return;
    }
    inorder(temp->left);
    printf("%d ", temp->data);
    inorder(temp->right);
}
int main(){
    int n, data, key;
    struct node *root = NULL;
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++){
        scanf("%d", &data);
        root = insert(root, data);
    }
    scanf("%d", &key);
    root=deleteNode(root, key);
    inorder(root);
}


// Problem Statement
// Kamal is interested in managing a collection of integers using a Binary Search Tree (BST). 
//He wants to write a program that constructs a BST from a given set of integers and then deletes all the nodes with values greater than the average value of all nodes in the BST.
// Help him solve this problem.
// Example

// Input:

// 5

// 10 20 30 40 50

// Output:

// 10 20 30

// Explanation:

// The sum of values is 10 + 20 + 30 + 40 + 50 = 150, and there are 5 nodes. So, the average is 150 / 5 = 30. Then, delete nodes with values greater than the average (30). The final output is the values of the remaining nodes in the BST, which are 10, 20 and 30.

// Input format :
// The first line consists of an integer N, representing the number of elements in the BST.

// The second line consists of N space-separated integers, representing the BST elements.

// Output format :
// The output prints the remaining integers in the BST after deleting nodes greater than the average value, separated by a space.

// The integers should be printed in an in-order traversal.



// Refer to the sample output for the formatting specifications.

// Code constraints :
// The given test cases will fall under the following constraints:

// 1 ≤ N ≤ 20

// 1 ≤ elements ≤ 1000

// Sample test cases :
// Input 1 :
// 5
// 10 20 30 40 50
// Output 1 :
// 10 20 30 
// Input 2 :
// 6
// 20 52 65 98 74 57
// Output 2 :
// 20 52 57 

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


struct node *insert(struct node *root, int data){
    if(root == NULL){
        return newNode(data);
    }
    
    if(data<root->data){
        root->left = insert(root->left, data);
    }
    else if(data>root->data){
        root->right = insert(root->right, data);
    }
    return root;
}

struct node *minValueNode(struct node *node) {
    struct node *current = node;
  
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}


struct node *deleteNode(struct node *temp, int key){
    if(temp == NULL){
        return temp;
    }
    
    if(key < temp->data){
        temp->left = deleteNode(temp->left, key);
    }
    else if(key>temp->data){
        temp->right = deleteNode(temp->right, key);
    }
    else{
        if(temp->left == NULL && temp->right == NULL){
            free(temp);
            return NULL;
        }
        
        if(temp->left == NULL){
            struct node *root = temp->right;
            free(temp);
            return root;
        }
        else if(temp->right == NULL){
            struct node *root = temp->left;
            free(temp);
            return root;
        }
        
        struct node *root = minValueNode(temp->right);
            temp->data = root->data;
            temp->right = deleteNode(temp->right, root->data);
        }
    return temp;
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
    int n, data, sum = 0;
    scanf("%d", &n);
    int arr[n];
    for(int i = 0 ; i < n ; i++){
        scanf("%d", &data);
        root = insert(root, data);
        arr[i] = data;
        sum += data;
    }
    
    int avg = sum/n;
    for(int i = 0 ; i < n ; i++){
        if(arr[i]>avg){
            root = deleteNode(root, arr[i]);
        }
    }
    
    inorder(root);
}





// Jay is studying binary search trees (BSTs) as part of his computer science curriculum. He is particularly interested in understanding operations like insertion and deletion in a BST.



// Jay wants to write a program that takes a sequence of characters as input, constructs a BST using those characters, deletes the minimum element from the BST, and then outputs the elements of the tree in sorted order.



// Help Jay by designing a program that achieves this.

// Input format :
// The first line of input contains an integer n, denoting the number of characters to be inserted into the BST.

// The second line contains n space-separated characters, each character representing a node to be inserted into the BST.

// Output format :
// The output displays a single line displaying the space-separated characters of the BST in sorted order after deleting the minimum element in the format:

// "Inorder traversal after deleting the minimum element:"

// "[char1] [char2] ...[char_n]"



// Refer to the sample output for the formatting specifications.

// Code constraints :
// The given test cases will fall under the following constraints:

// 1 ≤ n ≤ 10

// Characters are uppercase English alphabets.

// All characters in the input are distinct.

// Sample test cases :
// Input 1 :
// 6
// K J M V H F
// Output 1 :
// Inorder traversal after deleting the minimum element:
// H J K M V 
// Input 2 :
// 4
// T B C A
// Output 2 :
// Inorder traversal after deleting the minimum element:
// B C T 






#include <stdio.h>
#include <stdlib.h>

struct node{
    char data;
    struct node *left;
    struct node *right;
};

struct node *newNode(char data){
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}


struct node *insert(struct node *root, char data){
    if(root == NULL){
        return newNode(data);
    }
    
    if(data<root->data){
        root->left = insert(root->left, data);
    }
    else if(data>root->data){
        root->right = insert(root->right, data);
    }
    return root;
}

struct node *minValueNode(struct node *node) {
    struct node *current = node;
  
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}


struct node *deleteNode(struct node *temp, char key){
    if(temp == NULL){
        return temp;
    }
    
    if(key < temp->data){
        temp->left = deleteNode(temp->left, key);
    }
    else if(key>temp->data){
        temp->right = deleteNode(temp->right, key);
    }
    else{
        if(temp->left == NULL && temp->right == NULL){
            free(temp);
            return NULL;
        }
        
        if(temp->left == NULL){
            struct node *root = temp->right;
            free(temp);
            return root;
        }
        else if(temp->right == NULL){
            struct node *root = temp->left;
            free(temp);
            return root;
        }
        
        struct node *root = minValueNode(temp->right);
            temp->data = root->data;
            temp->right = deleteNode(temp->right, root->data);
        }
    return temp;
}

void inorder(struct node *root){
    if(root == NULL){
        return;
    }
    
    inorder(root->left);
    printf("%c ", root->data);
    inorder(root->right);
}
int main(){
    struct node *root = NULL;
    int n;
    char data;
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++){
        scanf(" %c", &data);
        root = insert(root, data);
    }
    struct node *minNode = minValueNode(root);
    root = deleteNode(root, minNode->data);
   
    printf("Inorder traversal after deleting the minimum element:\n");
    inorder(root);
}






// Problem Statement



// Emily is studying binary search trees (BST). She wants to write a program that inserts characters into a BST and then finds and prints the minimum and maximum values.



// Guide her with the program.

// Input format :
// The first line of input consists of an integer N, representing the number of values to be inserted into the BST.

// The second line consists of N space-separated characters.

// Output format :
// The first line of output prints "Minimum value: " followed by the minimum value of the given inputs.

// The second line prints "Maximum value: " followed by the maximum value of the given inputs.



// Refer to the sample outputs for formatting specifications.

// Code constraints :
// The input values will be upper-case characters.

// Sample test cases :
// Input 1 :
// 5
// Z E W T Y
// Output 1 :
// Minimum value: E
// Maximum value: Z
// Input 2 :
// 7
// S P O R T Y U
// Output 2 :
// Minimum value: O
// Maximum value: Y


// You are using GCC
#include <stdio.h>
#include <stdlib.h>

struct node {
    char data;
    struct node *left, *right;
};

struct node* newNode(char data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

struct node* insert(struct node* node, char data) {
    if (node == NULL)
        return newNode(data);
    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    return node;
}

struct node* minValueNode(struct node* node) {
    struct node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

struct node* maxValueNode(struct node* node) {
    struct node* current = node;
    while (current && current->right != NULL)
        current = current->right;
    return current;
}

int main() {
    int n;
    char data;
    struct node* root = NULL;
    
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf(" %c", &data);
        root = insert(root, data);
    }

    struct node *minNode = minValueNode(root);
    printf("Minimum value: %c\n", minNode->data);
    
    struct node *maxNode = maxValueNode(root);
    printf("Maximum value: %c", maxNode->data);

    return 0;
}





// Given a Binary Search Tree (BST) and an integer k, your task is to implement the kthSmallest function. The function should take the root of the BST and an integer k as input and return the k-th smallest element in the BST.

// Input format :
// The first line of input consists of a sequence of integers representing the elements of the BST. The input is terminated by -1.

// The second line consists of an integer k, representing the position of the desired smallest element.

// Output format :
// The output prints a single integer, which is the kth smallest element in the BST.



// Refer to the sample output for formatting specifications.

// Code constraints :
// 1 <= val <= 100

// 1 <= k <= number of elements in the BST

// Sample test cases :
// Input 1 :
// 20 8 22 4 12 10 14 -1
// 3
// Output 1 :
// 10
// Input 2 :
// 20 8 4 12 10 14 22 -1
// 4
// Output 2 :
// 12




#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *left, *right;
};

struct node *newNode(int data){
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

struct node *insert(struct node *root, int data){
    if(root == NULL){
        return newNode(data);
    }
    
    if(data<root->data){
        root->left = insert(root->left, data);
    }
    else if(data>root->data){
        root->right = insert(root->right, data);
    }
    return root;
}

void kthmin(struct node *root, int k, int *count, int *result){
    if(root == NULL || *result != -1){
        return;
    }
    
    kthmin(root->left, k, count, result);
    (*count)++;
    if(*count == k){
        *result = root->data;
        return;
    }
    kthmin(root->right, k, count, result);
}

int main() {
    int data;
    struct node *root = NULL;
    
    while (1) {  
        scanf("%d", &data);
        if (data == -1) {  
            break;
        }
        root = insert(root, data);
    }

    int k;
    scanf("%d", &k);

    int count = 0;
    int result = -1;
    kthmin(root, k, &count, &result);

    if (result != -1) {
        printf("%d\n", result);
    }

    return 0;
}
















