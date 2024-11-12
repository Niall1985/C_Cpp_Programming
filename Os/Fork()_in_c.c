#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>

void calc_square(int start, int end) {
    for(int i = start; i <= end; i++) {
        int sqrt_i = (int)sqrt(i);
        int sqr = sqrt_i * sqrt_i;
        if(sqr == i) {
            printf("%d ", i);
            fflush(stdout); 
        }
    }
    printf("\n"); 
}

int main(){
  pid_t p1, p2;
  p1 = fork();
  if(p1 == 0){
    printf("hehe\n", getpid);
    calc_square(1,25);
    _exit(0);
  }
  else if(p1<0){
    printf("Error");
    return 1;
  }
  
p2 = fork();
  if(p2 == 0){
    printf("hehe\n", getpid);
    calc_square(30,100);
    _exit(0);
  }
  else if(p2<0){
    printf("Error");
    return 1;
  }
  
waitpid(p1,NULL,0);
waitpid(p2,NULL,0);
printf("\n");
printf("Parent process (PID: %d) - Both child processes have finished.\n", getpid());

return 0;
}
