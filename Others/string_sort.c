#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void sort(char **arr, int n){
  char temp[100];
  for(int i=0;i<n;i++){
    for(int j=i+1; j<n;j++){
      if(strcmp(arr[i], arr[j])>0){
        strcpy(temp,arr[i]);
        strcpy(arr[i],arr[j]);
        strcpy(arr[j],temp);
      }
    }
    if(i != n-1){
      printf("After iteration %d: ",i+1);
      for(int i=0;i<n;i++){
        printf("%s ",arr[i]);
      }
      printf("\n");
    }
  }
}
int main()
{
    int n;
    scanf("%d",&n);
    char *arr[n];
    for(int i=0;i<n;i++){
      char buffer[100];
      arr[i] = (char*)malloc(100*sizeof(char));
      scanf("%s", buffer);
      strcpy(arr[i], buffer);
    }
    printf("Original array\n");
    for(int i=0;i<n;i++){
      printf("%s ",arr[i]);
    }
    printf("\n");
    sort(arr,n);
    printf("Sorted array\n");
    for(int i=0;i<n;i++){
      printf("%s ",arr[i]);
    }
    
    for(int i=0;i<n;i++){
      free(arr[i]);
    }
}
