#include<stdio.h>

#define MAX 10

int queue[MAX];
int front = 0;
int rear = -1;

int isEmpty(){
    return front > rear;
}

int isFull(){
    return rear == MAX-1;
}

void enqueue(int id){
    if(isFull()){
        printf("Queue is full\n");
    }
    else{
        queue[++rear] = id;
    }
}

int dequeue(){
    if(isEmpty()){
        printf("Queue is empty\n");
    }
    else{
        return queue[front++];
    }
}

void sortByFrequency() {
    int count[MAX] = {0}; 
    int sortedQueue[MAX];   

    for(i = front; i <= rear; i++){
        count[queue[i]]++;
    }

    for(i = front; i < rear; i++){
        for(j = i + 1; j <= rear; j++){
            if(count[queue[i]] < count[queue[j]] || 
               (count[queue[i]] == count[queue[j]] && queue[i] < queue[j])) {
                temp = queue[i];
                queue[i] = queue[j];
                queue[j] = temp;
            }
        }
    }
}

void display(){
    if(isEmpty()){
        printf("Queue is empty\n");
    }
    else{
        printf("Queue sorted by element frequency in descending order: ");
        for(int i = front; i <= rear; i++){
            printf("%d ", queue[i]);
        }
        printf("\n");
    }
}

int main(){
    int n, id;
    
    printf("Enter the number of elements in the queue: ");
    scanf("%d", &n);

    printf("Enter the elements:\n");
    for(int i = 0; i < n; i++){
        scanf("%d", &id);
        enqueue(id);
    }

    sortByFrequency();
    display();

    return 0;
}
