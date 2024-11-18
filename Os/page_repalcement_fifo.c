#include <stdio.h>

int main() {
    int incomingStream[] = {4, 1, 2, 4, 5};
    int pageFaults = 0, frames = 3, pages;
    pages = sizeof(incomingStream) / sizeof(incomingStream[0]);

    int temp[frames];
    for (int i = 0; i < frames; i++) temp[i] = -1;C

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




/*
Algorithm:
1. Create an array containing all the page requests and get the size of the array
2. Create an array of frames based on the size required
3. Create a variable which counts the page count and set it to zero
4. Run a loop to initialize all the frames in the frame array to -1
5. run a loop and iterate over all the page requests
6. Set a flag and initialize it to 0
7. Run another loop and iterate over the frames
8. If we find a hit (req in the page list is in a frame), set the flag to 1 and break n exit the inner loop;
9. If the flag is not set, we put the incoming pages in the frame in fifo manner -> frames[pagefault % frame size] = page[i] and then increment the count of the page fault
*/
