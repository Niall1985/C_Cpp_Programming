#include <stdio.h>
#include <stdbool.h>

void firstfit(int process, int n, int partitions[]){
  int index = 0;
  bool flag = false;
  int original[n];
  for(int i = 0 ; i < n ; i++){
    original[i] = partitions[i];
  }
  for(int i = 0 ; i < n ; i++){
    if(process<partitions[i]){
      index = i;
      flag = true;
      break;
    }
  }  
  if(flag){
    printf("%dkb is put in %dkb partition\n", process, original[index]);
    partitions[index] = partitions[index] - process;
  }
  else{
    printf("%dkb has to wait\n", process);
  }
}


void worstfit(int process, int n, int partitions[]){
  int index = 0;
  bool flag = false;
  int original[n];
  for(int i = 0 ; i < n ; i++){
    original[i] = partitions[i];
  }
  int max = -1;
  for(int i = 0 ; i < n ; i++){
    if(partitions[i]>max){
      max = partitions[i];
      if(process<max){
      flag = true;
      index = i;
      }
    }
  }

  if(flag){
    printf("%dkb is put in %dkb partition\n", process, original[index]);
    partitions[index] -= process;
  }
  else{
    printf("%dkb has to wait\n", process);
  }
}


void bestfit(int process, int n, int partitions[]){
  int index = 0;
  bool flag = false;
  int original[n];
  for(int i = 0 ; i < n ; i++){
    original[i] = partitions[i];
  }
  int min = 10000000000;
  for(int i = 0 ; i < n ; i++){
    if(partitions[i]>process && partitions[i]<min){
      min = partitions[i];
      flag = true;
      index = i;
        }
  }

  if(flag){
    printf("%dkb is put in %dkb partition\n", process, original[index]);
    partitions[index] -= process;
  }
  else{
    printf("%dkb has to wait\n", process);
  }
}

int main(){
  int n; //number of partitions;
  int m; //numbet of processes;
  scanf("%d %d", &n, &m);
  int partitions[n];
  for(int i = 0 ; i < n ; i++){
    scanf("%d", &partitions[i]);
  }
  int choice;
  scanf("%d", &choice);
  
  for(int i = 0 ; i < m ; i++){
    int process;
    scanf("%d", &process);
    if(choice == 1){
      firstfit(process, n, partitions);
    }
    else if(choice == 2){
      worstfit(process, n, partitions);
    }
    else if(choice == 3){
      bestfit(process, n, partitions);
    }
  }
}
