#include <stdio.h>

void insertionsort(int arr[], int n){
  for(int i=1;i<n;i++){ //start the loop from index 1 of the array
    int temp = arr[i]; //set temp an element of the array
    int j = i-1; //arr[0]
    while(j>=0 && arr[j]>temp){
      arr[j+1] = arr[j];
      j--;
    }
    arr[j+1] = temp;
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
       insertionsort(arr,n);
     }

// Output:

// Unsorted array
// 1 4 2 5 3 
// Sorted array
// 1 2 3 4
