#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Date{
  int date;
  char month[10];
  int year;
};
struct Events{
  char name[30];
  char type[30];
  float duration;
  float expenses;
  struct Date scheduleDate;
};
int main()
{
  int n;
  scanf("%d",&n);
  struct Events *events=(struct Events*)malloc(n*sizeof(struct Events));
  for(int i=0;i<n;i++){
    scanf("%s",events[i].name);
    scanf("%s",events[i].type);
    scanf("%f",&events[i].duration);
    scanf("%f",&events[i].expenses);
    scanf("%d %s %d",&events[i].scheduleDate.date,events[i].scheduleDate.month, &events[i].scheduleDate.year);
  }
  for(int i=0;i<n;i++){
    printf("Name: %s",events[i].name);
    printf("\n");
    printf("Type: %s",events[i].type);
    printf("\n");
    printf("Duration: %.1f hrs",events[i].duration);
    printf("\n");
    printf("Expenses: Rs %.2f",events[i].expenses);
    printf("\n");
    printf("Date: %d %s %d",events[i].scheduleDate.date,events[i].scheduleDate.month, events[i].scheduleDate.year);
    printf("\n");
    printf("\n");
  }
  return 0;
}
//malloc declaration -> int *ptr1 = (int*)malloc(n*sizeof(int));
//calloc decleration -> int *ptr2 = (int*)calloc(n,sizeof(int));
//realloc decleration -> int *ptr3 = (int*)realloc(*ptr1,n*sizeof(int));

/*Output:

Name: Hehe
Type: Comedy
Duration: 3.5 hrs
Epenses: Rs 10000.00
Date: 10 january 2024

Name: Hoho
Type: Musical
Duration: 2.0 hrs
Epenses: Rs 150000.00
Date: 10 March 2024*/
