10. A
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STATES 100
#define MAX_ITEMS  100
#define MAX_SYMBOLS 20
#define MAX_PROD_LEN 20
#define MAX_PRODUCTIONS 30

typedef struct {
    char lhs;
    char rhs[MAX_PROD_LEN];
} Production;

int nProductions;
Production productions[MAX_PRODUCTIONS + 1]; // +1 for augmented grammar

typedef struct {
    int prodIndex;
    int dotPos;
    char lookahead;
} Item;

typedef struct {
    Item items[MAX_ITEMS];
    int itemCount;
} State;

State states[MAX_STATES];
int stateCount = 0;

// Terminals and Non-terminals
char terminals[MAX_SYMBOLS];
int nTerminals = 0;
char nonTerminals[MAX_SYMBOLS];
int nNonTerminals = 0;

void addTerminal(char c);
void addNonTerminal(char c);
int isTerminal(char c);
int isNonTerminal(char c);

int closure(State *I);
void gotoFunction(State *I, char X, State *J);
int itemsEqual(Item *a, Item *b);
int stateEqual(State *a, State *b);
int findState(State *I);
int prodLen(int index);

int terminalIndex(char c);
int nonTerminalIndex(char c);

void buildActionGotoTables();
void printTables();

int actionTable[MAX_STATES][MAX_SYMBOLS];  
int actionType[MAX_STATES][MAX_SYMBOLS];   
int gotoTable[MAX_STATES][MAX_SYMBOLS];   

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &nProductions);
    getchar();

    for (int i = 0; i < nProductions; i++) {
        char line[100];
        printf("Enter production %d: ", i+1);
        fgets(line, sizeof(line), stdin);

        char *arrow = strstr(line, "->");
        if (!arrow) {
            printf("Invalid production format.\n");
            i--;
            continue;
        }

        productions[i].lhs = line[0];
        strcpy(productions[i].rhs, arrow + 2);

        int len = strlen(productions[i].rhs);
        if (productions[i].rhs[len-1] == '\n') productions[i].rhs[len-1] = '\0';

        addNonTerminal(productions[i].lhs);
        for (int j = 0; productions[i].rhs[j]; j++) {
            char c = productions[i].rhs[j];
            if (isupper(c)) addNonTerminal(c);
            else if (c != ' ' && c != '\t') addTerminal(c);
        }
    }

    // Augmented grammar: Z->S
    char startSymbol = productions[0].lhs;
    productions[nProductions].lhs = 'Z';
    productions[nProductions].rhs[0] = startSymbol;
    productions[nProductions].rhs[1] = '\0';
    addNonTerminal('Z');
    nProductions++;

    addTerminal('$');

    // Initial state closure({[Z->.S,$]})
    State start;
    start.itemCount = 1;
    start.items[0].prodIndex = nProductions - 1;
    start.items[0].dotPos = 0;
    start.items[0].lookahead = '$';
    closure(&start);
    states[0] = start;
    stateCount = 1;

    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < stateCount; i++) {
            State *cur = &states[i];
            for (int j = 0; j < nTerminals + nNonTerminals; j++) {
                char X = (j < nTerminals) ? terminals[j] : nonTerminals[j - nTerminals];
                State next;
                gotoFunction(cur, X, &next);
                if (next.itemCount == 0) continue;

                if (findState(&next) == -1) {
                    states[stateCount++] = next;
                    changed = 1;
                }
            }
        }
    }

    buildActionGotoTables();
    printTables();

    return 0;
}

// --- Implementations ---

void addTerminal(char c) {
    if (c == ' ' || c == '\t') return;
    for (int i = 0; i < nTerminals; i++)
        if (terminals[i] == c) return;
    terminals[nTerminals++] = c;
}

void addNonTerminal(char c) {
    for (int i = 0; i < nNonTerminals; i++)
        if (nonTerminals[i] == c) return;
    nonTerminals[nNonTerminals++] = c;
}

int isTerminal(char c) {
    for (int i = 0; i < nTerminals; i++)
        if (terminals[i] == c) return 1;
    return 0;
}

int isNonTerminal(char c) {
    for (int i = 0; i < nNonTerminals; i++)
        if (nonTerminals[i] == c) return 1;
    return 0;
}

int prodLen(int index) {
    return strlen(productions[index].rhs);
}

int itemsEqual(Item *a, Item *b) {
    return a->prodIndex == b->prodIndex && a->dotPos == b->dotPos && a->lookahead == b->lookahead;
}

