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
