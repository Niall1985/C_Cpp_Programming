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


/*
Algorithm:
1. Initialize all the elements (Process id, arrival time and burst time)
2. Set remaining time array with the values of burst time
3. Declare a completed var which tracks how many processes have completed their execution
4. Create a current count to track execution time of each process
5. While the number of processes completed is lesser than the total number of processes, run a loop continuously
6. Create a var shortest (to check the process (index) with the shortest burst time) and initialize it to -1
7. Create a minReamining var and set it to infinity
8. Run a loop from 0 to n and check if the arrival time of a process is lesser or equal to the current time value and check if the remaining time value is greater than 0 and lesser than min remaining time
9. If the above conditions are satisfied, set the value of shortest to the index being checked and set the value of minRemaining to remainingTime[i]
10. If shortest == -1, increment the current time and break else decrement the remaining time of the shortest index's element and increment the currentTime.
11. If remaining time of shortest = 0, increment the completed var and set the values for tat, wt and ct
*/
