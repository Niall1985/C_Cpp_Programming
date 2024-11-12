// Problem Statement



// Tisha wants to learn mathematical expressions and she wants to create a program to accept multiple infix expressions from the user and convert them into postfix expressions using a Stack-based algorithm. 



// The program should prompt the user to enter the number of expressions they wish to convert, and then accept each expression one by one. After converting each infix expression to a postfix, the program should print the corresponding postfix expression to the console. 

// Input format :
// The first line of input consists of an integer N, denoting the number of infix expressions to be converted.

// The following N lines of input consist of the infix expressions to be converted.

// Output format :
// The N lines of output print "Postfix expression T: " where T is the expression number followed by the corresponding postfix expression for N inputs, in separate lines.



// Refer to the sample output for the formatting specifications.

// Code constraints :
// The maximum length of an infix expression is 100 characters.

// The program should support multiple infix expressions.

// The program should use a stack-based algorithm to convert infix expressions to postfix expressions.

// Sample test cases :
// Input 1 :
// 1
// A+B*C-D/E^F
// Output 1 :
// Postfix expression 1: ABC*+DEF^/-
// Input 2 :
// 2
// A+B-C
// D+E/F-G
// Output 2 :
// Postfix expression 1: AB+C-
// Postfix expression 2: DEF/+G-
// Input 3 :
// 1
// a*(b+c)/d-e
// Output 3 :
// Postfix expression 1: abc+*d/e-

// You are using GCC
#include <stdio.h>
#include <string.h>

int prec(char c){
    if(c == '^'){
        return 3;
    }
    else if(c == '/' || c == '*'){
        return 2;
    }
    else if(c == '+' || c == '-'){
        return 1;
    }
    else{
        return -1;
    }
}

char check(char c){
    if(c == '^')
        return 'R';
    return 'L';
}


void infixToPostfix(char s[], int n){
    char result[1000];
    int resultIndex = 0;
    char stack[1000];
    int stackIndex = -1;
    int len = strlen(s);
    
    for(int i = 0; i < len; i++){
        char c = s[i];
        
        if((c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9')){
            result[resultIndex++] = c;
        }
        else if(c == '('){
            stack[++stackIndex] = c;
        }
        else if(c == ')'){
            while(stackIndex>=0 && stack[stackIndex] != '('){
                result[resultIndex++] = stack[stackIndex--];
            }
            stackIndex--;
        }
        else{
            while(stackIndex>=0 && (prec(s[i])<prec(stack[stackIndex]) || 
            prec(s[i]) == prec(stack[stackIndex]) && check(s[i]) == 'L')){
                result[resultIndex++] = stack[stackIndex--];
            }
            stack[++stackIndex] = c;
        }
    }
    
    while(stackIndex>=0){
        result[resultIndex++] = stack[stackIndex--];
    }
    result[resultIndex] = '\0';
 
    printf("Postfix expression %d: %s\n",n, result);
    
}


int main(){
    int n;
    scanf("%d", &n);
    getchar();
    for(int i = 0 ; i < n ; i++){
        char str[1000];
        fgets(str,1000,stdin);
        size_t len = strlen(str);
        if(len>0 && str[len-1] == '\n'){
            str[len-1] = '\0';
        }
        infixToPostfix(str, i+1);
    }
    
    return 0;
}
