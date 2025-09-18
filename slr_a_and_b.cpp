#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_RULES 50
#define MAX_SYMBOLS 20
#define MAX_STATES 100
#define MAX_ITEMS 20

// Grammar structure
typedef struct {
    char lhs;
    char rhs[15];
} Production;

// LR(0) Item
typedef struct {
    int prod_num;
    int dot_pos;
} Item;

// State
typedef struct {
    Item items[MAX_ITEMS];
    int item_count;
    int state_num;
} State;

// Global variables
Production grammar[MAX_RULES];
int num_productions = 0;
State states[MAX_STATES];
int num_states = 0;
int action_table[MAX_STATES][256];  // ACTION table
int goto_table[MAX_STATES][256];    // GOTO table
char terminals[MAX_SYMBOLS];
char non_terminals[MAX_SYMBOLS];
int num_terminals = 0, num_non_terminals = 0;
char start_symbol;

void input_grammar() {
    
    scanf("%d", &num_productions);
    
    scanf(" %c", &start_symbol);
    
    // Create augmented grammar
    grammar[0].lhs = 'S';  // Augmented start symbol
    grammar[0].rhs[0] = start_symbol;
    grammar[0].rhs[1] = '\0';
    
    
    for(int i = 1; i <= num_productions; i++) {
        char input[20];
        printf("Production %d: ", i);
        scanf("%s", input);
        
        // Parse the production A->BC
        char *arrow = strstr(input, "->");
        if(arrow == NULL) {
            printf("Invalid format! Use A->BC\n");
            i--;
            continue;
        }
        
        // Extract LHS
        grammar[i].lhs = input[0];
        
        // Extract RHS
        strcpy(grammar[i].rhs, arrow + 2);
    }
    
    num_productions++; // Include augmented production
    
    printf("\n");
}

void print_grammar() {
    printf("Augmented Grammar:\n");
    for(int i = 0; i < num_productions; i++) {
        printf("%d. %c -> %s\n", i, grammar[i].lhs, grammar[i].rhs);
    }
    printf("\n");
}

void find_symbols() {
    num_terminals = 0;
    num_non_terminals = 0;
    
    // Find terminals and non-terminals
    for(int i = 0; i < num_productions; i++) {
        // Add LHS to non-terminals
        int found = 0;
        for(int j = 0; j < num_non_terminals; j++) {
            if(non_terminals[j] == grammar[i].lhs) {
                found = 1;
                break;
            }
        }
        if(!found) {
            non_terminals[num_non_terminals++] = grammar[i].lhs;
        }
        
        // Check RHS symbols
        for(int k = 0; k < strlen(grammar[i].rhs); k++) {
            char sym = grammar[i].rhs[k];
            
            // Check if it's non-terminal
            int is_nt = 0;
            for(int j = 0; j < num_productions; j++) {
                if(grammar[j].lhs == sym) {
                    is_nt = 1;
                    break;
                }
            }
            
            if(!is_nt && sym != 'e') {  // 'e' represents epsilon
                // Add to terminals
                int found_t = 0;
                for(int j = 0; j < num_terminals; j++) {
                    if(terminals[j] == sym) {
                        found_t = 1;
                        break;
                    }
                }
                if(!found_t) {
                    terminals[num_terminals++] = sym;
                }
            }
        }
    }
    
    // Add $ to terminals
    terminals[num_terminals++] = '$';
}

int is_terminal(char c) {
    for(int i = 0; i < num_terminals; i++) {
        if(terminals[i] == c) return 1;
    }
    return 0;
}

void closure(State *state) {
    int added = 1;
    while(added) {
        added = 0;
        for(int i = 0; i < state->item_count; i++) {
            Item *item = &state->items[i];
            Production *prod = &grammar[item->prod_num];
            
            if(item->dot_pos < strlen(prod->rhs)) {
                char next_symbol = prod->rhs[item->dot_pos];
                
                // If next symbol is non-terminal
                if(!is_terminal(next_symbol) && next_symbol != 'e') {
                    // Add all productions with this non-terminal as LHS
                    for(int j = 0; j < num_productions; j++) {
                        if(grammar[j].lhs == next_symbol) {
                            // Check if item already exists
                            int exists = 0;
                            for(int k = 0; k < state->item_count; k++) {
                                if(state->items[k].prod_num == j && 
                                   state->items[k].dot_pos == 0) {
                                    exists = 1;
                                    break;
                                }
                            }
                            
                            if(!exists && state->item_count < MAX_ITEMS) {
                                state->items[state->item_count].prod_num = j;
                                state->items[state->item_count].dot_pos = 0;
                                state->item_count++;
                                added = 1;
                            }
                        }
                    }
                }
            }
        }
    }
}

