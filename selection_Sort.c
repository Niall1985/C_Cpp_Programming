#include <stdio.h>

void ss(int arr[], int n){
  int i,j,temp,minIndex;
  for(int i=0;i<n-1;i++){
    minIndex = i;
    for(int j=i+1;j<n;j++){
      if(arr[j] < arr[minIndex]){
        minIndex = j;
      }
    }
    
    if(minIndex != i){
      temp = arr[i];
      arr[i] = arr[minIndex];
      arr[minIndex] = temp;
    }
  }
}
int main()
{
    int n;
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++){
      scanf("%d",&arr[i]);
    }
    ss(arr, n);
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
}
