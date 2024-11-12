#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int stack[MAX];
int top = -1;

void pop(){
  if(top == -1){
  printf("Stack underflow");
  }
  else{
    printf("Popped %d from the stack.\n",stack[top]);
    top--;
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
    top++;
    stack[top] = 10;
    top++;
    stack[top] = 20;
    top++;
    stack[top] = 30;
    
    pop();
    pop();
    
    display();
}

// output
// Popped 30 from the stack.
// Popped 20 from the stack.
// 10
