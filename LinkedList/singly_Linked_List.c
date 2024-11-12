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




//insert at index
// You are using GCC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    int data;
    struct node* next;
};

struct node *head = NULL;
struct node *current = NULL;

void print(){
    struct node* p = head;
    while(p != NULL){
        printf("%d ", p->data);
        p = p->next;
    }
}


void insertBegining(int data){
    struct node *lk = (struct node*)malloc(sizeof(struct node));
    lk-> data = data;
    lk->next = head;
    head=lk;
}

void insertatpos(int index, int data){
    struct node *lk = (struct node*)malloc(sizeof(struct node));
    lk->data=data;
    if(index == 0){
        lk->next = head;
        head = lk;
        return;
    }
    
    struct node* temp = head;
    for(int i=0; temp != NULL & i<index-1; i++){
        temp = temp->next;
    }
    lk->next = temp->next;
    temp->next = lk;
}


int main(){
    int n, data;
    scanf("%d",&n);
    for(int i = 0 ; i < n ; i++){
        scanf("%d",&data);
        insertBegining(data);
    }
    
    int element;
    scanf("%d",&element);
    insertatpos(1, element);
    print();
}



***********************************************************************************

// Print unique elements in a linkedList
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    int data;
    struct node *next;
};

struct node *head = NULL;
struct node *current  = NULL;

void print(){
    struct node *p = head;
    while(p != NULL){
        struct node *q = head;
        int isUnique = 1;
        while(q != p){
            if(q->data == p->data){
                isUnique=0;
                break;
            }
            q=q->next;
        }
        if(isUnique){
            printf("%d ",p->data);
        }
        p = p->next;
    }
    printf("\n");
}

void insertAtEnd(int data){
    struct node *lk = (struct node*)malloc(sizeof(struct node));
    lk->data = data;
    lk->next = NULL;
    if(head == NULL){
        head=lk;
        return;
    }
    
    struct node *list = head;
    while(list->next != NULL)
        list = list->next;
    list->next = lk;
}


int main(){
    int T;
    scanf("%d", &T);
    for(int i = 0 ; i < T ; i++){
        int n;
        scanf("%d",&n);
        int data;
        for(int j = 0 ; j < n ;j++){
            scanf("%d",&data);
            insertAtEnd(data);
        }
        print();
        head=NULL;
    }
}
