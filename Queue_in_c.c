// You are using GCC
#include <stdio.h>
#define MAX 5

int front = 0;
int rear = -1;
int queue[MAX];

int isEmpty(){
    return front>rear;
}

int isFull(){
    return rear == MAX-1;
}

void enqueue(int element){
    if(!isFull()){
        queue[++rear] = element;
        printf("Helpdesk Ticket ID %d is enqueued.\n", element);
    }
    else{
        printf("Queue is full. Cannot enqueue.\n");
    }
}

void dequeue(){
    if(!isEmpty()){
        printf("Dequeued Helpdesk Ticket ID: %d\n", queue[front++]);
    }
    else{
        printf("Queue is empty.\n");
    }
}

void display(){
    if(!isEmpty()){
        printf("Helpdesk Ticket IDs in the queue are: ");
        for(int i = front; i <= rear; i++){
            if(i == rear){
                printf("%d",queue[i]);
            }
            else{
                printf("%d ",queue[i]);
            }
        }
        printf("\n");
    }
    else{
        printf("Queue is empty.\n");
    }
}

int main(){
    int choice, id;
    while(1){
        scanf("%d", &choice);
        
        switch(choice){
            case 1:
            scanf("%d",&id);
            enqueue(id);
            break;
            case 2:
            dequeue();
            break;
            case 3:
            display();
            break;
            case 4:
            printf("Exiting the program\n");
            return 0;
            default:
            printf("Invalid option.\n");
            break;
        }
    }
    
}
