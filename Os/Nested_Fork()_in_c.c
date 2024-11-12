#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void task1(int arr[], int n){
  int sum = 0;
  for(int i=0;i<n;i++){
    sum += i;
  }
  
  printf("The sum of the array elements is: %d\n",sum);
  fflush(stdout);
}

void task2(int arr[], int n){
  for(int i=0;i<n;i++){
    for(int j=i+1;j<n;j++){
      if(arr[i]>arr[j]){
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
  
  printf("Sorted Array\n");
  for(int i=0;i<n;i++){
    printf("%d ",arr[i]);
  }
  printf("\n");
  fflush(stdout);
}


int main(){
  pid_t p1, p2;
  int n = 5;
  int arr[5] = {1,5,3,2,4};
  p1 = fork();
  
  if(p1 == 0){
    task1(arr,n);
    
    p2 = fork();
    if(p2 == 0){
      task2(arr,n);
      _exit(0);
    }
    else if(p2<0){
      printf("Error\n");
      _exit(1);
    }
    waitpid(p2,NULL,0);
    _exit(0);
  }
  else if(p1<0){
    printf("Error\n");
    return 1;
  }
  
  waitpid(p1, NULL, 0);

  printf("Parent process (PID: %d) - All child processes have finished.\n", getpid());
  fflush(stdout);

  return 0;
}