State go_to(State *state, char symbol) {
    State new_state;
    new_state.item_count = 0;
    
    for(int i = 0; i < state->item_count; i++) {
        Item *item = &state->items[i];
        Production *prod = &grammar[item->prod_num];
        
        if(item->dot_pos < strlen(prod->rhs) && 
           prod->rhs[item->dot_pos] == symbol) {
            new_state.items[new_state.item_count].prod_num = item->prod_num;
            new_state.items[new_state.item_count].dot_pos = item->dot_pos + 1;
            new_state.item_count++;
        }
    }
    
    if(new_state.item_count > 0) {
        closure(&new_state);
    }
    
    return new_state;
}

int states_equal(State *s1, State *s2) {
    if(s1->item_count != s2->item_count) return 0;
    
    for(int i = 0; i < s1->item_count; i++) {
        int found = 0;
        for(int j = 0; j < s2->item_count; j++) {
            if(s1->items[i].prod_num == s2->items[j].prod_num &&
               s1->items[i].dot_pos == s2->items[j].dot_pos) {
                found = 1;
                break;
            }
        }
        if(!found) return 0;
    }
    return 1;
}

void construct_states() {
    // Initialize ACTION and GOTO tables with -1 (error)
    for(int i = 0; i < MAX_STATES; i++) {
        for(int j = 0; j < 256; j++) {
            action_table[i][j] = -1;
            goto_table[i][j] = -1;
        }
    }
    
    // State 0: S -> .start_symbol
    states[0].items[0].prod_num = 0;
    states[0].items[0].dot_pos = 0;
    states[0].item_count = 1;
    states[0].state_num = 0;
    closure(&states[0]);
    num_states = 1;
    
    // Generate all states
    for(int i = 0; i < num_states; i++) {
        // For each terminal
        for(int j = 0; j < num_terminals; j++) {
            if(terminals[j] != '$') {
                State new_state = go_to(&states[i], terminals[j]);
                if(new_state.item_count > 0) {
                    // Check if state already exists
                    int exists = -1;
                    for(int k = 0; k < num_states; k++) {
                        if(states_equal(&new_state, &states[k])) {
                            exists = k;
                            break;
                        }
                    }
                    
                    if(exists == -1) {
                        // New state
                        new_state.state_num = num_states;
                        states[num_states] = new_state;
                        action_table[i][terminals[j]] = num_states; // Shift
                        num_states++;
                    } else {
                        action_table[i][terminals[j]] = exists; // Shift
                    }
                }
            }
        }
        
        // For each non-terminal
        for(int j = 0; j < num_non_terminals; j++) {
            State new_state = go_to(&states[i], non_terminals[j]);
            if(new_state.item_count > 0) {
                // Check if state already exists
                int exists = -1;
                for(int k = 0; k < num_states; k++) {
                    if(states_equal(&new_state, &states[k])) {
                        exists = k;
                        break;
                    }
                }
                
                if(exists == -1) {
                    // New state
                    new_state.state_num = num_states;
                    states[num_states] = new_state;
                    goto_table[i][non_terminals[j]] = num_states;
                    num_states++;
                } else {
                    goto_table[i][non_terminals[j]] = exists;
                }
            }
        }
    }
}

void compute_follow_set(char symbol, char *follow_set) {
    strcpy(follow_set, "");
    
    // If it's the start symbol, add $
    if(symbol == start_symbol) {
        strcat(follow_set, "$");
    }
    
    // Look for the symbol in RHS of all productions
    for(int i = 0; i < num_productions; i++) {
        char *rhs = grammar[i].rhs;
        for(int j = 0; j < strlen(rhs); j++) {
            if(rhs[j] == symbol) {
                // Check what follows this symbol
                if(j + 1 < strlen(rhs)) {
                    char next = rhs[j + 1];
                    if(is_terminal(next)) {
                        // Add terminal to follow set if not already present
                        char temp[2] = {next, '\0'};
                        if(!strstr(follow_set, temp)) {
                            strcat(follow_set, temp);
                        }
                    }
                }
                
                // If symbol is at the end or followed by epsilon-producing symbols
                if(j + 1 >= strlen(rhs)) {
                    // Add FOLLOW of LHS (simplified - recursive case)
                    if(grammar[i].lhs != symbol) {
                        char lhs_follow[20];
                        compute_follow_set(grammar[i].lhs, lhs_follow);
                        for(int k = 0; k < strlen(lhs_follow); k++) {
                            char temp[2] = {lhs_follow[k], '\0'};
                            if(!strstr(follow_set, temp)) {
                                strcat(follow_set, temp);
                            }
                        }
                    }
                }
            }
        }
    }
}

