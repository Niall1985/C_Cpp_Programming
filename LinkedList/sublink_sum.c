/*Jack is working on a project involving a doubly linked list of integers. He needs to find all pairs of nodes in the list that sum up to a given value, x. Jack wants to implement a function that efficiently identifies and prints these pairs or indicates if no such pairs exist. Help him by giving a suitable program.

Input format :
The first line of input contains an integer n, representing the number of elements in the linked list.

The second line consists of n space-separated positive distinct integers, representing the elements in the sorted doubly-linked list.

The third line contains an integer x, indicating the target sum value.

Output format :
The output should display pairs in the linked list whose sum equals x.

If there are no such pairs in the list, print "No pair found".



Refer to the sample output for formatting specifications.

Code constraints :
In this scenario, given test cases will fall under the following constraints:

2 ≤ n ≤ 10

0 ≤ element, x ≤ 100

Sample test cases :
Input 1 :
7
1 2 4 5 6 8 9
7
Output 1 :
(6, 1)
(5, 2)
Input 2 :
7
1 2 4 5 6 8 9
3
Output 2 :
(2, 1)
Input 3 :
7
1 2 4 5 6 8 9
30
Output 3 :
No pair found
Input 4 :
5
0 1 2 3 5
5
Output 4 :
(5, 0)
(3, 2) */


#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* next;
    struct node* prev;
};
struct node *head = NULL;
struct node *tail = NULL;
void insertEnd(int data){
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;
    temp->prev = NULL;
    if(head == NULL){
        head = temp;
        tail = temp;
    }
    else{
        tail->next = temp;
        temp->prev = tail;
        tail=temp;
    }
}

void print(int target){
    struct node *start = head;
    struct node *end = tail;
    int found = 0;
    while(start != end && end->next != start){
        int sum = start->data+end->data;
        if(sum == target) {
            printf("(%d, %d)\n", end->data, start->data);
            found = 1;
            start = start->next;
            end = end->prev;
        } else if(sum < target) {
            start = start->next;  
        } else {
            end = end->prev;  
        }
    }
    if(!found){
        printf("No pair found");
    }
}

int main(){
    int n, data;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&data);
        insertEnd(data);
    }
    int target;
    scanf("%d", &target);
    print(target);
}
