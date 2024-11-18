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
