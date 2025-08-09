#include <stdio.h>
#include <string.h>
#define MAX 100
int numStates, numSymbols;
char states[MAX][10], symbols[MAX];
char transition[MAX][MAX][10];
char finalStates[MAX][10];
char startState[10];

int getStateIndex(char *state) {
    for (int i = 0; i < numStates; i++) {
        if (strcmp(states[i], state) == 0)
            return i;
    }
    return -1;
}
int getSymbolIndex(char symbol) {
    for (int i = 0; i < numSymbols; i++) {
        if (symbols[i] == symbol)
            return i;
    }
    return -1;
}
int isFinalState(char *state) {
    for (int i = 0; i < numStates; i++) {
        if (strcmp(finalStates[i], state) == 0)
            return 1;
    }
    return 0;
}
int main() {
    char w[100];
    char currentState[10];

    scanf("%d", &numStates);
    for (int i = 0; i < numStates; i++) {
        scanf("%s", states[i]);
    }
    scanf("%d", &numSymbols);
    scanf("%s", symbols);
    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < numSymbols; j++) {
            scanf("%s", transition[i][j]);
        }
    }
    int numFinal;
    scanf("%d", &numFinal);
    for (int i = 0; i < numFinal; i++) {
        scanf("%s", finalStates[i]);
    }
    scanf("%s", startState);
    scanf("%s", w);
    strcpy(currentState, startState);
    printf("\nTransition sequence:\n%s", currentState);

    for (int i = 0; i < strlen(w); i++) {
        int symbolIndex = getSymbolIndex(w[i]);
        if (symbolIndex == -1) {
            printf("\nInvalid input symbol: %c\n", w[i]);
            return 1;
        }

        int stateIndex = getStateIndex(currentState);
        if (stateIndex == -1) {
            printf("\nInvalid current state: %s\n", currentState);
            return 1;
        }

        strcpy(currentState, transition[stateIndex][symbolIndex]);
        printf(" -> %s", currentState);
    }

    if (isFinalState(currentState)) {
        printf("\n\nResult: String accepted!\n");
    } else {
        printf("\n\nResult: String rejected.\n");
    }

    // Print transition table
    printf("\nTransition Table:\n   ");
    for (int j = 0; j < numSymbols; j++)
        printf("   %c", symbols[j]);
    printf("\n");

    for (int i = 0; i < numStates; i++) {
        printf("%s ", states[i]);
        for (int j = 0; j < numSymbols; j++) {
            printf(" %3s", transition[i][j]);
        }
        printf("\n");
    }
    return 0;
}






The following relations keep track of airline flight information: 
Flights(flno: integer, from: string, to: string, distance: integer, departs:time, arrives:time, price: 
integer) 
Aircraft(aid: integer, aname: string, cruisingrange: integer) 
Certified(eid: integer, aid: integer) 
Employees(eid: integer, ename: string, salary: integer) 
Note that the Employees relation describes pilots and other kinds of employees as well; 
every pilot is certified for some aircraft, and only pilots are certified to fly. 
Write each of the following queries in SQL. 
1. For each pilot who is certified for more than three aircraft, find the eid and the 
maximum cruising range of the aircraft for which she or he is certified. 
2. Find the names of pilots whose salary is less than the price of the cheapest route from 
Los Angeles to Honolulu. 
3. For all aircraft with cruising range over 1000 miles, find the name of the aircraft and the 
average salary of all pilots certified for this aircraft. 
4. Find the names of pilots certified for some Boeing aircraft. 
5. Find the aids of all aircraft that can be used on routes from Los Angeles to Chicago. 
6. Identify the routes that can be piloted by every pilot who makes more than $100,000. 
7. Print the enames of pilots who can operate planes with cruising range greater than 3000 
miles but are not certified on any Boeing aircraft. 
8. Compute the difference between the average salary of a pilot and the average salary of 
all employees (including pilots). 
9. Print the name and salary of every nonpilot whose salary is more than the average 
salary for pilots
10. Print the names of employees who are certified only on aircrafts with cruising range 
longer than 1000 miles
