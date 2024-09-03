#include <stdio.h>

typedef struct Process{
int pid;
int at;
int bt;
int st;
int ct;
int tat;
int wt;
};

void sort_arrival_time(struct Process p[], int n){
for(int i=0;i<n-1;i++){
for(int j=i+1; j<n; j++){
if(p[i].at>p[j].at){
struct Process temp = p[i];
p[i] = p[j];
p[j] = temp;
}
}
}
}
int main(){
int n;
printf("Enter the number of processes: ");
scanf("%d", &n);
struct Process p[n];

for(int i=0;i<n;i++){
p[i].pid = i+1;
scanf("%d %d", &p[i].at, &p[i].bt); 
}

sort_arrival_time(p,n);
int current = 0;
for(int i=0;i<n;i++){
p[i].st = (current > p[i].at)?current:p[i].at;
p[i].ct = p[i].st + p[i].bt;
p[i].tat = p[i].ct - p[i].at;
p[i].wt = p[i].tat - p[i].bt;
current = p[i].ct;
}

float total_tat = 0;
float total_wt = 0;
for(int i=0;i<n;i++){
total_tat += p[i].tat;
total_wt += p[i].wt;
}

float avg_tat = total_tat/4.0;
float avg_wt = total_wt/4.0;
printf("Avg TAT: %.2f\n", avg_tat);
printf("Avg WT: %.2f\n", avg_wt);
for(int i=0;i<n;i++){
printf("P%d ", p[i].pid);
}
printf("\n");
}

//Input
// pid  AT  BT
// P1   1   3
// P2   0   4
// P3   2   2
// P4   1   5

// Output:
// Avg TAT: 8.25
// Avg WT: 4.75
// P2 P1 P4 P3 

