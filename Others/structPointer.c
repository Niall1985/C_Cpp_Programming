// using memory allocation with structures
#include <stdio.h>
#include <stdlib.h>
struct date{
  int day;
  char month[15];
  int year;
};
struct Event{
  char name[30];
  char type[30];
  float cost;
  float duration;
  struct date d;
};
int main()
{
  int n;
  scanf("%d",&n);
  struct Event *event[n];
  for(int i=0;i<n;i++){
    event[i] =(struct Event *)malloc(sizeof(struct Event));
    scanf("%s",event[i]->name);
    scanf("%s",event[i]->type);
    scanf("%f",&event[i]->cost);
    scanf("%f",&event[i]->duration);
    scanf("%d %s %d",&event[i]->d.day,event[i]->d.month,&event[i]->d.year);
  }
  printf("Event Details:\n");
  for(int i=0;i<n;i++){
    printf("Name:%s\n",event[i]->name);
    printf("Type:%s\n",event[i]->type);
    printf("Cost:$%.2f\n",event[i]->cost);
    printf("Duration:%.1f hrs\n",event[i]->duration);
    printf("Event Date:%d %s %d",event[i]->d.day,event[i]->d.month,event[i]->d.year);
  }
}
//malloc declaration -> int *ptr1 = (int*)malloc(n*sizeof(int));
//calloc decleration -> int *ptr2 = (int*)calloc(n,sizeof(int));
//realloc decleration -> int *ptr3 = (int*)realloc(*ptr1,n*sizeof(int));

/*Output:

Name: Hehe1
Type: Comedy
Duration: 3.5 hrs
Epenses: Rs 10000.00
Date: 10 january 2024

Name: Hehe2
Type: Musical
Duration: 2.0 hrs
Epenses: Rs 150000.00
Date: 10 March 2024*/
