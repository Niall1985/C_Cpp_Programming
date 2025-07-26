#include <stdio.h>
#include <string.h>

#define MAX 100

int numStates, numSymbols;
char states[MAX][10];
char alphabet[MAX];
char transitions[MAX][MAX][10];  // transitions[state][symbol] = next_state
char finalStates[MAX][10];
char startState[10];

int getStateIndex(char *state) {
    for (int i = 0; i < numStates; i++)
        if (strcmp(states[i], state) == 0)
            return i;
    return -1;
}

int isFinalState(char *state) {
    for (int i = 0; i < numStates; i++)
        if (strcmp(finalStates[i], state) == 0)
            return 1;
    return 0;
}

int main() {
    int numFinal;
    
    // Input states
    
    scanf("%d", &numStates);

    for (int i = 0; i < numStates; i++)
        scanf("%s", states[i]);

    // Input alphabet
  ;
    scanf("%d", &numSymbols);
 
    for (int i = 0; i < numSymbols; i++)
        scanf(" %c", &alphabet[i]);

    // Input transition table

    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < numSymbols; j++) {
            // printf("δ(%s, %c) = ", states[i], alphabet[j]);
            scanf("%s", transitions[i][j]);
        }
    }

    // Input final states
    scanf("%d", &numFinal);

    for (int i = 0; i < numFinal; i++)
        scanf("%s", finalStates[i]);

    // Input start state

    scanf("%s", startState);

    // Output grammar
    printf("\nRegular Grammar G = (N, T, P, S)\n");

    // Non-terminal symbols N
    printf("N = { ");
    for (int i = 0; i < numStates; i++)
        printf("%s ", states[i]);
    printf("}\n");

    // Terminal symbols T
    printf("T = { ");
    for (int i = 0; i < numSymbols; i++)
        printf("%c ", alphabet[i]);
    printf("}\n");

    // Start symbol S
    printf("S = %s\n", startState);

    // Production rules P
    printf("P = {\n");
    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < numSymbols; j++) {
            char *from = states[i];
            char symbol = alphabet[j];
            char *to = transitions[i][j];
            
            printf("  %s -> %c%s", from, symbol, to);
            if (isFinalState(to)) {
                printf(" | %c", symbol);  // Add terminal-only production for final state
            }
            printf("\n");
        }
    }
    printf("}\n");

    return 0;
}
