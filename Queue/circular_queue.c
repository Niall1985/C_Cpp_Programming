#include<stdio.h>
#define MAX 5

int queue[MAX];
int front = -1;
int rear = -1;

int isFull(){
  return (rear+1)%MAX == front;
}

int isEmpty(){
  return front == -1;
}


void enqueue(int data){
  if(isFull()){
    printf("Queue Overflow!\n");
  }
  if(front == -1){
    front = 0;
  }
  rear = (rear+1)%MAX;
  queue[rear] = data;
  // printf("%d\n", queue[rear]);
}


int dequeue(){
  if(isEmpty()){
    printf("Queue is empty\n");
    return -1;
  }
  
  int data = queue[front];
  if(rear == front){
    rear = front = -1;
  }
  else{
    front = (front+1)%MAX;
  }
  return data;
}


void display(){
  if(isEmpty()){
    printf("Queue is empty");
  }
  else{
    int i = front;
    while(i != rear){
      printf("%d ",queue[i]);
      i = (i+1)%MAX;
    }
    printf("%d\n", queue[rear]);
  }
}



int main(){
  int n, id;
  scanf("%d",&n);
  for(int i=0;i<n;i++){
    scanf("%d",&id);
    enqueue(id);
  }
  display();
}