void construct_slr_table() {
    // Add reduce actions
    for(int i = 0; i < num_states; i++) {
        for(int j = 0; j < states[i].item_count; j++) {
            Item *item = &states[i].items[j];
            Production *prod = &grammar[item->prod_num];
            
            // If dot is at the end (complete item)
            if(item->dot_pos == strlen(prod->rhs) || 
               (item->dot_pos == 1 && prod->rhs[0] == 'e')) {
                
                if(item->prod_num == 0) {
                    // Accept state
                    action_table[i]['$'] = -2; // Accept
                } else {
                    // Reduce action - add for all symbols in FOLLOW(LHS)
                    char follow_set[20];
                    compute_follow_set(prod->lhs, follow_set);
                    
                    for(int k = 0; k < strlen(follow_set); k++) {
                        action_table[i][follow_set[k]] = -(item->prod_num + 10); // Reduce
                    }
                }
            }
        }
    }
}

void print_states() {
    printf("LR(0) States:\n");
    printf("=============\n");
    for(int i = 0; i < num_states; i++) {
        printf("State %d:\n", i);
        for(int j = 0; j < states[i].item_count; j++) {
            Item *item = &states[i].items[j];
            Production *prod = &grammar[item->prod_num];
            printf("  %c -> ", prod->lhs);
            
            for(int k = 0; k < strlen(prod->rhs); k++) {
                if(k == item->dot_pos) printf(".");
                printf("%c", prod->rhs[k]);
            }
            if(item->dot_pos == strlen(prod->rhs)) printf(".");
            printf("\n");
        }
        printf("\n");
    }
}

void print_parse_table() {
    printf("SLR Parse Table:\n");
    printf("================\n\n");
    
    // Print header
    printf("State\t");
    for(int i = 0; i < num_terminals; i++) {
        printf("%c\t", terminals[i]);
    }
    for(int i = 0; i < num_non_terminals; i++) {
        if(non_terminals[i] != 'S') {  // Don't print augmented start symbol
            printf("%c\t", non_terminals[i]);
        }
    }
    printf("\n");
    
    // Print separator
    printf("-----\t");
    for(int i = 0; i < num_terminals + num_non_terminals - 1; i++) {
        printf("----\t");
    }
    printf("\n");
    
    // Print table
    for(int i = 0; i < num_states; i++) {
        printf("%d\t", i);
        
        // ACTION part
        for(int j = 0; j < num_terminals; j++) {
            int action = action_table[i][terminals[j]];
            if(action == -1) {
                printf("\t");
            } else if(action == -2) {
                printf("acc\t");
            } else if(action < -2) {
                printf("r%d\t", -(action + 10));
            } else {
                printf("s%d\t", action);
            }
        }
        
        // GOTO part
        for(int j = 0; j < num_non_terminals; j++) {
            if(non_terminals[j] != 'S') {
                int gt = goto_table[i][non_terminals[j]];
                if(gt == -1) {
                    printf("\t");
                } else {
                    printf("%d\t", gt);
                }
            }
        }
        printf("\n");
    }
}

int main() {
    input_grammar();
    print_grammar();
    find_symbols();
    
    printf("Terminals: ");
    for(int i = 0; i < num_terminals; i++) {
        printf("%c ", terminals[i]);
    }
    printf("\n");
    
    printf("Non-terminals: ");
    for(int i = 0; i < num_non_terminals; i++) {
        printf("%c ", non_terminals[i]);
    }
    printf("\n\n");
    
    construct_states();
    construct_slr_table();
    
    print_states();
    print_parse_table();
    
    // printf("\nSample Input Format:\n");
    // printf("Number of productions: 6\n");
    // printf("Start symbol: E\n");
    // printf("Productions:\n");
    // printf("E->E+T\n");
    // printf("E->T\n");
    // printf("T->T*F\n");
    // printf("T->F\n");
    // printf("F->(E)\n");
    // printf("F->i\n");
    
    return 0;
}

