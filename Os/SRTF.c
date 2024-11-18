#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    scanf("%d", &n);
    int pid[n];
    int arrivalTime[n], burstTime[n], remainingTime[n];
    int waitingTime[n], turnaroundTime[n];
    int completed = 0, currentTime = 0;
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
[
    // Input arrival and burst times]
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d",&pid[i], &arrivalTime[i], &burstTime[i]);
        remainingTime[i] = burstTime[i]; // Initialize remaining times
    }

    // Process scheduling loop
    while (completed != n) {
        int shortest = -1;
        int minRemaining = INT_MAX;

        // Find the process with the shortest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (arrivalTime[i] <= currentTime && remainingTime[i] > 0 && remainingTime[i] < minRemaining) {
                minRemaining = remainingTime[i];
                shortest = i;
            }
        }

        // If no process is ready, increment time
        if (shortest == -1) {
            currentTime++;
            continue;
        }

        // Process the shortest remaining time process
        remainingTime[shortest]--;
        currentTime++;

        // If the process is completed
        if (remainingTime[shortest] == 0) {
            completed++;
            int finishTime = currentTime;
            waitingTime[shortest] = finishTime - burstTime[shortest] - arrivalTime[shortest];
            turnaroundTime[shortest] = finishTime - arrivalTime[shortest];
            totalWaitingTime += waitingTime[shortest];
            totalTurnaroundTime += turnaroundTime[shortest];
        }
    }

    // Print results
    printf("Process\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", pid[i], arrivalTime[i], burstTime[i], waitingTime[i], turnaroundTime[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);

    return 0;
}
