#include <stdio.h>
int main()
{
    int R1,C1,R2,C2;
    scanf("%d %d %d %d", &R1, &C1, &R2, &C2);
    int m1[R1][C1];
    int m2[R2][C2];
    int m3[R1][C2] ;
    for(int i=0; i<R1; i++){
      for(int j=0; j<C1; j++){
        scanf("%d", &m1[i][j]);
      }
    }
    
    for(int i=0; i<R2; i++){
      for(int j=0; j<C2; j++){
        scanf("%d", &m2[i][j]);
      }
    }
    
    for(int i=0; i<R1; i++){
      for(int j=0; j<C2; j++){
        m3[i][j] = 0;
      }
    }
    
    for(int i=0;i<R1;i++){
      for(int j=0;j<C2;j++){
        for(int k=0;k<R2;k++){
          m3[i][j] += m1[i][k] * m2[k][j];
        }
      }
    }
    
    for(int i=0;i<R1;i++){
      for(int j=0;j<C2;j++){
        printf("%d ",m3[i][j]);
      }
      printf("\n");
    }
}
