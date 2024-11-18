#include <stdio.h>

int main(){
  
  int pages[] = {4, 1, 2, 4, 5};
  int page_size = sizeof(pages)/sizeof(pages[0]);
  int frame_size = 3;
  int frames[frame_size];
  int time1[frame_size];
  int pagefault = 0;
  
  for(int i = 0 ; i < frame_size ; i++){
    frames[i] = -1;
    time1[i] = 0;
  }
  printf("Incomig\t\tFrame 1\t\tFrame 2\t\tFrame 3\n");
  for(int i = 0 ; i < page_size ; i++){
    int found = 0;
    for(int j = 0 ; j < frame_size ; j++){
      if(frames[j] == pages[i]){
        found = 1;
        time1[j] = i;
        break;
      }
    }
    if(!found){
      int lru_index = 0;
      for(int j = 1 ; j < frame_size ; j++){
        if(time1[j] < time1[lru_index]){
          lru_index = j;
        }
      }
      frames[lru_index] = pages[i];
      time1[lru_index] = i;
      pagefault++;
    }
    printf("%d\t\t", pages[i]);
    for(int j = 0 ; j < frame_size ; j++){
      if(frames[j] != -1){
        printf("%d\t\t", frames[j]);
      }
      else{
        printf("-\t\t");
      }
    }
    printf("\n");
  }
    printf("Page Fault: %d", pagefault);
}


/*
Algorithm:
1. Create an array containing all the page requests and get the size of the array
2. Create an array of frames based on the size required
3. Create a variable which counts the page count and set it to zero
4. Create a time array with the same size as the frame array to keep track of the access time 
5. Run a loop to initialize all the frames in the frame array to -1 and all slots in the time array to 0
6. run a loop and iterate over all the page requests
7. Set a flag and initialize it to 0
8. Run another loop and iterate over the frames
9. If we find a hit (req in the page list is in a frame), set the flag to 1 , set the value of i to the time array for the particular request and break n exit the inner loop;
10. If the flag is not set, we create a var to track the index of the lru element and set it to 0 as of now.
11. The we run a loop over all the frames and check if the time[j] < time[lru_time]
12. If yes, then we set the value of j to the lru_index
13. Then we put the incoming page request at the lru index in the frame, set the time[lru_index] to i and increment the pade fault count
*/