6
E
E->E+T
E->T
T->T*F
T->F
F->(E)
F->i








#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODS 20
#define MAX_PROD_LEN 20
#define MAX_STATES 50
#define MAX_ITEMS 100
#define MAX_SYMBOLS 20
#define STACK_SIZE 100

typedef struct {
    char lhs;
    char rhs[MAX_PROD_LEN];
} Production;

typedef struct {
    int prodIndex;
    int dotPos;
} Item;

typedef struct {
    Item items[MAX_ITEMS];
    int count;
} State;

Production prods[MAX_PRODS];
int prodCount = 0;

char terminals[MAX_SYMBOLS];
int termCount = 0;

char nonTerminals[MAX_SYMBOLS];
int nonTermCount = 0;

State states[MAX_STATES];
int stateCount = 0;

int actionTable[MAX_STATES][MAX_SYMBOLS]; // shift: positive state+1, reduce: -prodIndex-1, accept: -999, error: 0
int gotoTable[MAX_STATES][MAX_SYMBOLS];

int follow[MAX_SYMBOLS][MAX_SYMBOLS]; // FOLLOW sets

// Utility functions
int isTerminal(char c) {
    for(int i=0; i<termCount; i++)
        if(terminals[i] == c) return 1;
    return 0;
}

int isNonTerminal(char c) {
    for(int i=0; i<nonTermCount; i++)
        if(nonTerminals[i] == c) return 1;
    return 0;
}

int indexOfTerminal(char c) {
    for(int i=0; i<termCount; i++)
        if(terminals[i] == c) return i;
    return -1;
}

int indexOfNonTerminal(char c) {
    for(int i=0; i<nonTermCount; i++)
        if(nonTerminals[i] == c) return i;
    return -1;
}

void addTerminal(char c) {
    if(c == ' ' || c == '\t') return;
    if(!isTerminal(c) && !isNonTerminal(c)) {
        terminals[termCount++] = c;
    }
}

void addNonTerminal(char c) {
    if(!isNonTerminal(c)) {
        nonTerminals[nonTermCount++] = c;
    }
}

int prodLength(int p) {
    return strlen(prods[p].rhs);
}

int itemsEqual(Item a, Item b) {
    return (a.prodIndex == b.prodIndex) && (a.dotPos == b.dotPos);
}

int stateContainsItem(State *s, Item it) {
    for(int i=0; i<s->count; i++)
        if(itemsEqual(s->items[i], it)) return 1;
    return 0;
}

int statesEqual(State *a, State *b) {
    if(a->count != b->count) return 0;
    for(int i=0; i<a->count; i++) {
        if(!stateContainsItem(b, a->items[i])) return 0;
    }
    return 1;
}

int findState(State *s) {
    for(int i=0; i<stateCount; i++) {
        if(statesEqual(&states[i], s)) return i;
    }
    return -1;
}

void addItem(State *s, Item it) {
    if(!stateContainsItem(s, it)) {
        s->items[s->count++] = it;
    }
}

// Compute closure of LR(0) items for a state
void closure(State *s) {
    int added;
    do {
        added = 0;
        for(int i=0; i<s->count; i++) {
            Item it = s->items[i];
            Production p = prods[it.prodIndex];
            if(it.dotPos < prodLength(it.prodIndex)) {
                char B = p.rhs[it.dotPos];
                if(isNonTerminal(B)) {
                    for(int j=0; j<prodCount; j++) {
                        if(prods[j].lhs == B) {
                            Item newItem = {j, 0};
                            if(!stateContainsItem(s, newItem)) {
                                s->items[s->count++] = newItem;
                                added = 1;
                            }
                        }
                    }
                }
            }
        }
    } while(added);
}

// GOTO function: compute next state on symbol X from state s
void goTo(State *from, char X, State *to) {
    to->count = 0;
    for(int i=0; i<from->count; i++) {
        Item it = from->items[i];
        Production p = prods[it.prodIndex];
        if(it.dotPos < prodLength(it.prodIndex) && p.rhs[it.dotPos] == X) {
            Item newItem = {it.prodIndex, it.dotPos + 1};
            addItem(to, newItem);
        }
    }
    closure(to);
}

