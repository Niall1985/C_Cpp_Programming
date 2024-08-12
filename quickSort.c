#include <stdio.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;

  
}

int partition(int arr[], int lb, int ub){
  int pivot = arr[lb];
  int start = lb;
  int end = ub;
  while(start<end){
    while(arr[start]<=pivot && start < end){
      start++;
    }
    while(arr[end]>pivot){
      end--;
    }
    if(start<end){
      swap(&arr[start], &arr[end]);
    }
    
  }
    swap(&arr[lb], &arr[end]);
    return end;
}

void quicksort(int arr[], int lb, int ub){
  if(ub>lb){
    int loc = partition(arr, lb, ub);
    quicksort(arr,lb,loc-1);
    quicksort(arr,loc+1,ub);
  }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
int main()
{
    int arr[] = {10, 7, 8, 9, 1, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, size);

    quicksort(arr, 0, size - 1);

    printf("Sorted array:\n");
    printArray(arr, size);

    return 0;
}
