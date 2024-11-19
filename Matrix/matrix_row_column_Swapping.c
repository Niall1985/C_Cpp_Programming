#include <stdio.h>

int main(){
  int n;
  scanf("%d", &n);
  int mat[n][n];
  for(int i = 0 ; i < n ; i++){
    for(int j = 0 ; j < n ; j++){
      scanf("%d", &mat[i][j]);
    }
  }
  printf("Original matrix\n");
  for(int i = 0 ; i < n ; i++){
    for(int j = 0 ; j < n ; j++){
      printf("%d ", mat[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  
  int index1, index2;
  scanf("%d %d", &index1, &index2);
  for(int i = 0 ; i < n ; i++){
    int temp = mat[index1][i];
    mat[index1][i] = mat[index2][i];
    mat[index2][i] = temp;
  }
  printf("Modifed rows\n");
  for(int i = 0 ; i < n ; i++){
    for(int j = 0 ; j < n ; j++){
      printf("%d ", mat[i][j]);
    }
    printf("\n");
  }
printf("\n");
 for(int i = 0 ; i < n ; i++){
    int temp = mat[i][index1];
    mat[i][index1] = mat[i][index2];
    mat[i][index2] = temp;
  }
  printf("Modifed cols\n");
  for(int i = 0 ; i < n ; i++){
    for(int j = 0 ; j < n ; j++){
      printf("%d ", mat[i][j]);
    }
    printf("\n");
  }


}
