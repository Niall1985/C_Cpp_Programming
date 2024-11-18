#include <stdio.h>

int main() {
    int pages[] = {4, 1, 2, 4, 5};
    int page_size = sizeof(pages) / sizeof(pages[0]);
    int frame_size = 3;
    int frames[frame_size];
    int pagefault = 0;

    // Initialize frames with -1 to indicate they are empty
    for (int i = 0; i < frame_size; i++) {
        frames[i] = -1;
    }

    printf("Incoming\tFrame 1\t\tFrame 2\t\tFrame 3\n");

    for (int i = 0; i < page_size; i++) {
        int found = 0;

        // Check if the page is already in the frame
        for (int j = 0; j < frame_size; j++) {
            if (frames[j] == pages[i]) {
                found = 1;  // Page is already in one of the frames
                break;
            }
        }

        if (!found) {
            int replace_index = -1;
            int farthest = -1;

            // Find the page to replace (optimal replacement)
            for (int j = 0; j < frame_size; j++) {
                int next_use = -1;

                // Find when the current frame will be used next in the future
                for (int k = i + 1; k < page_size; k++) {
                    if (frames[j] == pages[k]) {
                        next_use = k;
                        break;
                    }
                }

                // If the page is not found again in the future, it is the optimal candidate to replace
                if (next_use == -1) {
                    replace_index = j;
                    break;
                }

                // Track the farthest next usage
                if (next_use > farthest) {
                    farthest = next_use;
                    replace_index = j;
                }
            }

            // Replace the page at the selected frame
            frames[replace_index] = pages[i];
            pagefault++;
        }

        // Print the current state of frames
        printf("%d\t\t", pages[i]);
        for (int j = 0; j < frame_size; j++) {
            if (frames[j] != -1) {
                printf("%d\t\t", frames[j]);
            } else {
                printf("-\t\t");
            }
        }
        printf("\n");
    }

    printf("Page Faults: %d\n", pagefault);
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
9. If the flag is not set, we create two vars int replaced_index (to track the index to be replaced) and int farthest (to track the farthest element) and set their values to -1
10. Run a loop from 0 to frame_size and we initialize a variable to track the index of when an element in the frame will occur next in the paging sequence
11. Run a loop from i+1 to page_size and iterate over all the elements, if we find an element that is in the frame and in the request sequnce, we set the next_use variable with the index of the found value and we break
12. If we don't find such an element, we set the replaced_index value to the current frame index and we break
13. If we do find a value(we will check if the next_uze val is greater than furthest), if yes then we will set farthest with next_use and replaced_index to the current frame index
14. The we will fill the page in the frame usinf frame[replaced_index] = page[i] and we will increment the page fault counter
*/
