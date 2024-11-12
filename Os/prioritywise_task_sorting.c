//the objective of this program is to sort the user input of task descriptions and their priorities in the descending order of priority

#include <stdio.h>
#include <stdlib.h>
struct Tasks{
    char description[50];
    int priority;
};
int main()
{
    int n;
    scanf("%d",&n);
    struct Tasks *tasks[n];
    for(int i=0;i<n;i++){
        tasks[i] = (struct Tasks *)malloc(sizeof (struct Tasks));
        scanf("%s",tasks[i]->description);
        scanf("%d",&tasks[i]->priority);
    }  
    printf("Unsorted Output\n");
    for (int i=0;i<n;i++){
        printf("Task Description:%s\n",tasks[i]->description);
        printf("Task Priority:%d\n",tasks[i]->priority);
    }
    //logic to sort tasks in descending order of priority
    for(int i=0;i<n;i++){
      for(int j=i+1;j<n;j++){
        if(tasks[i]->priority<tasks[j]->priority){
          struct Tasks *temp = tasks[i]->priority;
          tasks[i]->priority = tasks[j]->priority;
          tasks[j]->priority = temp;
        }
      }
    }
    //logic to sort tasks in ascending order of priority
    // for(int i=0;i<n;i++){
    //   for(int j=i+1;j<n;j++){
    //     if(tasks[i]->priority>tasks[j]->priority){
    //       struct Tasks *temp = tasks[i]->priority;
    //       tasks[i]->priority = tasks[j]->priority;
    //       tasks[j]->priority = temp;
    //     }
    //   }
    // }
    
    printf("\n");
    printf("Sorted Output\n");
    for (int i=0;i<n;i++){
        printf("Task Description:%s\n",tasks[i]->description);
        printf("Task Priority:%d\n",tasks[i]->priority);
    }
    return 0;
}

// sample input:
// 3 //number of tasks
// hehe1 //description of task 1
// 1 // priority level of task 1
// hehe2 // description of task 2
// 3 //priority level of task 2
// hehe3 // description of task 3
// 2 // priority level of task 3

// sample output: 
// Unsorted Output
// Task Description:hehe1
// Task Priority:1
// Task Description:hehe2
// Task Priority:3
// Task Description:hehe3
// Task Priority:2

// Sorted Output
// Task Description:hehe1
// Task Priority:3
// Task Description:hehe2
// Task Priority:2
// Task Description:hehe3
// Task Priority:1
