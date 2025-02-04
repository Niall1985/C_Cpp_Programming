#include <iostream>
#include <vector>

using namespace std;

int rodcut(int i, vector <int>&price){
  if(i == 0){
    return 0;
  }
  int ans = 0;
  for(int j = 1 ; j <= i ; j++){
    ans = max(ans, price[j-1]+rodcut(i-j, price));
  }
  
  return ans;
}

int cutrod(vector<int>&price){
  int n = price.size();
  return rodcut(n, price);
}

int main() {
  vector<int> price =  { 1, 5, 8, 9, 10, 17, 17, 20};
  cout << cutrod(price);
  return 0;
}
