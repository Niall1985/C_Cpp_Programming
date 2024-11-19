#include <stdio.h>

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    int arrivalTime[n], burstTime[n], remainingTime[n];
    int waitingTime[n], turnaroundTime[n];
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    // Input arrival and burst times
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &arrivalTime[i], &burstTime[i]);
        remainingTime[i] = burstTime[i]; // Initialize remaining times
    }

    int currentTime = 0;
    int completed = 0;

    // Loop until all processes are completed
    while (completed != n) {
        int idle = 1; // Check if no process is ready to run in this cycle

        for (int i = 0; i < n; i++) {
            if (remainingTime[i] > 0 && arrivalTime[i] <= currentTime) {
                idle = 0; // At least one process is ready
                if (remainingTime[i] > quantum) {
                    // Process can only use part of its burst time (quantum)
                    currentTime += quantum;
                    remainingTime[i] -= quantum;
                } else {
                    // Process completes its execution
                    currentTime += remainingTime[i];
                    waitingTime[i] = currentTime - burstTime[i] - arrivalTime[i];
                    turnaroundTime[i] = currentTime - arrivalTime[i];
                    remainingTime[i] = 0;
                    completed++;
                    totalWaitingTime += waitingTime[i];
                    totalTurnaroundTime += turnaroundTime[i];
                }
            }
        }
        // If no process is ready, increment time to avoid infinite loop
        if (idle) currentTime++;
    }

    // Print results
    printf("Process\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", i + 1, arrivalTime[i], burstTime[i], waitingTime[i], turnaroundTime[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);

    return 0;
}
