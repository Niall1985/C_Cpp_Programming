#include <stdio.h>

int main() {
    int no_of_frames, no_of_pages, frames[10], pages[30], future[10], i, j, k, pos, faults = 0;
    printf("Enter number of frames: ");
    scanf("%d", &no_of_frames);
    printf("Enter number of pages: ");
    scanf("%d", &no_of_pages);
    printf("Enter page reference string: ");
    for (i = 0; i < no_of_pages; i++) {
        scanf("%d", &pages[i]);
    }

    // Initialize frames with -1 (indicating empty)
    for (i = 0; i < no_of_frames; i++) {
        frames[i] = -1;
    }

    for (i = 0; i < no_of_pages; i++) {
        int found = 0;
        
        // Check if the current page is already in a frame
        for (j = 0; j < no_of_frames; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        // If page is not found in frames, page fault occurs
        if (!found) {
            faults++;
            int empty_found = 0;

            // Look for an empty frame
            for (j = 0; j < no_of_frames; j++) {
                if (frames[j] == -1) {
                    frames[j] = pages[i];
                    empty_found = 1;
                    break;
                }
            }

            // If no empty frame, find the optimal page to replace
            if (!empty_found) {
                for (j = 0; j < no_of_frames; j++) {
                    future[j] = -1;
                    for (k = i + 1; k < no_of_pages; k++) {
                        if (frames[j] == pages[k]) {
                            future[j] = k;
                            break;
                        }
                    }
                }

                // Find the frame with the farthest future use or not used at all
                pos = 0;
                for (j = 1; j < no_of_frames; j++) {
                    if (future[j] == -1 || (future[pos] != -1 && future[j] > future[pos])) {
                        pos = j;
                    }
                }
                frames[pos] = pages[i];
            }
        }

        // Print the current frame state
        printf("\n");
        for (j = 0; j < no_of_frames; j++) {
            if (frames[j] != -1)
                printf("%d\t", frames[j]);
            else
                printf("-\t");
        }
    }
    printf("\n\nTotal Page Faults = %d\n", faults);
    return 0;
}
