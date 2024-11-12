#include <stdio.h>
int main(){
  
  int m,n;
  scanf("%d %d", &m, &n);
  int matrix1[m][n];
  int matrix2[m][n];
  int matrix[m][n];
  
  for(int i=0;i<m;i++){
    for(int j=0;j<n;j++){
      scanf("%d", &matrix1[i][j]);
    }
  }
  
    for(int i=0;i<m;i++){
      for(int j=0;j<n;j++){
        scanf("%d", &matrix2[i][j]);
    }
  }
  
    for(int i=0;i<m;i++){
      for(int j=0;j<n;j++){
        matrix[i][j] = matrix1[i][j] + matrix2[i][j];
    }
  }
  
    for(int i=0;i<m;i++){
      for(int j=0;j<n;j++){
        printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
  
}


