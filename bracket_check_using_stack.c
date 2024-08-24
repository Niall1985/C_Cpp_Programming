#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100

int stack[100];
int top = -1;

void push(int c){
  if(top == MAX-1){
    printf("Stack Overflow");
  }
  else{
    top++;
    stack[top] = c;
  }
}

char pop(){
  if(top == -1){
    return '\0';
  }
  else{
    return stack[top--];
  }
}

bool is_balanced(const char *expression){
  for(int i=0;i<strlen(expression); i++){
    char current = expression[i];
    if(current == '(' || current == '[' || current == '{'){
      push(current);
    }
    else if(current == ')' || current == ']' || current == '}'){
      int last_open = pop();
      if(current == '(' && last_open != ')' ||
      current == '[' && last_open != ']' ||
      current == '{' && last_open != '}'){
        return false;
      }
    }
  }
  return top == -1;
}

int main() {
    const char *expressions[] = {"(a+b)", "(a+b)*(c+d)", "{a+[b*(c+d)]}", "(a+b", "[(a+b]*c)"};
    
    for (int i = 0; i < 5; i++) {
        if (is_balanced(expressions[i])) {
            printf("%s is balanced.\n", expressions[i]);
        } else {
            printf("%s is not balanced.\n", expressions[i]);
        }
    }

    return 0;
}

// output:
// (a+b) is balanced.
// (a+b)*(c+d) is balanced.
// {a+[b*(c+d)]} is balanced.
// (a+b is not balanced.
// [(a+b]*c) is not balanced.
