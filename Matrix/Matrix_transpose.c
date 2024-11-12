#include <stdio.h>
int main(){
  int R,C;
  scanf("%d %d", &R,&C);
  int m[R][C];
  int t[C][R];
  for(int i=0;i<R;i++){
    for(int j=0;j<C;j++){
      scanf("%d",&m[i][j]);
    }
  }
  
  for(int i=0;i<R;i++){
    for(int j=0; j<C; j++){
      t[j][i] = m[i][j];
    }
  }
  
  for(int i=0;i<C;i++){
    for(int j=0;j<R;j++){
      printf("%d ", t[i][j]);
    }
    printf("\n");
  }
  
}
