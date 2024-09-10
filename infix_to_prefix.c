#include<stdio.h>
#include<string.h>
#include<ctype.h>

void strrev(char s[]){
  int n = strlen(s);
  int start = 0;
  int end = n-1;
  while(start<end){
    char temp = s[start];
    s[start] = s[end];
    s[end] = temp;
    start++;
    end--;
  }
  
  for(int i = 0 ; i < n ; i++){
    if(s[i] == '('){
      s[i] =')';
    }
    else if(s[i] == ')'){
      s[i] = '(';
    }
  }
}


int prec(char c){
  if(c == '^'){
    return 3;
  }
  else if(c == '/' || c == '*'){
    return 2;
  }
  else if(c == '-' || c == '+'){
    return 1;
  }
  else{
    return -1;
  }
}


char check(char c){
  if(c == '^'){
    return 'R';
  }
  return 'L';
}



void InfixToPostfix(char s[]){
  char result[1000];
  int resultIndex = 0;
  char stack[1000];
  int stackIndex = -1;
  int n = strlen(s);
  
  for(int i=0;i<n;i++){
    char c = s[i];
    
    if(isalnum(c)){
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
    while(stackIndex >= 0 && (prec(s[i])<prec(stack[stackIndex]) || prec(s[i]) == prec(stack[stackIndex]) && check(s[i]) == 'L')){
      result[resultIndex++] = stack[stackIndex--];
    }
    stack[++stackIndex] = c;
  }
  }
  
  while(stackIndex>=0){
    result[resultIndex++] = stack[stackIndex--];
  }
  
  result[resultIndex] = '\0';
  strrev(result);
  printf("%s\n",result);
}

int main(){
  char temp[1000];
  scanf("%[^\n]s", temp);
  strrev(temp);
  printf("%s", temp);
  printf("\n");
  InfixToPostfix(temp);
  printf("\n");

}
