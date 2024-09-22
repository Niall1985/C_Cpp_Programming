#include<stdio.h>
#include <stdlib.h>

struct node{
  int data; //create a ndoe with two elements, data and a link to the next node
  struct node* link;
};

struct node *head = NULL;
struct node *current = NULL;

void insertBegining(int data){
  struct node *ptr = (struct node*)malloc(sizeof(struct node)); //create a new node
  ptr->data = data; //store the data in the node
  ptr->link = head; //point the node's link to the current head i.e first node
  head=ptr; //update head to the new node
}


void insertEnd(int data){
    struct node *temp = (struct node*)malloc(sizeof(struct node));//new node to insert the data and link
    temp->data=data;//initialize the new node with data
    struct node *list = head; //create a new link for traversal and point it to head
    while(list->link != NULL){//traverse the entire linked list until the link becomes NULL
      list = list->link;//procede to the next node using this
    }
    list->link = temp; //point the last node's next to the new node
}

void insertAfterNode(struct node *list, int data){ //contains the node after which insertion is to be made and data
  struct node *lk = (struct node *)malloc(sizeof(struct node)); //create a new node
  lk->data=data; //fill the data in the node
  lk->link = list->link; //Set the new node's next to the given node's next
  list->next=lk; //set the given node's next to the new node
}

void deleteBegin(){
  head = head->next;
}

void deleteEnd(){
  struct node *list = head; //Start from the head of the list
  while(list->link->link != NULL){ //iterate till the 2nd last node
    list = list->link;
  }
  list->link - NULL; //set the second last node to NULL to indicate end of linkedList
}

void deleteNode(int key){
  struct node *temp = head;
  *prev=NULL; //The prev pointer tracks the node before temp to allow for proper deletion once the node is found.
  if(temp != NULL && temp->data == key){
    head = temp->link;
    free(temp);
    return;
  }
  
  while(temp != NULL && temp->data != key){ //interate throgh the entire list
    prev = temp; //prev is updated to temp before temp is pushed to the next node
    // /This way, when we find the node to delete, prev will already point to the node right before it.
    temp = temp->link; //update temp till key is found
  }
  
  if(temp == NULL)return;
  prev->link = temp->link; ..remove the node
}


int searchList(int key){
  struct node *temp = head; //set temp as the head of the linkedList
  while(temp != NULL){ //iterate through the list
    if(temp->data = key){ //if key is found reutrn 1
      return 1;
    }
    temp = temp->link; //update the temp to iterate through the list till the key is found
  }
  return 0;
}
void print(){
  struct node *p = head;
  while (p != NULL){
    printf("%d ",p->data);
    p=p->link;
  }
}

int main(){
  //your operations go here
}