// Compute FOLLOW sets for SLR
void computeFollow() {
    for(int i=0; i<nonTermCount; i++)
        for(int j=0; j<termCount; j++)
            follow[i][j] = 0;

    // Add $ to FOLLOW of start symbol (augmented start is nonTerminals[nonTermCount-1] = 'Z')
    int startIdx = indexOfNonTerminal('Z');
    int dollarIdx = indexOfTerminal('$');
    if(startIdx != -1 && dollarIdx != -1)
        follow[startIdx][dollarIdx] = 1;

    int changed;
    do {
        changed = 0;
        for(int i=0; i<prodCount; i++) {
            char A = prods[i].lhs;
            int A_idx = indexOfNonTerminal(A);
            char *rhs = prods[i].rhs;
            int len = strlen(rhs);

            for(int pos=0; pos<len; pos++) {
                char B = rhs[pos];
                if(isNonTerminal(B)) {
                    int B_idx = indexOfNonTerminal(B);
                    if(pos+1 < len) {
                        char beta = rhs[pos+1];
                        if(isTerminal(beta)) {
                            int t_idx = indexOfTerminal(beta);
                            if(follow[B_idx][t_idx] == 0) {
                                follow[B_idx][t_idx] = 1;
                                changed = 1;
                            }
                        } else if(isNonTerminal(beta)) {
                            int beta_idx = indexOfNonTerminal(beta);
                            for(int t=0; t<termCount; t++) {
                                if(follow[beta_idx][t]) {
                                    if(follow[B_idx][t] == 0) {
                                        follow[B_idx][t] = 1;
                                        changed = 1;
                                    }
                                }
                            }
                        }
                    } else {
                        for(int t=0; t<termCount; t++) {
                            if(follow[A_idx][t]) {
                                if(follow[B_idx][t] == 0) {
                                    follow[B_idx][t] = 1;
                                    changed = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    } while(changed);
}

// Helper to print stack content
void printStack(int *stack, int top) {
    printf("Stack: ");
    for(int i=0; i<=top; i++) {
        printf("%d ", stack[i]);
    }
}

// Main LR parsing function
void parseInput(char *input) {
    int stack[STACK_SIZE];
    int top = 0;
    stack[0] = 0;  // initial state

    int ip = 0; // input pointer

    printf("\nParsing steps:\n");
    printf("%-20s %-15s %-20s\n", "Stack", "Input", "Action");

    while(1) {
        int state = stack[top];
        char a = input[ip];
        int aIdx = indexOfTerminal(a);
        if(aIdx == -1) {
            printf("Error: Unknown input symbol '%c'\n", a);
            return;
        }

        int action = actionTable[state][aIdx];

        // Print stack and input
        printf("%-20s %-15s ", "", &input[ip]);
        // Print stack
        printf("\r");
        printStack(stack, top);
        printf(" ");

        if(action == 0) {
            printf("Error: No action defined.\n");
            return;
        }
        else if(action == -999) {
            printf("Accept\n");
            return;
        }
        else if(action > 0) {
            // Shift
            printf("Shift %d\n", action-1);
            stack[++top] = aIdx + 1000; // store symbol (offset 1000 to separate symbol and state)
            stack[++top] = action - 1;
            ip++;
        }
        else {
            // Reduce
            int prodIndex = -action - 1;
            Production p = prods[prodIndex];
            int rhsLen = strlen(p.rhs);

            printf("Reduce by %c->%s\n", p.lhs, p.rhs);

            // Pop 2*rhsLen symbols/states from stack
            for(int i=0; i<rhsLen*2; i++) {
                if(top >= 0) top--;
                else {
                    printf("Error: Stack underflow during reduce\n");
                    return;
                }
            }

            int currState = stack[top];
            int lhsIdx = indexOfNonTerminal(p.lhs);
            if(lhsIdx == -1) {
                printf("Error: Non-terminal not found in goto table\n");
                return;
            }

            int gotoState = gotoTable[currState][lhsIdx];
            if(gotoState == -1) {
                printf("Error: No goto state\n");
                return;
            }

            stack[++top] = lhsIdx + 1000;  // push lhs symbol
            stack[++top] = gotoState;      // push goto state
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &prodCount);
    getchar();

    for(int i=0; i<prodCount; i++) {
        char line[100];
        printf("Enter production %d: ", i+1);
        fgets(line, sizeof(line), stdin);

        char *arrow = strstr(line, "->");
        if(!arrow) {
            printf("Invalid production format\n");
            i--;
            continue;
        }
        prods[i].lhs = line[0];
        strcpy(prods[i].rhs, arrow + 2);
        int len = strlen(prods[i].rhs);
        if(prods[i].rhs[len-1] == '\n') prods[i].rhs[len-1] = '\0';

        addNonTerminal(prods[i].lhs);
        for(int j=0; prods[i].rhs[j]; j++) {
            char c = prods[i].rhs[j];
            if(isupper(c)) addNonTerminal(c);
            else addTerminal(c);
        }
    }

    // Add augmented production S'->S with new start symbol Z
    Production augmented = {'Z'};
    augmented.rhs[0] = prods[0].lhs;
    augmented.rhs[1] = '\0';
    prods[prodCount++] = augmented;
    addNonTerminal('Z');
    addTerminal('$');

    // Create initial state I0 = closure({Z->.S})
    State I0;
    I0.count = 1;
    I0.items[0].prodIndex = prodCount - 1;
    I0.items[0].dotPos = 0;
    closure(&I0);

    states[0] = I0;
    stateCount = 1;

    // Construct canonical collection of LR(0) items
    int changed;
    do {
        changed = 0;
        for(int i=0; i<stateCount; i++) {
            State s = states[i];
            for(int j=0; j<termCount + nonTermCount; j++) {
                char X = (j < termCount) ? terminals[j] : nonTerminals[j - termCount];
                State g;
                goTo(&s, X, &g);
                if(g.count > 0) {
                    if(findState(&g) == -1) {
                        states[stateCount++] = g;
                        changed = 1;
                    }
                }
            }
        }
    } while(changed);

    // Initialize tables
    for(int i=0; i<stateCount; i++) {
        for(int j=0; j<termCount; j++) actionTable[i][j] = 0;
        for(int j=0; j<nonTermCount; j++) gotoTable[i][j] = -1;
    }

    computeFollow();

    // Build ACTION and GOTO tables
    for(int i=0; i<stateCount; i++) {
        State *s = &states[i];
        for(int k=0; k<s->count; k++) {
            Item it = s->items[k];
            Production p = prods[it.prodIndex];

            if(it.dotPos < prodLength(it.prodIndex)) {
                char a = p.rhs[it.dotPos];
                if(isTerminal(a)) {
                    State g;
                    goTo(s, a, &g);
                    int t = findState(&g);
                    if(t != -1) {
                        int aIdx = indexOfTerminal(a);
                        actionTable[i][aIdx] = t+1; // shift
                    }
                }
            } else {
                if(p.lhs == 'Z') {
                    int dollarIdx = indexOfTerminal('$');
                    actionTable[i][dollarIdx] = -999; // accept
                } else {
                    int lhsIdx = indexOfNonTerminal(p.lhs);
                    for(int t=0; t<termCount; t++) {
                        if(follow[lhsIdx][t]) {
                            if(actionTable[i][t] != 0) {
                                // Conflicts are not handled here
                            }
                            actionTable[i][t] = -(it.prodIndex + 1); // reduce
                        }
                    }
                }
            }
        }
        for(int j=0; j<nonTermCount; j++) {
            State g;
            goTo(s, nonTerminals[j], &g);
            if(g.count > 0) {
                int st = findState(&g);
                if(st != -1) gotoTable[i][j] = st;
            }
        }
    }

    // Print ACTION and GOTO table (optional)
    printf("\nSLR Parse Table\n");
    printf("States |");
    for(int i=0; i<termCount; i++) printf("  %c  |", terminals[i]);
    printf(" || ");
    for(int i=0; i<nonTermCount; i++) printf("  %c  |", nonTerminals[i]);
    printf("\n---------------------------------------------------------\n");

    for(int i=0; i<stateCount; i++) {
        printf("  %2d   |", i);
        for(int j=0; j<termCount; j++) {
            int val = actionTable[i][j];
            if(val == 0) printf("     |");
            else if(val == -999) printf(" acc |");
            else if(val > 0) printf(" s%-3d|", val-1);
            else printf(" r%-3d|", -val - 1);
        }
        printf(" || ");
        for(int j=0; j<nonTermCount; j++) {
            if(gotoTable[i][j] == -1) printf("     |");
            else printf("  %2d |", gotoTable[i][j]);
        }
        printf("\n");
    }

    char input[100];
    printf("\nEnter input string to parse (append '$' at end): ");
    fgets(input, sizeof(input), stdin);
    int len = strlen(input);
    if(input[len-1] == '\n') input[len-1] = '\0';

    parseInput(input);

    return 0;
}
6
E
E->E+T
E->T
T->T*F
T->F
F->(E)
F->i
i+i*i$
