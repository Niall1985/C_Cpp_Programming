#include <stdio.h>

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arrivalTime[n], burstTime[n], priority[n];
    int remainingTime[n], waitingTime[n], turnaroundTime[n];
    int completed = 0, currentTime = 0, minPriority = 9999, shortest = -1;
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    int isCompleted[n];

    // Input process details and initialize remaining time
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &arrivalTime[i], &burstTime[i], &priority[i]);
        remainingTime[i] = burstTime[i];  // Remaining time initially is burst time
        isCompleted[i] = 0;  // Initialize as not completed
    }

    printf("\nProcess\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");

    // Preemptive Priority Scheduling loop
    while (completed < n) {
        minPriority = 9999;  // Reset to find highest priority available
        shortest = -1;

        // Find the highest priority process that has arrived and is not completed
        for (int i = 0; i < n; i++) {
            if (arrivalTime[i] <= currentTime && !isCompleted[i] && priority[i] < minPriority) {
                minPriority = priority[i];
                shortest = i;
            }
        }

        // If no process is found, increment the current time and continue
        if (shortest == -1) {
            currentTime++;
            continue;
        }

        // Execute the process for one unit of time
        remainingTime[shortest]--;
        currentTime++;

        // If the process is completed
        if (remainingTime[shortest] == 0) {
            isCompleted[shortest] = 1;  // Mark as completed
            completed++;
            int finishTime = currentTime;
            waitingTime[shortest] = finishTime - arrivalTime[shortest] - burstTime[shortest];
            turnaroundTime[shortest] = waitingTime[shortest] + burstTime[shortest];
            totalWaitingTime += waitingTime[shortest];
            totalTurnaroundTime += turnaroundTime[shortest];

            // Print process information after completion
            printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", shortest + 1, arrivalTime[shortest], burstTime[shortest], priority[shortest], waitingTime[shortest], turnaroundTime[shortest]);
        }
    }

    // Calculate and print average waiting and turnaround times
    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);

    return 0;
}
