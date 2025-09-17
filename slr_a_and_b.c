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
    printf("SLR Parse Table Construction\n");
    printf("============================\n\n");
    
    printf("Enter the number of productions: ");
    scanf("%d", &num_productions);
    
    printf("Enter the start symbol: ");
    scanf(" %c", &start_symbol);
    
    // Create augmented grammar
    grammar[0].lhs = 'S';  // Augmented start symbol
    grammar[0].rhs[0] = start_symbol;
    grammar[0].rhs[1] = '\0';
    
    printf("\nEnter the productions (format: A->BC or A->a):\n");
    printf("Use 'e' for epsilon productions\n");
    printf("Use single characters for symbols\n\n");
    
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
    
    printf("\nSample Input Format:\n");
    printf("Number of productions: 6\n");
    printf("Start symbol: E\n");
    printf("Productions:\n");
    printf("E->E+T\n");
    printf("E->T\n");
    printf("T->T*F\n");
    printf("T->F\n");
    printf("F->(E)\n");
    printf("F->i\n");
    
    return 0;
}










#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK 100
#define MAX_INPUT 100
#define MAX_RULES 50

// Grammar productions
typedef struct {
    char lhs;
    char rhs[15];
    int rhs_len;
} Production;

// Stack for parsing
typedef struct {
    int data[MAX_STACK];
    int top;
} Stack;

// Global variables
Production grammar[MAX_RULES];
int num_productions = 0;
int action_table[100][256];  // ACTION table
int goto_table[100][256];    // GOTO table
char terminals[20];
char non_terminals[20];
int num_terminals = 0, num_non_terminals = 0;
int num_states = 0;

