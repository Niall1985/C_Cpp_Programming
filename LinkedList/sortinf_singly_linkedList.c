#include <stdio.h>
#include <stdlib.h>

struct node{
  int data;
  struct node *next;
};

struct node *head = NULL;

void insertEnd(int data){
  struct node *newNode = (struct node*)malloc(sizeof(struct node));
  newNode->data = data;
  newNode->next = NULL;
  if(head==NULL){
    head = newNode;
  }
  else{
    struct node *traverse = head;
    while(traverse->next != NULL){
      traverse = traverse->next;
    }
    traverse->next = newNode;
  }
}

void display(){
  struct node *traverse = head;
  while(traverse != NULL){
    printf("%d ",traverse->data);
    traverse = traverse->next;
  }
}

void sort(){
  if(head == NULL){
    return;
  }
  struct node *i;
  struct node *j;
  int temp;
  for(i=head; i != NULL; i = i->next){
    for(j = i->next; j != NULL; j = j -> next){
      if(i->data < j->data){
        temp = i->data;
        i->data = j->data;
        j->data = temp;
      }
    }
  }
}

void sort1(){
  if(head == NULL){
    return;
  }
  struct node *i;
  struct node *j;
  int temp;
  for(i=head; i != NULL; i = i->next){
    for(j = i->next; j != NULL; j = j -> next){
      if(i->data > j->data){
        temp = i->data;
        i->data = j->data;
        j->data = temp;
      }
    }
  }
}

int main(){
  insertEnd(3);
  insertEnd(5);
  insertEnd(2);
  insertEnd(4);
  insertEnd(1);
  printf("Original\n");
  display();
  printf("\n");
  printf("Descending\n");
  sort();
  display();
  printf("\n");
  printf("Ascending\n");
  sort1();
  display();
}
