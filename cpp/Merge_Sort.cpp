#include <iostream>
#include <vector>
using namespace std;


void merge(vector<int>&arr, int left, int mid, int right){
  int n1 = mid-left+1;
  int n2 = right - mid;
  
  vector<int>L(n1);
  vector<int>R(n2);
  
  for(int i = 0 ; i < n1 ; i++){
    L[i] = arr[left + i];
  }
  
  for(int j = 0 ; j < n2 ; j++){
    R[j] = arr[mid + 1 + j];
  }
  
  int i,j,k = left;
  while(i<n1 && j<n2){
    if(L[i]<R[j]){
      arr[k++] = L[i++];
    }
    else{
      arr[k++] = R[j++];
    }
  }
  
  while(i<n1){
    arr[k++] = L[i++];
  }
  while(j<n2){
    arr[k++] = R[j++];
  }
}

void mergesort(vector <int>&arr, int left, int right){
  if(left >= right){
    return;
  }
  int mid = left + (right - left)/2;
  mergesort(arr, left, mid);
  mergesort(arr, mid+1, right);
  merge(arr, left, mid, right);
}

int main() 
{
  std::vector<int>arr;
  int num;
  while(std::cin >> num){
    arr.push_back(num);
  }
  int n = arr.size();
  mergesort(arr,0,n-1);
  
  for(int val : arr){
    std::cout << val <<" ";
  }
}
