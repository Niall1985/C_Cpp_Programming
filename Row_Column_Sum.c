#include <stdio.h>
int main(){
  int R,C;
  scanf("%d %d", &R,&C);
  int m[R][C];
  int r[R];
  int c[C];
  
  for(int i=0;i<R;i++){
    r[i] = 0;
  }
  
  for(int j=0;j<C;j++){
    c[j] = 0;
  }
  
  for(int i=0;i<R;i++){
    for(int j=0;j<C;j++){
      scanf("%d",&m[i][j]);
      r[i] += m[i][j];
      c[j] += m[i][j];
    }
  }
  
  printf("Row sum\n");
  for(int i=0;i<R;i++){
    printf("%d ",r[i]);
  }
  
  printf("\n");
  printf("Column sum\n");
  for(int j=0;j<C;j++){
    printf("%d ",c[j]);
  }
  
  printf("\n");
  printf("Row+Col sum\n");
  int final[R];
  for(int k=0;k<R;k++){
    final[k] = r[k] + c[k];
  }
  
  for(int i=0;i<R;i++){
    printf("Sum of Row %d, Column %d: %d \n",i+1,i+1, final[i]);
  }
}



 
// STDIN
// 4 2
// 1
// 2
// 3
// 4
// 5
// 6
// 7
// 8

// Output:

// Row sum
// 3 7 11 15 
// Column sum
// 16 20 
// Row+Col sum
// Sum of Row 1, Column 1: 19 
// Sum of Row 2, Column 2: 27 
// Sum of Row 3, Column 3: 11 
// Sum of Row 4, Column 4: 15 
