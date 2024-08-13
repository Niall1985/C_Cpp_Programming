#include <stdio.h>

int Binary(int arr[], int left, int right, int target){
  
  while(left<right){
    
    int mid = left + (right-left)/2;
    if(arr[mid] == target){
      return mid;
    }
    else if(target>arr[mid]){
      left = mid+1;
    }
    else{
      right = mid-1;
    }
  }
  
return -1;
  
}

int main()
{
    int arr[8] = {25,30,35,40,45,50,55,60};
    int target = 50;
    int res = Binary(arr,0,7,target);
    if(res == -1){
      printf("Error");
    }
    else{
      printf("Index: %d",res);
    }
}
