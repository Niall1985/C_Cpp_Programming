// Problem Statement



// Akash wants to write a program that populates values in a singly linked list by inserting each element into the front of the list. After insertion, the program should delete a node immediately after a node with a specific value X. 



// Assist him with a suitable program.

// Input format :
// The first line of input consists of an integer N, representing the number of elements.

// The second line consists of N space-separated integers, representing the elements of the linked list.

// The third line consists of an integer X, representing the value after which the node has to be deleted.

// Output format :
// The first line of output prints the elements of the original linked list in the format: "Original Linked List: " followed by the linked list elements, separated by " -> " and ending with "NULL".

// The second line prints the modified linked list after deleting the node after the value X in the format: "After deleting node after X: " followed by the modified linked list elements, separated by " -> " and ending with "NULL".



// Refer to the sample output for formatting specifications.

// Code constraints :
// 2 ≤ N ≤ 10

// 1 ≤ elements of the linked list ≤ 100

// X will be a value present in the linked list excluding the first and last elements.

// Sample test cases :
// Input 1 :
// 4
// 15 28 36 43
// 36
// Output 1 :
// Original Linked List: 43 -> 36 -> 28 -> 15 -> NULL
// After deleting node after 36: 43 -> 36 -> 15 -> NULL
// Input 2 :
// 5
// 1 2 3 4 5
// 2
// Output 2 :
// Original Linked List: 5 -> 4 -> 3 -> 2 -> 1 -> NULL
// After deleting node after 2: 5 -> 4 -> 3 -> 2 -> NULL



// You are using GCC
#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *next;
};

struct Node* createNode(int data){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if(!newNode){
        exit(1);
    }
    
    newNode -> data = data;
    newNode -> next = NULL;
    return newNode;
}

void insertFront(struct Node** head, int data){
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

void deleteNode(struct Node** head, int value){
   if(*head == NULL){
       return;
   }
   
   struct Node* temp = *head;
   
   while(temp != NULL && temp -> data != value){
       temp = temp->next;
   }
   if(temp != NULL && temp -> next != NULL){
       struct Node* nodeToDelete = temp-> next;
       temp -> next = nodeToDelete -> next;
       free(nodeToDelete);
   }
}

void display(struct Node* head){
    struct Node* temp = head;
    while(temp != NULL){
    printf("%d -> ", temp->data);
    temp = temp->next;
    }
    printf("NULL\n");
}

int main(){
    struct Node* head = NULL;
    int n;
    scanf("%d",&n);
    for(int i = 0 ; i < n ; i++){
        int data;
        scanf("%d", &data);
        insertFront(&head, data);
    }
    printf("Original Linked List: ");
    display(head);
    int del;
    scanf("%d", &del);
    deleteNode(&head, del);
    printf("After deleting node after %d: ",del);
    display(head);
}
