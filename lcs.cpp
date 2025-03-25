#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int LCS(string X, string Y, int m, int n){
  if (m == 0 || n == 0){
    return 0;
  }
  if(X[m-1] == Y[n-1]){
    return 1+LCS(X,Y,m-1,n-1);
  }
  else{
    return max(LCS(X,Y,m,n-1), LCS(X,Y,m-1,n));
  }
}
int main(){
  string X;
  string Y;
  cin>>X;
  cin>>Y;
  int m = X.length();
  int n = Y.length();
  cout<<LCS(X,Y,m,n);
  
}
