#include <stdio.h>
#include <string.h>

#define MAX 100

int numStates, numSymbols;
char states[MAX], symbols[MAX];
int transition[MAX][MAX]; // Transition table
char finalStates[MAX];
char startState;

// Get the index of a state
int getStateIndex(char state) {
    for (int i = 0; i < numStates; i++) {
        if (states[i] == state)
            return i;
    }
    return -1;
}

// Get the index of a symbol
int getSymbolIndex(char symbol) {
    for (int i = 0; i < numSymbols; i++) {
        if (symbols[i] == symbol)
            return i;
    }
    return -1;
}

// Check if a state is final
int isFinalState(char state) {
    for (int i = 0; i < strlen(finalStates); i++) {
        if (finalStates[i] == state)
            return 1;
    }
    return 0;
}

int main() {
    char w[100];

    // Input states
    printf("Enter number of states: ");
    scanf("%d", &numStates);
    printf("Enter states (e.g., ABC): ");
    scanf("%s", states);

    // Input symbols
    printf("Enter number of input symbols: ");
    scanf("%d", &numSymbols);
    printf("Enter symbols (e.g., 01): ");
    scanf("%s", symbols);

    // Input transition table
    printf("Enter transition table:\n");
    printf("For each state and symbol, enter the resulting state.\n");

    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < numSymbols; j++) {
            char nextState;
            printf("δ(%c, %c) = ", states[i], symbols[j]);
            scanf(" %c", &nextState);
            transition[i][j] = getStateIndex(nextState);
        }
    }

    // Input final states
    printf("Enter final states (e.g., C): ");
    scanf("%s", finalStates);

    // Input start state
    printf("Enter start state: ");
    scanf(" %c", &startState);

    // Input string to test
    printf("Enter string to test: ");
    scanf("%s", w);

    // Processing the string
    int currentState = getStateIndex(startState);
    printf("\nTransition sequence:\n");
    printf("%c", states[currentState]);

    for (int i = 0; i < strlen(w); i++) {
        int symbolIndex = getSymbolIndex(w[i]);
        if (symbolIndex == -1) {
            printf("\nInvalid input symbol: %c\n", w[i]);
            return 1;
        }
        currentState = transition[currentState][symbolIndex];
        printf(" -> %c", states[currentState]);
    }

    if (isFinalState(states[currentState])) {
        printf("\n\nResult: String accepted!\n");
    } else {
        printf("\n\nResult: String rejected.\n");
    }

    // Print transition table
    printf("\nTransition Table:\n  ");
    for (int j = 0; j < numSymbols; j++)
        printf("  %c", symbols[j]);
    printf("\n");

    for (int i = 0; i < numStates; i++) {
        printf("%c ", states[i]);
        for (int j = 0; j < numSymbols; j++) {
            printf("  %c", states[transition[i][j]]);
        }
        printf("\n");
    }

    return 0;
}
