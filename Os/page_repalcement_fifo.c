#include <stdio.h>

int main() {
    int incomingStream[] = {4, 1, 2, 4, 5};
    int pageFaults = 0, frames = 3, pages;
    pages = sizeof(incomingStream) / sizeof(incomingStream[0]);

    int temp[frames];
    for (int i = 0; i < frames; i++) temp[i] = -1;

    printf("Incoming\tFrame 1\t\tFrame 2\t\tFrame 3\n");

    for (int i = 0; i < pages; i++) {
        int found = 0;
        
        // Check if the page is already in a frame
        for (int j = 0; j < frames; j++) {
            if (temp[j] == incomingStream[i]) {
                found = 1;
                break;
            }
        }
        
        // If page is not found, it's a page fault
        if (!found) {
            temp[pageFaults % frames] = incomingStream[i];
            pageFaults++;
        }

        printf("%d\t\t", incomingStream[i]);
        for (int j = 0; j < frames; j++) {
            if (temp[j] != -1)
                printf("%d\t\t", temp[j]);
            else
                printf("-\t\t");
        }
        printf("\n");
    }

    printf("Total Page Faults:\t%d\n", pageFaults);
    return 0;
}
