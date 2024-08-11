#include <stdio.h>

void bubblesort(int arr[], int n){
  for(int i=0;i<n;i++){
    for(int j=i+1; j<n;j++){
      if(arr[i]>arr[j]){
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j]= temp;
      }
    }
  }
  printf("Sorted array\n");
  for(int i=0;i<n;i++){
    printf("%d ",arr[i]);
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
     printf("Unsorted array\n");
     for(int i=0;i<n;i++){
       printf("%d ",arr[i]);
     }
       printf("\n");
       bubblesort(arr,n);
     }



// Output:
// Unsorted array
// 1 4 2 5 3 
// Sorted array
// 1 2 3 4 5 