int stateEqual(State *a, State *b) {
    if (a->itemCount != b->itemCount) return 0;
    for (int i = 0; i < a->itemCount; i++) {
        int found = 0;
        for (int j = 0; j < b->itemCount; j++) {
            if (itemsEqual(&a->items[i], &b->items[j])) {
                found = 1;
                break;
            }
        }
        if (!found) return 0;
    }
    return 1;
}

int findState(State *I) {
    for (int i = 0; i < stateCount; i++) {
        if (stateEqual(&states[i], I)) return i;
    }
    return -1;
}

int closure(State *I) {
    int added;
    do {
        added = 0;
        for (int i = 0; i < I->itemCount; i++) {
            Item it = I->items[i];
            int p = it.prodIndex;
            int dot = it.dotPos;

            if (dot < prodLen(p)) {
                char B = productions[p].rhs[dot];
                if (isNonTerminal(B)) {
                    for (int prodIdx = 0; prodIdx < nProductions; prodIdx++) {
                        if (productions[prodIdx].lhs == B) {
                            for (int t = 0; t < nTerminals; t++) {
                                Item newItem = {prodIdx, 0, terminals[t]};
                                int present = 0;
                                for (int m = 0; m < I->itemCount; m++) {
                                    if (itemsEqual(&I->items[m], &newItem)) {
                                        present = 1;
                                        break;
                                    }
                                }
                                if (!present) {
                                    I->items[I->itemCount++] = newItem;
                                    added = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    } while (added);
    return 1;
}

void gotoFunction(State *I, char X, State *J) {
    J->itemCount = 0;
    for (int i = 0; i < I->itemCount; i++) {
        Item it = I->items[i];
        int p = it.prodIndex;
        int dot = it.dotPos;
        if (dot < prodLen(p) && productions[p].rhs[dot] == X) {
            Item newItem = {p, dot + 1, it.lookahead};
            J->items[J->itemCount++] = newItem;
        }
    }
    closure(J);
}

int terminalIndex(char c) {
    for (int i = 0; i < nTerminals; i++) if (terminals[i] == c) return i;
    return -1;
}

int nonTerminalIndex(char c) {
    for (int i = 0; i < nNonTerminals; i++) if (nonTerminals[i] == c) return i;
    return -1;
}

void buildActionGotoTables() {
    for (int i = 0; i < stateCount; i++) {
        for (int j = 0; j < nTerminals; j++) {
            actionTable[i][j] = -1;
            actionType[i][j] = 0;
        }
        for (int j = 0; j < nNonTerminals; j++) {
            gotoTable[i][j] = -1;
        }
    }

    for (int i = 0; i < stateCount; i++) {
        State *state = &states[i];

        // Reduce/accept
        for (int k = 0; k < state->itemCount; k++) {
            Item *item = &state->items[k];
            Production *p = &productions[item->prodIndex];
            int len = prodLen(item->prodIndex);

            if (item->dotPos == len) {
                if (p->lhs == 'Z') {
                    if (item->lookahead == '$') {
                        int idx = terminalIndex('$');
                        if (idx != -1) {
                            actionType[i][idx] = 3;
                            actionTable[i][idx] = -2; // accept
                        }
                    }
                } else {
                    int idx = terminalIndex(item->lookahead);
                    if (idx != -1) {
                        if (actionType[i][idx] == 0) {
                            actionType[i][idx] = 2; // reduce
                            actionTable[i][idx] = item->prodIndex;
                        } else {
                            printf("Conflict at state %d on terminal '%c'\n", i, item->lookahead);
                        }
                    }
                }
            }
        }

        // Shift
        for (int j = 0; j < nTerminals; j++) {
            char X = terminals[j];
            State next;
            gotoFunction(state, X, &next);
            if (next.itemCount > 0) {
                int s = findState(&next);
                if (s != -1) {
                    if (actionType[i][j] == 0) {
                        actionType[i][j] = 1;
                        actionTable[i][j] = s;
                    } else if (actionType[i][j] == 2) {
                        printf("Shift/Reduce conflict at state %d on terminal '%c'\n", i, X);
                    }
                }
            }
        }

        // GOTO
        for (int j = 0; j < nNonTerminals; j++) {
            char X = nonTerminals[j];
            State next;
            gotoFunction(state, X, &next);
            if (next.itemCount > 0) {
                int s = findState(&next);
                if (s != -1) {
                    gotoTable[i][j] = s;
                }
            }
        }
    }
}

void printTables() {
    printf("\nACTION and GOTO tables:\n");

    // Header
    printf("State |");
    for (int j = 0; j < nTerminals; j++) {
        printf("  %c  |", terminals[j]);
    }
    printf("  ||  ");
    for (int j = 0; j < nNonTerminals; j++) {
        printf(" %c |", nonTerminals[j]);
    }
    printf("\n");

    printf("------------------------------------------------------------\n");

    for (int i = 0; i < stateCount; i++) {
        printf("%5d |", i);
        for (int j = 0; j < nTerminals; j++) {
            switch (actionType[i][j]) {
                case 0: printf("     |"); break;       // error
                case 1: printf(" s%-3d|", actionTable[i][j]); break; // shift
                case 2: printf(" r%-3d|", actionTable[i][j]); break; // reduce
                case 3: printf(" acc |"); break;       // accept
            }
        }
        printf("  ||  ");
        for (int j = 0; j < nNonTerminals; j++) {
            if (gotoTable[i][j] == -1) printf("   |");
            else printf("%3d|", gotoTable[i][j]);
        }
        printf("\n");
    }
}
 
10 B
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STATES 100
#define MAX_ITEMS  100
#define MAX_SYMBOLS 20
#define MAX_PROD_LEN 20
#define MAX_PRODUCTIONS 30
#define MAX_STACK 1000
#define MAX_INPUT 1000

typedef struct {
    char lhs;
    char rhs[MAX_PROD_LEN];
} Production;

int nProductions;
Production productions[MAX_PRODUCTIONS + 1]; // +1 for augmented grammar

typedef struct {
    int prodIndex;
    int dotPos;
    char lookahead;
} Item;

typedef struct {
    Item items[MAX_ITEMS];
    int itemCount;
} State;

State states[MAX_STATES];
int stateCount = 0;

// Terminals and Non-terminals
char terminals[MAX_SYMBOLS];
int nTerminals = 0;
char nonTerminals[MAX_SYMBOLS];
int nNonTerminals = 0;

void addTerminal(char c);
void addNonTerminal(char c);
int isTerminal(char c);
int isNonTerminal(char c);

int closure(State *I);
void gotoFunction(State *I, char X, State *J);
int itemsEqual(Item *a, Item *b);
int stateEqual(State *a, State *b);
int findState(State *I);
int prodLen(int index);

int terminalIndex(char c);
int nonTerminalIndex(char c);

void buildActionGotoTables();
void printTables();

int actionTable[MAX_STATES][MAX_SYMBOLS];  // stores state index or prod number or special
int actionType[MAX_STATES][MAX_SYMBOLS];   // 0=error,1=shift,2=reduce,3=accept
int gotoTable[MAX_STATES][MAX_SYMBOLS];   // stores next state

// LR Parser functions
int parseInput(char *input);

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &nProductions);
    getchar();

    for (int i = 0; i < nProductions; i++) {
        char line[100];
        printf("Enter production %d: ", i+1);
        fgets(line, sizeof(line), stdin);

        char *arrow = strstr(line, "->");
        if (!arrow) {
            printf("Invalid production format.\n");
            i--;
            continue;
        }

        productions[i].lhs = line[0];
        strcpy(productions[i].rhs, arrow + 2);

        int len = strlen(productions[i].rhs);
        if (productions[i].rhs[len-1] == '\n') productions[i].rhs[len-1] = '\0';

        addNonTerminal(productions[i].lhs);
        for (int j = 0; productions[i].rhs[j]; j++) {
            char c = productions[i].rhs[j];
            if (isupper(c)) addNonTerminal(c);
            else if (c != ' ' && c != '\t') addTerminal(c);
        }
    }

    // Augmented grammar: Z->S
    char startSymbol = productions[0].lhs;
    productions[nProductions].lhs = 'Z';
    productions[nProductions].rhs[0] = startSymbol;
    productions[nProductions].rhs[1] = '\0';
    addNonTerminal('Z');
    nProductions++;

    addTerminal('$');

    // Initial state closure({[Z->.S,$]})
    State start;
    start.itemCount = 1;
    start.items[0].prodIndex = nProductions - 1;
    start.items[0].dotPos = 0;
    start.items[0].lookahead = '$';
    closure(&start);
    states[0] = start;
    stateCount = 1;

    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < stateCount; i++) {
            State *cur = &states[i];
            for (int j = 0; j < nTerminals + nNonTerminals; j++) {
                char X = (j < nTerminals) ? terminals[j] : nonTerminals[j - nTerminals];
                State next;
                gotoFunction(cur, X, &next);
                if (next.itemCount == 0) continue;

                if (findState(&next) == -1) {
                    states[stateCount++] = next;
                    changed = 1;
                }
            }
        }
    }

    buildActionGotoTables();

    // Print only tables
    printTables();

    // Get input string for parsing
    char input[MAX_INPUT];
    printf("\nEnter input string terminated by $: ");
    fgets(input, sizeof(input), stdin);
    int len = strlen(input);
    if (input[len-1] == '\n') input[len-1] = '\0';

    // Parse the input
    if (parseInput(input)) {
        printf("Input string is accepted by the grammar.\n");
    } else {
        printf("Input string is rejected by the grammar.\n");
    }

    return 0;
}

// --- Implementations ---

void addTerminal(char c) {
    if (c == ' ' || c == '\t') return;
    for (int i = 0; i < nTerminals; i++)
        if (terminals[i] == c) return;
    terminals[nTerminals++] = c;
}

void addNonTerminal(char c) {
    for (int i = 0; i < nNonTerminals; i++)
        if (nonTerminals[i] == c) return;
    nonTerminals[nNonTerminals++] = c;
}

int isTerminal(char c) {
    for (int i = 0; i < nTerminals; i++)
        if (terminals[i] == c) return 1;
    return 0;
}

int isNonTerminal(char c) {
    for (int i = 0; i < nNonTerminals; i++)
        if (nonTerminals[i] == c) return 1;
    return 0;
}

int prodLen(int index) {
    return strlen(productions[index].rhs);
}

int itemsEqual(Item *a, Item *b) {
    return a->prodIndex == b->prodIndex && a->dotPos == b->dotPos && a->lookahead == b->lookahead;
}

int stateEqual(State *a, State *b) {
    if (a->itemCount != b->itemCount) return 0;
    for (int i = 0; i < a->itemCount; i++) {
        int found = 0;
        for (int j = 0; j < b->itemCount; j++) {
            if (itemsEqual(&a->items[i], &b->items[j])) {
                found = 1;
                break;
            }
        }
        if (!found) return 0;
    }
    return 1;
}

int findState(State *I) {
    for (int i = 0; i < stateCount; i++) {
        if (stateEqual(&states[i], I)) return i;
    }
    return -1;
}

int closure(State *I) {
    int added;
    do {
        added = 0;
        for (int i = 0; i < I->itemCount; i++) {
            Item it = I->items[i];
            int p = it.prodIndex;
            int dot = it.dotPos;

            if (dot < prodLen(p)) {
                char B = productions[p].rhs[dot];
                if (isNonTerminal(B)) {
                    for (int prodIdx = 0; prodIdx < nProductions; prodIdx++) {
                        if (productions[prodIdx].lhs == B) {
                            for (int t = 0; t < nTerminals; t++) {
                                Item newItem = {prodIdx, 0, terminals[t]};
                                int present = 0;
                                for (int m = 0; m < I->itemCount; m++) {
                                    if (itemsEqual(&I->items[m], &newItem)) {
                                        present = 1;
                                        break;
                                    }
                                }
                                if (!present) {
                                    I->items[I->itemCount++] = newItem;
                                    added = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    } while (added);
    return 1;
}

void gotoFunction(State *I, char X, State *J) {
    J->itemCount = 0;
    for (int i = 0; i < I->itemCount; i++) {
        Item it = I->items[i];
        int p = it.prodIndex;
        int dot = it.dotPos;
        if (dot < prodLen(p) && productions[p].rhs[dot] == X) {
            Item newItem = {p, dot + 1, it.lookahead};
            J->items[J->itemCount++] = newItem;
        }
    }
    closure(J);
}

int terminalIndex(char c) {
    for (int i = 0; i < nTerminals; i++) if (terminals[i] == c) return i;
    return -1;
}

int nonTerminalIndex(char c) {
    for (int i = 0; i < nNonTerminals; i++) if (nonTerminals[i] == c) return i;
    return -1;
}

void buildActionGotoTables() {
    for (int i = 0; i < stateCount; i++) {
        for (int j = 0; j < nTerminals; j++) {
            actionTable[i][j] = -1;
            actionType[i][j] = 0;
        }
        for (int j = 0; j < nNonTerminals; j++) {
            gotoTable[i][j] = -1;
        }
    }

    for (int i = 0; i < stateCount; i++) {
        State *state = &states[i];

        // Reduce/accept
        for (int k = 0; k < state->itemCount; k++) {
            Item *item = &state->items[k];
            Production *p = &productions[item->prodIndex];
            int len = prodLen(item->prodIndex);

            if (item->dotPos == len) {
                if (p->lhs == 'Z') {
                    if (item->lookahead == '$') {
                        int idx = terminalIndex('$');
                        if (idx != -1) {
                            actionType[i][idx] = 3;
                            actionTable[i][idx] = -2; // accept
                        }
                    }
                } else {
                    int idx = terminalIndex(item->lookahead);
                    if (idx != -1) {
                        if (actionType[i][idx] == 0) {
                            actionType[i][idx] = 2; // reduce
                            actionTable[i][idx] = item->prodIndex;
                        } else {
                            printf("Conflict at state %d on terminal '%c'\n", i, item->lookahead);
                        }
                    }
                }
            }
        }

        // Shift
        for (int j = 0; j < nTerminals; j++) {
            char X = terminals[j];
            State next;
            gotoFunction(state, X, &next);
            if (next.itemCount > 0) {
                int s = findState(&next);
                if (s != -1) {
                    if (actionType[i][j] == 0) {
                        actionType[i][j] = 1;
                        actionTable[i][j] = s;
                    } else if (actionType[i][j] == 2) {
                        printf("Shift/Reduce conflict at state %d on terminal '%c'\n", i, X);
                    }
                }
            }
        }

        // GOTO
        for (int j = 0; j < nNonTerminals; j++) {
            char X = nonTerminals[j];
            State next;
            gotoFunction(state, X, &next);
            if (next.itemCount > 0) {
                int s = findState(&next);
                if (s != -1) {
                    gotoTable[i][j] = s;
                }
            }
        }
    }
}

void printTables() {
    printf("\nACTION and GOTO tables:\n");

    // Header
    printf("State |");
    for (int j = 0; j < nTerminals; j++) {
        printf("  %c  |", terminals[j]);
    }
    printf("  ||  ");
    for (int j = 0; j < nNonTerminals; j++) {
        printf(" %c |", nonTerminals[j]);
    }
    printf("\n");

    printf("------------------------------------------------------------\n");

    for (int i = 0; i < stateCount; i++) {
        printf("%5d |", i);
        for (int j = 0; j < nTerminals; j++) {
            switch (actionType[i][j]) {
                case 0: printf("     |"); break;       // error
                case 1: printf(" s%-3d|", actionTable[i][j]); break; // shift
                case 2: printf(" r%-3d|", actionTable[i][j]); break; // reduce
                case 3: printf(" acc |"); break;       // accept
            }
        }
        printf("  ||  ");
        for (int j = 0; j < nNonTerminals; j++) {
            if (gotoTable[i][j] == -1) printf("   |");
            else printf("%3d|", gotoTable[i][j]);
        }
        printf("\n");
    }
}

// Parse input using LR parsing table
int parseInput(char *input) {
    int stack[MAX_STACK];
    char symbolStack[MAX_STACK];
    int top = 0;
    stack[top] = 0; // start with state 0
    symbolStack[top] = '#'; // bottom marker
    top++;

    int ip = 0;
    int len = strlen(input);

    printf("\nParsing steps:\n");
    printf("Stack\t\tInput\t\tAction\n");

    while (1) {
        int state = stack[top - 1];
        char a = input[ip];
        int aIndex = terminalIndex(a);

        if (aIndex == -1) {
            printf("Error: unexpected symbol '%c' in input\n", a);
            return 0;
        }

        printf("[");
        for (int i = 0; i < top; i++) printf("%d%c ", stack[i], symbolStack[i]);
        printf("]\t%s\t", input + ip);

        int action = actionType[state][aIndex];
        int val = actionTable[state][aIndex];

        if (action == 1) {
            // shift
            printf("Shift %d\n", val);
            stack[top] = val;
            symbolStack[top] = a;
            top++;
            ip++;
        } else if (action == 2) {
            // reduce
            Production *p = &productions[val];
            printf("Reduce by %c->%s\n", p->lhs, p->rhs);

            int lenRHS = prodLen(val);
            top -= lenRHS;
            // pop symbols and states

            // push LHS symbol
            symbolStack[top] = p->lhs;
            int gIdx = nonTerminalIndex(p->lhs);
            if (gIdx == -1) {
                printf("Error: non-terminal %c not found in GOTO\n", p->lhs);
                return 0;
            }
            int gotoState = gotoTable[stack[top - 1]][gIdx];
            if (gotoState == -1) {
                printf("Error: GOTO undefined for state %d and symbol %c\n", stack[top - 1], p->lhs);
                return 0;
            }
            stack[top] = gotoState;
            top++;
        } else if (action == 3) {
            printf("Accept\n");
            return 1;
        } else {
            printf("Error: no action defined for state %d and input '%c'\n", state, a);
            return 0;
        }
    }
}


6
E
E->E+T
E->T
T->T*F
T->F
F->(E)
F->i
