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
    struct Node* temp = *head;
    struct Node* prev = NULL;
    if(temp != NULL && temp->data == value){
        *head = temp->next;
        free(temp);
        return;
    }
    while(temp != NULL && temp->data != value){
        prev = temp;
        temp = temp->next;
    }
    
    if(temp == NULL){
        return;
    }
    prev->next = temp->next;
    free(temp);
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
