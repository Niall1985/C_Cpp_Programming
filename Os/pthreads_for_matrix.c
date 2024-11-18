#include <stdio.h>
#include <pthread.h>

#define rows 3
#define columns 3
int matrix1[rows][columns];
int matrix2[rows][columns];

void *matrixSum(void *arg){
  pthread_t pid = pthread_self();
  printf("PID for thread 1: %lu\n", pid);
  int result[rows][columns];
  for(int i = 0 ; i < rows ; i++){
    for(int j = 0 ; j < columns ; j++){
      result[i][j] = matrix1[i][j] + matrix2[i][j];
    }
  }
  printf("Matrix Addition: \n");
  for(int i = 0 ; i < rows ; i++){
    for(int j = 0 ; j < columns ; j++){
      printf("%d ", result[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  pthread_exit(NULL);
}

void *matrixSub(void *arg){
  pthread_t pid = pthread_self();
  printf("PID for thread 2: %lu\n", pid);
  int result[rows][columns];
  for(int i = 0 ; i < rows ; i++){
    for(int j = 0 ; j < columns ; j++){
      result[i][j] = matrix1[i][j] - matrix2[i][j];
    }
  }
  printf("Matrix Subtraction: \n");
  for(int i = 0 ; i < rows ; i++){
    for(int j = 0 ; j < columns ; j++){
      printf("%d ", result[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  pthread_exit(NULL);
}

void *matrixMult(void *arg){
  pthread_t pid = pthread_self();
  printf("PID for thread 3: %lu\n", pid);
  int result[rows][columns];
  for(int i = 0 ; i < rows ; i++){
    for(int j = 0 ; j < columns ; j++){
      result[i][j] = 0;
    }
  }
  
  for(int i = 0 ; i < rows ; i++){
    for(int j = 0 ; j < columns ; j++){
      for(int k = 0 ; k < rows ; k++){
        result[i][j] += matrix1[i][k] * matrix2[k][j];
      }
    }
  }
  printf("Matrix Multiplication: \n");
  for(int i = 0 ; i < rows ; i++){
    for(int j = 0 ; j < columns ; j++){
      printf("%d ", result[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  pthread_exit(NULL);
}


int main(){
  for(int i = 0 ; i < rows ; i++){
    for(int j = 0 ; j < columns ; j++){
      scanf("%d", &matrix1[i][j]);
  }
}
  
   for(int i = 0 ; i < rows ; i++){
    for(int j = 0 ; j < columns ; j++){
      scanf("%d", &matrix2[i][j]);
  }
}
  
  pthread_t thread1, thread2, thread3;
  
  pthread_create(&thread1, NULL, matrixSum, NULL);
  pthread_create(&thread2, NULL, matrixSub, NULL);
  pthread_create(&thread3, NULL, matrixMult, NULL);
  
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);
}
