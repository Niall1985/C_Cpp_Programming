#include <stdio.h>

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arrivalTime[n], burstTime[n], priority[n];
    int waitingTime[n], turnaroundTime[n];
    int completionTime = 0;
    int isCompleted[n];
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    // Initialize isCompleted array to 0 (not completed)
    for (int i = 0; i < n; i++) {
        isCompleted[i] = 0;
    }

    // Input arrival time, burst time, and priority for each process
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &arrivalTime[i], &burstTime[i], &priority[i]);
    }

    printf("\nProcess\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");

    // Process scheduling loop
    for (int completed = 0; completed < n; ) {
        int highestPriorityIndex = -1;

        // Find the highest priority process that has arrived and is not completed
        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && arrivalTime[i] <= completionTime) {
                if (highestPriorityIndex == -1 || priority[i] < priority[highestPriorityIndex]) {
                    highestPriorityIndex = i;
                }
            }
        }

        // If no process has arrived, increment time and continue
        if (highestPriorityIndex == -1) {
            completionTime++;
            continue;
        }

        // Process the selected highest-priority process
        int i = highestPriorityIndex;
        waitingTime[i] = completionTime - arrivalTime[i];
        turnaroundTime[i] = waitingTime[i] + burstTime[i];
        completionTime += burstTime[i];
        isCompleted[i] = 1;  // Mark as completed
        completed++;

        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", i + 1, arrivalTime[i], burstTime[i], priority[i], waitingTime[i], turnaroundTime[i]);
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }

    // Calculate and print averages
    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);

    return 0;
}
