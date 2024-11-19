// You are using GCC
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
    struct node *prev;
};

struct node *head = NULL;
struct node *prev = NULL;

struct node *insertEnd(int data){
    struct node *ptr = (struct node*)malloc(sizeof(struct node));
    ptr->data = data;
    ptr->next = NULL;
    if(head == NULL){
        ptr->prev = NULL;
        head = ptr;
    }
    else{
        struct node *traverse = head;
        while(traverse->next != NULL){
            traverse = traverse->next;
        }
        traverse->next = ptr;
        ptr->next = NULL;
        ptr->prev = traverse;
    }
}


struct node *deleteNode(int index){
    if(head == NULL){
        return NULL;
    }
    struct node *traverse = head;
    int count = 1;
    while(count != index){
        traverse = traverse->next;
        count++;
        if(traverse == NULL){
            return head;
        }
    }
    if(traverse == head){
        head = traverse->next;
        if(head != NULL){
            head->prev = NULL;
        }
    }
    else{
        traverse->prev->next = traverse->next;
        if(traverse->next != NULL){
            traverse->next->prev = traverse->prev;
        }
    }
    free(traverse);
    return head;
}


void print(){
    struct node *print = head;
    int count = 0;

    printf("Data entered in the list:\n");
    while(print != NULL){
        count++;
        printf("Node %d : %d\n", count, print->data);
        print = print->next;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    int data;
    for(int i = 0 ; i < n ; i++){
        scanf("%d", &data);
        insertEnd(data);
    }
    print();
    int x;
    scanf("%d", &x);
    deleteNode(x);
    printf("After deletion\n");
    print();
    
}
