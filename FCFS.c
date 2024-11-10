//follow thsi code for fcfs

#include <stdio.h>

int main(){
  int n;
  scanf("%d", &n); //number of processes
  int p[n];
  int at[n];
  int bt[n];
  int ct[n];
  int tat[n];
  int wt[n];
  for(int i = 0 ; i < n  ; i++){
    scanf("%d %d %d", &p[i], &at[i], &bt[i]);
  }
  
  int btc = 0;
  for(int i = 0 ; i < n ; i++){
    for(int j = i+1 ; j < n ; j++){
      if(at[i] > at[j] || (at[i] == at[j] && p[i] > p[j])){
        int temp = at[i];
        at[i] = at[j];
        at[j] = temp;
        
        int temp1 = bt[i];
        bt[i] = bt[j];
        bt[j] = temp1;
        
        int temp2 = p[i];
        p[i] = p[j];
        p[j] = temp2;
        
      }
    }
    btc += bt[i];
    ct[i] = btc;
    tat[i] = ct[i] - at[i];
    wt[i] = tat[i] - bt[i];
  
  }
  
  printf("P AT BT CT TAT WT\n");
  for(int i = 0 ; i < n  ; i++){
    printf("%d %d %d %d %d %d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
  }
  
  // printf("%d", btc);
}




// 5
// 2 0 2
// 1 0 3
// 3 2 6
// 4 3 5
// 5 4 4

// P AT BT CT TAT WT
// 1 0 3 3 3 0
// 2 0 2 5 5 3
// 3 2 6 11 9 3
// 4 3 5 16 13 8
// 5 4 4 20 16 12
