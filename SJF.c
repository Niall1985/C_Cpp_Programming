// #include <stdio.h>
// #include <limits.h>

// int main() {
//     int n;
//     scanf("%d", &n); // Number of processes

//     int p[n], at[n], bt[n], ct[n], tat[n], wt[n], completed[n];
//     for(int i = 0; i < n; i++) {
//         scanf("%d %d %d", &p[i], &at[i], &bt[i]);
//         completed[i] = 0; // Mark all processes as not completed initially
//     }

//     int btc = 0, completed_count = 0;

//     // Sort processes by arrival time and process ID as a tie-breaker
//     for(int i = 0; i < n; i++) {
//         for(int j = i + 1; j < n; j++) {
//             if(at[i] > at[j] || (at[i] == at[j] && p[i] > p[j])) {
//                 // Swap arrival times
//                 int temp = at[i];
//                 at[i] = at[j];
//                 at[j] = temp;

//                 // Swap burst times
//                 int temp1 = bt[i];
//                 bt[i] = bt[j];
//                 bt[j] = temp1;

//                 // Swap process IDs
//                 int temp2 = p[i];
//                 p[i] = p[j];
//                 p[j] = temp2;
//             }
//         }
//     }

//     // Process scheduling based on SJF
//     while(completed_count < n) {
//         int idx = -1;
//         int min_bt = INT_MAX;

//         // Select the process with the shortest burst time among arrived and uncompleted processes
//         for(int i = 0; i < n; i++) {
//             if(completed[i] == 0 && at[i] <= btc) {
//                 if(bt[i] < min_bt || (bt[i] == min_bt && p[i] < p[idx])) {
//                     min_bt = bt[i];
//                     idx = i;
//                 }
//             }
//         }

//         if(idx == -1) {
//             // No process is available, increment current time
//             btc++;
//         } else {
//             // Process found, execute it
//             btc += bt[idx];
//             ct[idx] = btc; // Completion time
//             tat[idx] = ct[idx] - at[idx]; // Turnaround time
//             wt[idx] = tat[idx] - bt[idx]; // Waiting time
//             completed[idx] = 1; // Mark as completed
//             completed_count++;
//         }
//     }

//     // Display the results
//     printf("P\tAT\tBT\tCT\tTAT\tWT\n");
//     for(int i = 0; i < n; i++) {
//         printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
//     }

//     return 0;
// }



#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    scanf("%d", &n); // Number of processes

    int p[n], at[n], bt[n], ct[n], tat[n], wt[n], completed[n];
    for(int i = 0; i < n; i++) {
        scanf("%d %d %d", &p[i], &at[i], &bt[i]);
        completed[i] = 0; // Mark all processes as incomplete initially
    }

    int btc = 0, completed_count = 0;

    while (completed_count < n) {
        int idx = -1;
        int min_bt = INT_MAX;

        // Select the process with the shortest burst time among arrived and uncompleted processes
        for (int i = 0; i < n; i++) {
            if (completed[i] == 0 && at[i] <= btc) { // Process is available and incomplete
                if (bt[i] < min_bt || (bt[i] == min_bt && at[i] < at[idx])) {
                    min_bt = bt[i];
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            // No process is available, increment current time
            btc++;
        } else {
            // Execute the process
            btc += bt[idx];
            ct[idx] = btc;           // Completion time
            tat[idx] = ct[idx] - at[idx]; // Turnaround time
            wt[idx] = tat[idx] - bt[idx]; // Waiting time
            completed[idx] = 1;      // Mark as completed
            completed_count++;
        }
    }

    // Display the results
    printf("P\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    return 0;
}
