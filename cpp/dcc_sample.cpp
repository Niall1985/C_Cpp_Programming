#include <iostream>
#include <vector>
using namespace std;

int findMax(vector <int>&arr, int low, int high){
  if(low>=high){
    return 0;
  }
  
  int mid = low + (high-low)/2;
  int leftmax = findMax(arr, low, mid);
  int rightMax = findMax(arr, mid+1, high);
  return max(leftmax, rightMax);
}

int main(){
  vector <int> arr = {1,2,3,4,5};
  int n = arr.size();
  
  int res = findMax(arr, 0, n-1);
  cout<<res;
}
