//Find the transpose of a matrix and reverse each row of the transposed matrix


#include <stdio.h>
int main()
{
    int n;
    scanf("%d",&n);
    int m[n][n];
    int t[n][n];
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        scanf("%d",&m[i][j]);
      }
    }
    
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        t[j][i] = m[i][j];
      }
    }
    
    printf("Original Matrix:\n");
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        printf("%d ",m[i][j]);
      }
      printf("\n");
    }
    printf("\n");
    
    printf("Transposed Matrix:\n");
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        printf("%d ",t[i][j]);
      }
      printf("\n");
    }
    printf("\n");
    
    for(int i=0;i<n;i++){
      int start = 0;
      int end = n-1;
      while(start<end){
        int temp = t[i][start];
        t[i][start] = t[i][end];
        t[i][end] = temp;
        start++;
        end--;
      }
      
    }
    
    printf("Transposed Matrix with rows flipped\n");
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        printf("%d ",t[i][j]);
      }
      printf("\n");
    }   
}



// Output:

// Original Matrix:
// 1 2 3 
// 4 5 6 
// 7 8 9 

// Transposed Matrix:
// 1 4 7 
// 2 5 8 
// 3 6 9 

// Transposed Matrix with rows flipped
// 7 4 1 
// 8 5 2 
// 9 6 3 