void input_grammar_and_table() {
    printf("SLR Parser Implementation\n");
    printf("=========================\n\n");
    
    printf("Enter the number of productions: ");
    scanf("%d", &num_productions);
    
    printf("\nEnter the productions (format: A->BC):\n");
    printf("Production 0 should be the augmented production (S'->S)\n");
    
    for(int i = 0; i < num_productions; i++) {
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
        grammar[i].rhs_len = strlen(grammar[i].rhs);
        
        // Handle epsilon productions
        if(strcmp(grammar[i].rhs, "e") == 0) {
            grammar[i].rhs_len = 0;
        }
    }
    
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
            
            if(!is_nt && sym != 'e') {
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
    
    printf("\nEnter the number of states in the parse table: ");
    scanf("%d", &num_states);
    
    // Initialize tables
    for(int i = 0; i < num_states; i++) {
        for(int j = 0; j < 256; j++) {
            action_table[i][j] = -1;  // Error
            goto_table[i][j] = -1;    // Error
        }
    }
    
    printf("\nEnter the ACTION table:\n");
    printf("Format: state terminal action (e.g., 0 i s5, 1 $ acc, 2 + r3)\n");
    printf("Use 'done' to finish entering ACTION table\n");
    
    char input[20];
    while(1) {
        printf("ACTION entry: ");
        scanf("%s", input);
        if(strcmp(input, "done") == 0) break;
        
        int state = atoi(input);
        char terminal;
        char action[10];
        scanf(" %c %s", &terminal, action);
        
        if(strcmp(action, "acc") == 0) {
            action_table[state][terminal] = -2;  // Accept
        } else if(action[0] == 's') {
            int shift_state = atoi(action + 1);
            action_table[state][terminal] = shift_state;  // Shift
        } else if(action[0] == 'r') {
            int reduce_prod = atoi(action + 1);
            action_table[state][terminal] = -(reduce_prod + 10);  // Reduce
        }
    }
    
    printf("\nEnter the GOTO table:\n");
    printf("Format: state nonterminal state (e.g., 0 E 1)\n");
    printf("Use 'done' to finish entering GOTO table\n");
    
    while(1) {
        printf("GOTO entry: ");
        scanf("%s", input);
        if(strcmp(input, "done") == 0) break;
        
        int state = atoi(input);
        char nonterminal;
        int goto_state;
        scanf(" %c %d", &nonterminal, &goto_state);
        
        goto_table[state][nonterminal] = goto_state;
    }
}

// Stack operations
void init_stack(Stack *s) {
    s->top = -1;
}

void push(Stack *s, int val) {
    if(s->top < MAX_STACK - 1) {
        s->data[++s->top] = val;
    }
}

int pop(Stack *s) {
    if(s->top >= 0) {
        return s->data[s->top--];
    }
    return -1;
}

int top(Stack *s) {
    if(s->top >= 0) {
        return s->data[s->top];
    }
    return -1;
}

void print_stack(Stack *s) {
    printf("[");
    for(int i = 0; i <= s->top; i++) {
        printf("%d", s->data[i]);
        if(i < s->top) printf(" ");
    }
    printf("]");
}

void print_step(int step, Stack *s, char *input, int input_pos, char *action) {
    printf("%2d\t", step);
    print_stack(s);
    printf("\t\t%s\t\t%s\n", input + input_pos, action);
}

int slr_parse(char *input) {
    Stack state_stack;
    Stack symbol_stack;
    init_stack(&state_stack);
    init_stack(&symbol_stack);
    
    // Add input end marker
    int len = strlen(input);
    input[len] = '$';
    input[len + 1] = '\0';
    
    // Initialize
    push(&state_stack, 0);
    int input_pos = 0;
    int step = 1;
    
    printf("\nSLR Parsing Steps:\n");
    printf("==================\n");
    printf("Step\tStack\t\t\tInput\t\t\tAction\n");
    printf("----\t-----\t\t\t-----\t\t\t------\n");
    
    while(1) {
        int current_state = top(&state_stack);
        char current_input = input[input_pos];
        
        int action = action_table[current_state][current_input];
        char action_str[50];
        
        if(action == -1) {
            sprintf(action_str, "ERROR");
            print_step(step++, &state_stack, input, input_pos, action_str);
            printf("\nParsing FAILED: Syntax Error\n");
            return 0;
        }
        else if(action == -2) {
            sprintf(action_str, "ACCEPT");
            print_step(step++, &state_stack, input, input_pos, action_str);
            printf("\nParsing SUCCESSFUL!\n");
            return 1;
        }
        else if(action > 0) {
            // Shift action
            sprintf(action_str, "Shift %d", action);
            print_step(step++, &state_stack, input, input_pos, action_str);
            
            push(&state_stack, action);
            push(&symbol_stack, current_input);
            input_pos++;
        }
        else {
            // Reduce action
            int prod_num = -(action + 10);
            Production *prod = &grammar[prod_num];
            sprintf(action_str, "Reduce by %c->%s", prod->lhs, prod->rhs);
            print_step(step++, &state_stack, input, input_pos, action_str);
            
            // Pop symbols and states
            for(int i = 0; i < prod->rhs_len; i++) {
                pop(&state_stack);
                pop(&symbol_stack);
            }
            
            // Get goto state
            int goto_state = top(&state_stack);
            int next_state = goto_table[goto_state][prod->lhs];
            
            if(next_state == -1) {
                printf("Error: Invalid GOTO transition\n");
                return 0;
            }
            
            push(&state_stack, next_state);
            push(&symbol_stack, prod->lhs);
        }
    }
}

void print_parse_table() {
    printf("\nSLR Parse Table:\n");
    printf("================\n\n");
    
    printf("ACTION Table:\n");
    printf("State\t");
    for(int i = 0; i < num_terminals; i++) {
        printf("%c\t", terminals[i]);
    }
    printf("\n-----\t");
    for(int i = 0; i < num_terminals; i++) {
        printf("----\t");
    }
    printf("\n");
    
    for(int i = 0; i < num_states; i++) {
        printf("%d\t", i);
        for(int j = 0; j < num_terminals; j++) {
            int action = action_table[i][terminals[j]];
            if(action == -1) {
                printf("\t");
            } else if(action == -2) {
                printf("acc\t");
            } else if(action > 0) {
                printf("s%d\t", action);
            } else {
                printf("r%d\t", -(action + 10));
            }
        }
        printf("\n");
    }
    
    printf("\nGOTO Table:\n");
    printf("State\t");
    for(int i = 0; i < num_non_terminals; i++) {
        if(non_terminals[i] != grammar[0].lhs) { // Skip augmented start symbol
            printf("%c\t", non_terminals[i]);
        }
    }
    printf("\n-----\t");
    for(int i = 0; i < num_non_terminals - 1; i++) {
        printf("----\t");
    }
    printf("\n");
    
    for(int i = 0; i < num_states; i++) {
        printf("%d\t", i);
        for(int j = 0; j < num_non_terminals; j++) {
            if(non_terminals[j] != grammar[0].lhs) {
                if(goto_table[i][non_terminals[j]] == -1) {
                    printf("\t");
                } else {
                    printf("%d\t", goto_table[i][non_terminals[j]]);
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

void print_grammar() {
    printf("\nGrammar:\n");
    printf("========\n");
    for(int i = 0; i < num_productions; i++) {
        printf("%d. %c -> %s\n", i, grammar[i].lhs, grammar[i].rhs);
    }
    printf("\n");
}

int main() {
    input_grammar_and_table();
    print_grammar();
    print_parse_table();
    
    char input[MAX_INPUT];
    
    // Interactive mode
    printf("Interactive Parsing Mode\n");
    printf("========================\n");
    printf("Enter input string to parse (or 'quit' to exit):\n");
    
    while(1) {
        printf("\nInput: ");
        scanf("%s", input);
        
        if(strcmp(input, "quit") == 0) {
            break;
        }
        
        slr_parse(input);
    }
    
    printf("\nSample Input Format:\n");
    printf("====================\n");
    printf("Number of productions: 7\n");
    printf("Productions:\n");
    printf("S->E\n");
    printf("E->E+T\n");
    printf("E->T\n");
    printf("T->T*F\n");
    printf("T->F\n");
    printf("F->(E)\n");
    printf("F->i\n");
    printf("\nNumber of states: 12\n");
    printf("\nACTION table entries:\n");
    printf("0 i s5\n");
    printf("0 ( s4\n");
    printf("1 + s6\n");
    printf("1 $ acc\n");
    printf("... (continue with all ACTION entries)\n");
    printf("done\n");
    printf("\nGOTO table entries:\n");
    printf("0 E 1\n");
    printf("0 T 2\n");
    printf("0 F 3\n");
    printf("... (continue with all GOTO entries)\n");
    printf("done\n");
    
    return 0;
}
