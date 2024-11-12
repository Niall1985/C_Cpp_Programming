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




// input
// 1 101
// 1 202
// 1 203
// 1 204
// 1 205
// 1 206
// 3
// 2
// 3
// 4

// output:
// Enter your choice (1: Enqueue, 2: Dequeue, 3: Display, 4: Exit): Enter ticket ID to enqueue: Helpdesk Ticket ID 101 is enqueued.

// Enter your choice (1: Enqueue, 2: Dequeue, 3: Display, 4: Exit): Enter ticket ID to enqueue: Helpdesk Ticket ID 202 is enqueued.

// Enter your choice (1: Enqueue, 2: Dequeue, 3: Display, 4: Exit): Enter ticket ID to enqueue: Helpdesk Ticket ID 203 is enqueued.

// Enter your choice (1: Enqueue, 2: Dequeue, 3: Display, 4: Exit): Enter ticket ID to enqueue: Helpdesk Ticket ID 204 is enqueued.

// Enter your choice (1: Enqueue, 2: Dequeue, 3: Display, 4: Exit): Enter ticket ID to enqueue: Helpdesk Ticket ID 205 is enqueued.

// Enter your choice (1: Enqueue, 2: Dequeue, 3: Display, 4: Exit): Enter ticket ID to enqueue: Queue is full. Cannot enqueue.

// Enter your choice (1: Enqueue, 2: Dequeue, 3: Display, 4: Exit): Helpdesk Ticket IDs in the queue are: 101 202 203 204 205 

// Enter your choice (1: Enqueue, 2: Dequeue, 3: Display, 4: Exit): Dequeued Helpdesk Ticket ID 101

// Enter your choice (1: Enqueue, 2: Dequeue, 3: Display, 4: Exit): Helpdesk Ticket IDs in the queue are: 202 203 204 205 

// Enter your choice (1: Enqueue, 2: Dequeue, 3: Display, 4: Exit): Exiting the program
