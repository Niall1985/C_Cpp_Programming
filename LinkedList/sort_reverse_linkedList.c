// You are using GCC
#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

struct node* head = NULL;
struct node* current = NULL;

void print(){
    struct node* print = head;
    while(print != NULL){
        printf("%d ",print->data);
        print = print->next;
    }
}


void insertBegining(int data){
    struct node *lk = (struct node*)malloc(sizeof(struct node));
    lk->data = data;
    lk->next = head;
    head = lk;
}

struct node* reverseList(struct node* head){
    struct node *prev = NULL, *current = head, *next=NULL;
    while(current != NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

void processList(){
    struct node *even = NULL, *odd=NULL;
    struct node *current = head;
    while(current != NULL){
        struct node *newNode = (struct node*)malloc(sizeof(struct node));
        newNode->data = current->data;
        if(current->data % 2 == 0){
            newNode->next = even;
            even = newNode;
        }
        else{
            newNode->next = odd;
            odd = newNode;
        }
        current = current->next;
    }
    even = reverseList(even);
    odd = reverseList(odd);
    
    head = even;
    if(even == NULL){
        head = odd;
    }
    else{
        struct node *tail = even;
        while(tail->next != NULL){
            tail = tail->next;
        }
        tail->next = odd;
    }
}



int main(){
    int n, data;
    scanf("%d",&n);
    for(int i = 0 ; i < n ; i++){
        scanf("%d",&data);
        insertBegining(data);
    }
    // print();
    // printf("\n");
    // sortListEven();
    processList();
    print();
}
