#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int stack[MAX];
int top = -1;

void push(int value){
  if(top == MAX-1){
  printf("Stack overflow");
  }
  else{
    top++;
    stack[top] = value;
    printf("Pushed %d into the stack.\n", value);
  }
}

void display(){
  if(top == -1){
  printf("Stack is empty");
  }
  else{
    for(int i = top; i>=0;i--){
      printf("%d\n", stack[i]);
    }
  }
}
int main()
{
    push(10);
    push(20);
    push(30);
    display();
}


// output
// Pushed 10 into the stack.
// Pushed 20 into the stack.
// Pushed 30 into the stack.
// 30
// 20
// 10
