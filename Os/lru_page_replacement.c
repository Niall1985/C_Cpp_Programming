#include <stdio.h>

int main() {
    int frames[20], reference[50], pageFaults = 0;
    int frameCount, referenceCount;

    // Input number of pages and reference string
    printf("Enter number of pages: ");
    scanf("%d", &referenceCount);
    printf("Enter the reference string: ");
    for (int i = 0; i < referenceCount; i++)
        scanf("%d", &reference[i]);

    // Input number of frames
    printf("Enter number of frames: ");
    scanf("%d", &frameCount);

    // Initialize frames to -1 (indicating empty)
    for (int i = 0; i < frameCount; i++)
        frames[i] = -1;

    // Process each page in the reference string
    for (int i = 0; i < referenceCount; i++) {
        int page = reference[i], found = 0;

        // Check if the page is already in the frame
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        // If page is not found, handle the page fault
        if (!found) {
            pageFaults++;

            // Find the least recently used page to replace if frames are full
            int replaceIndex = 0, leastRecent = i;
            for (int j = 0; j < frameCount; j++) {
                int lastUsed = -1;
                for (int k = i - 1; k >= 0; k--) {
                    if (reference[k] == frames[j]) {
                        lastUsed = k;
                        break;
                    }
                }
                if (lastUsed < leastRecent) {
                    leastRecent = lastUsed;
                    replaceIndex = j;
                }
            }
            frames[replaceIndex] = page;

            // Print the frame's current state
            printf("\n");
            for (int j = 0; j < frameCount; j++)
                printf("%d\t", frames[j] != -1 ? frames[j] : -1);
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
    return 0;
}
