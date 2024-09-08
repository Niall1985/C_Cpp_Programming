// Problem Statement



// Develop a feature to transform infix expressions into prefix notation for improved parsing efficiency and evaluation clarity. The task involves reading infix expressions from source code, converting them using stack-based algorithms to maintain operator precedence, and outputting the resulting prefix notation. 

// Input format :
// The input consists of a string, an infix expression that includes only digits(0-9), and operators(+, -, *, /).

// Output format :
// The output displays the equivalent prefix expression of the given infix expression.



// Refer to the sample output for formatting specifications.

// Code constraints :
// The infix expression will contain only valid arithmetic operators (+, -, *, /), numbers, and parentheses.

// The infix expression will have a maximum length of 30 characters.

// The numbers in the infix expression will be non-negative integers.

// Sample test cases :
// Input 1 :
// (1+2)*(3/4-5)
// Output 1 :
// *+12-/345
// Input 2 :
// 5+(4*8)/2
// Output 2 :
// +5/*482


// You are using GCC
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

int top = -1;
char stack[MAX];

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

int precedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return -1;
}

void reverseString(char str[]) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void infixToPostfix(char infix[], char postfix[]) {
    char stack[MAX];
    int top = -1;
    int k = 0;
    
    for (int i = 0; infix[i]; i++) {
        char c = infix[i];
        
        if (isdigit(c)) {
            postfix[k++] = c;
        } else if (c == '(') {
            stack[++top] = c;
        } else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[k++] = stack[top--];
            }
            top--; 
        } else {
            while (top != -1 && precedence(c) <= precedence(stack[top])) {
                postfix[k++] = stack[top--];
            }
            stack[++top] = c;
        }
    }
    
    while (top != -1) {
        postfix[k++] = stack[top--];
    }
    
    postfix[k] = '\0';
}

void infixToPrefix(char infix[], char prefix[]) {
    char reversedInfix[MAX], reversedPostfix[MAX];
    
    reverseString(infix);
    int len = strlen(infix);
    for (int i = 0; i < len; i++) {
        if (infix[i] == '(') reversedInfix[i] = ')';
        else if (infix[i] == ')') reversedInfix[i] = '(';
        else reversedInfix[i] = infix[i];
    }
    reversedInfix[len] = '\0';
    
    infixToPostfix(reversedInfix, reversedPostfix);
    
    reverseString(reversedPostfix);
    
    strcpy(prefix, reversedPostfix);
}

int main() {
    char infix[MAX];
    char prefix[MAX];
    scanf("%[^\n]s",infix);
    infixToPrefix(infix, prefix);
    
    printf("%s\n", prefix);
    
    return 0;
}
