code:
#include <stdio.h>
int main(){
  for (int i=5;i>=1;i--){
    for (int j=i;j>=1;j--){
      printf("@");
    }
    printf("\n");
  }
}

output:
// @@@@@
// @@@@
// @@@
// @@
// @

code:
#include <stdio.h>
int main(){
  for (int i=1;i<=5;i++){
    for (int j=1;j<=i;j++){
      printf("@");
    }
    printf("\n");
  }
}

output:
// @
// @@
// @@@
// @@@@
// @@@@@

code:
#include <stdio.h>
int main(){
  for (int i=1;i<=5;i++){
    for (int j=1;j<=i;j++){
      printf("%d",j);
    }
    printf("\n");
  }
}

output:
// 1
// 12
// 123
// 1234
// 12345

code:
#include <stdio.h>
int main(){
  for (int i=5;i>=1;i--){
    for (int j=i;j>=1;j--){
      printf("%d",j);
    }
    printf("\n");
  }
}

output:
// 54321
// 4321
// 321
// 21
// 1

code:
#include <stdio.h>
int main(){
  for (int i=1;i<=5;i++){
    for (int j=1;j<=5;j++){
      if (i+j <= 5){
        printf(" ");
      }
      else{
        printf("@");
      }
    }
    printf("\n");
  } 
}

// output:
//     @
//    @@
//   @@@
//  @@@@
// @@@@@

code:
#include <stdio.h>
void print_pattern(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            printf(" ");
        }
        for (int k = 0; k < n - i; k++) {
            printf("*");
        }
        printf("\n");
    }
}
int main() {
    int n = 5; 
    print_pattern(n);
    return 0;
}

output:
// *****
//  ****
//   ***
//    **
//     *

code:
#include <stdio.h>
int main(){
  for (int i=5;i>=1;i--){
    for (int j=i;j>=1;j--){
      printf("%d",i);
    }
    printf("\n");
  }
}

output:
// 55555
// 4444
// 333
// 22
// 1

code:
#include <stdio.h>
int main(){
  int n=0;
  for(int i=1;i<=5;i++){
    for (int j=1;j<=i;j++){
      n++;
      printf("%d ", n);
    }
    printf("\n");
  }
}

output:
// 1 
// 2 3 
// 4 5 6 
// 7 8 9 10 
// 11 12 13 14 15 

code:
#include <stdio.h>
int main(){
  int n=0;
  for(int i=5;i>=1;i--){
    for (int j=i;j>=1;j--){
      n++;
      printf("%d  ", n);
    }
    printf("\n");
  }
}

output:
// 1  2  3  4  5  
// 6  7  8  9  
// 10  11  12  
// 13  14  
// 15 

code:
#include <stdio.h>
int main(){
  int n=5;
  for (int i=1;i<=n;i++){
    for (int space = 1; space<=(n-i); space++){
      printf(" ");
    }
    for (int j=1;j<=i;j++){
      printf("@ ");
    }
    printf("\n");
  }
}

// output:
//     @ 
//    @ @ 
//   @ @ @ 
//  @ @ @ @ 
// @ @ @ @ @ 

code:
#include <stdio.h>
int main(){
  int n=5;
  for (int i=n;i>=1;i--){
    for (int space = 1; space<=(n-i); space++){
      printf(" ");
    }
    for (int j=5;j>=1;j--){
      printf("@ ");
    }
    printf("\n");
  }
}

output:
@ @ @ @ @ 
 @ @ @ @ @ 
  @ @ @ @ @ 
   @ @ @ @ @ 
    @ @ @ @ @ 

code:
#include <stdio.h>
int main(){
  int n=5;
  for (int i=n;i>=1;i--){
    for (int space = 1; space<=(n-i); space++){
      printf(" ");
    }
    for (int j=1;j<=i;j++){
      printf("@ ");
    }
    printf("\n");
  }
}

Explanation:
// 1. The outer loop (`for (int i = n; i >= 1; i--)`) controls the number of lines to be printed, starting from `n` down to `1`.
// 2. The first inner loop (`for (int space = 1; space <= (n - i); space++)`) prints the appropriate number of leading spaces.
// 3. The second inner loop (`for (int j = 1; j <= i; j++)`) prints the '@' characters. The number of '@' characters decreases with each line.
// 4. `printf("\n")` moves the cursor to the next line after printing the spaces and '@' characters.

output:
// @ @ @ @ @ 
//  @ @ @ @ 
//   @ @ @ 
//    @ @ 
//     @ 
