// 11.a
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <queue>
#include <iomanip>  // For setw

using namespace std;

struct Production {
    char lhs;
    string rhs;
};

struct Item {
    int prodIndex;
    int dotPos;
    set<char> lookahead;

    bool operator<(const Item& other) const {
        if (prodIndex != other.prodIndex)
            return prodIndex < other.prodIndex;
        if (dotPos != other.dotPos)
            return dotPos < other.dotPos;
        return lookahead < other.lookahead;
    }

    bool coreEquals(const Item& other) const {
        return prodIndex == other.prodIndex && dotPos == other.dotPos;
    }
};

struct State {
    set<Item> items;

    bool operator<(const State& other) const {
        return items < other.items;
    }
};

vector<Production> productions;
set<char> terminals;
set<char> nonTerminals;
char startSymbol;

map<char, set<char>> firstSets;

int prodCount;

// Helpers to check terminal/non-terminal
bool isTerminal(char c) {
    return terminals.count(c) > 0;
}

bool isNonTerminal(char c) {
    return nonTerminals.count(c) > 0;
}

// Compute FIRST sets for all symbols
void computeFirst() {
    // Initialize FIRST sets for terminals
    for (char t : terminals) {
        firstSets[t].insert(t);
    }

    bool changed;
    do {
        changed = false;
        for (auto &p : productions) {
            char A = p.lhs;
            string rhs = p.rhs;

            for (size_t i = 0; i < rhs.size(); ++i) {
                char X = rhs[i];
                size_t before = firstSets[A].size();
                for (char c : firstSets[X]) {
                    if (c != '#') firstSets[A].insert(c);
                }
                if (firstSets[X].count('#') == 0) break; // No epsilon
                if (i == rhs.size() - 1) firstSets[A].insert('#'); // epsilon at end
                if (firstSets[A].size() != before) changed = true;
            }
        }
    } while (changed);
}

// Compute FIRST of a string (used for lookahead calculation)
set<char> firstOfString(const string &s) {
    set<char> result;
    bool epsilonPossible = true;
    for (char c : s) {
        for (char f : firstSets[c]) {
            if (f != '#') result.insert(f);
        }
        if (firstSets[c].count('#') == 0) {
            epsilonPossible = false;
            break;
        }
    }
    if (epsilonPossible) result.insert('#');
    return result;
}

// Closure of LR(1) items
set<Item> closure(const set<Item> &items) {
    set<Item> closureSet = items;
    bool changed;
    do {
        changed = false;
        set<Item> newItems;
        for (auto &item : closureSet) {
            if (item.dotPos >= (int)productions[item.prodIndex].rhs.size()) continue;
            char B = productions[item.prodIndex].rhs[item.dotPos];
            if (!isNonTerminal(B)) continue;

            // Compute lookahead for new items
            string beta_a = "";
            if (item.dotPos + 1 < (int)productions[item.prodIndex].rhs.size())
                beta_a = productions[item.prodIndex].rhs.substr(item.dotPos + 1);
            for (char la : item.lookahead)
                beta_a += la;

            set<char> look = firstOfString(beta_a);

            for (int i = 0; i < prodCount; ++i) {
                if (productions[i].lhs == B) {
                    Item newItem;
                    newItem.prodIndex = i;
                    newItem.dotPos = 0;
                    for (char c : look) {
                        if (c != '#') newItem.lookahead.insert(c);
                    }
                    // Insert or merge lookahead
                    auto it = closureSet.find(newItem);
                    if (it == closureSet.end()) {
                        newItems.insert(newItem);
                        changed = true;
                    } else {
                        // merge lookahead sets
                        Item merged = *it;
                        size_t oldSize = merged.lookahead.size();
                        merged.lookahead.insert(newItem.lookahead.begin(), newItem.lookahead.end());
                        if (merged.lookahead.size() > oldSize) {
                            closureSet.erase(it);
                            closureSet.insert(merged);
                            changed = true;
                        }
                    }
                }
            }
        }
        closureSet.insert(newItems.begin(), newItems.end());
    } while (changed);
    return closureSet;
}

// GOTO function for LR(1)
set<Item> goTo(const set<Item> &I, char X) {
    set<Item> gotoSet;
    for (auto &item : I) {
        if (item.dotPos < (int)productions[item.prodIndex].rhs.size()
            && productions[item.prodIndex].rhs[item.dotPos] == X) {
            Item moved = item;
            moved.dotPos++;
            gotoSet.insert(moved);
        }
    }
    return closure(gotoSet);
}

// Compare cores of states for merging LALR
bool coresEqual(const set<Item> &a, const set<Item> &b) {
    if (a.size() != b.size()) return false;
    auto itA = a.begin();
    auto itB = b.begin();
    while (itA != a.end()) {
        if (!itA->coreEquals(*itB)) return false;
        ++itA; ++itB;
    }
    return true;
}

// Merge lookaheads for LALR states
set<Item> mergeItems(const set<Item> &a, const set<Item> &b) {
    set<Item> merged;
    for (auto &itemA : a) {
        Item mergedItem = itemA;
        for (auto &itemB : b) {
            if (itemA.coreEquals(itemB)) {
                mergedItem.lookahead.insert(itemB.lookahead.begin(), itemB.lookahead.end());
            }
        }
        merged.insert(mergedItem);
    }
    return merged;
}

int main() {
    cout << "Enter number of productions: ";
    cin >> prodCount;
    cin.ignore();

    productions.resize(prodCount);
    cout << "Enter productions (e.g., S->CC):\n";
    for (int i = 0; i < prodCount; i++) {
        string prodLine;
        getline(cin, prodLine);
        // parse lhs and rhs
        int arrowPos = prodLine.find("->");
        if (arrowPos == string::npos || arrowPos == 0 || arrowPos + 2 > (int)prodLine.size()) {
            cout << "Invalid production format. Try again.\n";
            i--;
            continue;
        }
        productions[i].lhs = prodLine[0];
        productions[i].rhs = prodLine.substr(arrowPos + 2);

        // Add terminals/non-terminals
        if (i == 0) startSymbol = productions[i].lhs;
        nonTerminals.insert(productions[i].lhs);
    }

    // Identify terminals
    for (auto &p : productions) {
        for (char c : p.rhs) {
            if (!isupper(c) && c != '#') terminals.insert(c);
        }
    }
    terminals.insert('$'); // End marker

    // Add augmented production S'->S
    productions.push_back({(char)(startSymbol + 1), string(1, startSymbol)});
    nonTerminals.insert((char)(startSymbol + 1));
    prodCount++;

    computeFirst();

    // Create initial item (S' -> .S, lookahead $)
    Item startItem;
    startItem.prodIndex = prodCount - 1;
    startItem.dotPos = 0;
    startItem.lookahead.insert('$');

    set<Item> I0 = closure({startItem});

    // Canonical collection of LR(1) items
    vector<set<Item>> C;
    C.push_back(I0);

    map<set<Item>, int> stateIds;
    stateIds[I0] = 0;

    queue<int> q;
    q.push(0);

    // Collect all grammar symbols
    vector<char> grammarSymbols;
    for (char t : terminals) grammarSymbols.push_back(t);
    for (char nt : nonTerminals) grammarSymbols.push_back(nt);

    while (!q.empty()) {
        int i = q.front(); q.pop();
        for (char X : grammarSymbols) {
            set<Item> g = goTo(C[i], X);
            if (g.empty()) continue;
            if (stateIds.find(g) == stateIds.end()) {
                stateIds[g] = (int)C.size();
                C.push_back(g);
                q.push(stateIds[g]);
            }
        }
    }

    // Merge states with same cores (LALR states)
    vector<set<Item>> lalrStates;
    vector<int> mapping(C.size(), -1);

    for (int i = 0; i < (int)C.size(); ++i) {
        bool merged = false;
        for (int j = 0; j < (int)lalrStates.size(); ++j) {
            if (coresEqual(C[i], lalrStates[j])) {
                lalrStates[j] = mergeItems(lalrStates[j], C[i]);
                mapping[i] = j;
                merged = true;
                break;
            }
        }
        if (!merged) {
            lalrStates.push_back(C[i]);
            mapping[i] = (int)lalrStates.size() - 1;
        }
    }

    // Build LALR parse table
    int nStates = (int)lalrStates.size();

    map<char, int> termIndex, nonTermIndex;
    int tIdx = 0, ntIdx = 0;
    for (char t : terminals) termIndex[t] = tIdx++;
    for (char nt : nonTerminals) nonTermIndex[nt] = ntIdx++;

    vector<map<char, string>> action(nStates);
    vector<map<char, int>> goToTable(nStates);

    for (int i = 0; i < (int)C.size(); ++i) {
        int state = mapping[i];
        for (auto &item : C[i]) {
            if (item.dotPos < (int)productions[item.prodIndex].rhs.size()) {
                char a = productions[item.prodIndex].rhs[item.dotPos];
                if (isTerminal(a)) {
                    set<Item> g = goTo(C[i], a);
                    if (!g.empty()) {
                        int nextState = mapping[stateIds[g]];
                        action[state][a] = "s" + to_string(nextState);
                    }
                }
            } else {
                // At end of production, reduce
                if (productions[item.prodIndex].lhs == (char)(startSymbol + 1)) {
                    // Accept
                    if (item.lookahead.count('$') > 0)
                        action[state]['$'] = "acc";
                } else {
                    for (char la : item.lookahead) {
                        action[state][la] = "r" + to_string(item.prodIndex);
                    }
                }
            }
        }

        // GOTO entries
        for (char nt : nonTerminals) {
            set<Item> g = goTo(lalrStates[state], nt);
            if (!g.empty()) {
                int nextState = mapping[stateIds[g]];
                goToTable[state][nt] = nextState;
            }
        }
    }

    // Prepare terminal and non-terminal vectors in order for printing
    vector<char> termVec(terminals.begin(), terminals.end());
    vector<char> nonTermVec(nonTerminals.begin(), nonTerminals.end());
    sort(termVec.begin(), termVec.end());
    sort(nonTermVec.begin(), nonTermVec.end());

    // Print combined ACTION + GOTO table header
    cout << "\nACTION and GOTO tables:\n";

    // Print header row
    cout << setw(6) << "State" << " |";
    for (char t : termVec) cout << setw(5) << t << " |";
    cout << "  ||";
    for (char nt : nonTermVec) cout << setw(4) << nt << " |";
    cout << "\n";

    // Print separator line
    int totalWidth = 6 + 2 + (int)termVec.size() * 6 + 4 + (int)nonTermVec.size() * 6;
    for (int i = 0; i < totalWidth; ++i) cout << "-";
    cout << "\n";

    // Print rows
    for (int i = 0; i < nStates; ++i) {
        cout << setw(6) << i << " |";
        for (char t : termVec) {
            if (action[i].count(t))
                cout << setw(5) << action[i][t] << " |";
            else
                cout << setw(5) << " " << " |";
        }
        cout << "  ||";
        for (char nt : nonTermVec) {
            if (goToTable[i].count(nt))
                cout << setw(4) << goToTable[i][nt] << " |";
            else
                cout << setw(4) << " " << " |";
        }
        cout << "\n";
    }

    return 0;
}

3
S->CC
C->cC
C->d

STDIN
Output:

Enter number of productions: Enter productions (e.g., S->CC):

ACTION and GOTO tables:
 State |    $ |    c |    d |  ||   C |   S |   T |
------------------------------------------------
     0 |      |   s1 |   s2 |  ||   3 |   4 |     |
     1 |      |   s1 |   s2 |  ||   0 |     |     |
     2 |   r2 |   r2 |   r2 |  ||     |     |     |
     3 |      |   s1 |   s2 |  ||   6 |     |     |
     4 |  acc |      |      |  ||     |     |     |
     5 |   r1 |   r1 |   r1 |  ||     |     |     |
     6 |   r0 |      |      |  ||     |     |     |







//11.b
   #include <bits/stdc++.h>
using namespace std;

// Structure to hold a production rule
struct Production {
    char lhs;
    string rhs;
};

int main() {
    int num_states, num_terminals, num_non_terminals;
    cin >> num_states >> num_terminals;

    vector<char> terminals(num_terminals);
    for (int i = 0; i < num_terminals; i++) {
        cin >> terminals[i];
    }

    cin >> num_non_terminals;
    vector<char> non_terminals(num_non_terminals);
    for (int i = 0; i < num_non_terminals; i++) {
        cin >> non_terminals[i];
    }

    // Read productions
    int num_productions;
    cin >> num_productions;
    vector<Production> productions(num_productions + 1); // 1-based indexing

    for (int i = 1; i <= num_productions; i++) {
        string prod_str;
        cin >> prod_str;  // format: A->alpha
        productions[i].lhs = prod_str[0];
        productions[i].rhs = prod_str.substr(3);
    }

    // ACTION table: states x terminals (strings)
    vector<vector<string>> action_table(num_states, vector<string>(num_terminals));
    for (int i = 0; i < num_states; i++) {
        for (int j = 0; j < num_terminals; j++) {
            cin >> action_table[i][j];
        }
    }

    // GOTO table: states x non-terminals (integers)
    vector<vector<int>> goto_table(num_states, vector<int>(num_non_terminals));
    for (int i = 0; i < num_states; i++) {
        for (int j = 0; j < num_non_terminals; j++) {
            cin >> goto_table[i][j];
        }
    }

    string input_str;
    cin >> input_str;
    input_str += "$"; // End marker

    stack<int> state_stack;
    stack<char> symbol_stack;
    state_stack.push(0);

    int ip = 0;
    bool accepted = false;

    // Helper to get terminal index
    auto get_terminal_index = [&](char c) -> int {
        for (int i = 0; i < num_terminals; i++) {
            if (terminals[i] == c) return i;
        }
        return -1; // Not found
    };

    // Function to print stack trace
    auto print_trace = [&](string action) {
        // Print state stack
        stack<int> tmp_state = state_stack;
        vector<int> states;
        while (!tmp_state.empty()) {
            states.push_back(tmp_state.top());
            tmp_state.pop();
        }
        reverse(states.begin(), states.end());

        // Print symbol stack
        stack<char> tmp_sym = symbol_stack;
        vector<char> syms;
        while (!tmp_sym.empty()) {
            syms.push_back(tmp_sym.top());
            tmp_sym.pop();
        }
        reverse(syms.begin(), syms.end());

        cout << "States: ";
        for (auto s : states) cout << s << " ";
        cout << " | Symbols: ";
        for (auto c : syms) cout << c;
        cout << " | Input: " << input_str.substr(ip);
        cout << " | Action: " << action << "\n";
    };

    while (true) {
        int state = state_stack.top();
        char current_input = input_str[ip];

        int term_index = get_terminal_index(current_input);
        if (term_index == -1) {
            cout << "Error: Unexpected symbol '" << current_input << "'\n";
            break;
        }

        string action = action_table[state][term_index];
        print_trace(action);  // print step trace

        if (action == "-" || action == "0") {
            cout << "Error: No action for state " << state << " and input '" << current_input << "'\n";
            break;
        }
        else if (action == "acc") {
            cout << "Input string accepted.\n";
            accepted = true;
            break;
        }
        else if (action[0] == 's') {
            // Shift
            int next_state = stoi(action.substr(1));
            symbol_stack.push(current_input);
            state_stack.push(next_state);
            ip++;
        }
        else if (action[0] == 'r') {
            // Reduce by production number
            int prod_num = stoi(action.substr(1));
            Production &prod = productions[prod_num];

            // Pop |RHS| symbols and states
            for (int i = 0; i < (int)prod.rhs.size(); i++) {
                if (!symbol_stack.empty()) symbol_stack.pop();
                if (!state_stack.empty()) state_stack.pop();
            }

            int top_state = state_stack.top();
            symbol_stack.push(prod.lhs);

            // GOTO from top_state and LHS
            int nt_index = -1;
            for (int i = 0; i < num_non_terminals; i++) {
                if (non_terminals[i] == prod.lhs) {
                    nt_index = i;
                    break;
                }
            }
            if (nt_index == -1) {
                cout << "Error: LHS symbol not found in non-terminals\n";
                break;
            }

            int next_state = goto_table[top_state][nt_index];
            if (next_state == -1) {
                cout << "Error: No GOTO entry for state " << top_state << " and symbol " << prod.lhs << "\n";
                break;
            }

            state_stack.push(next_state);
        }
        else {
            cout << "Error: Invalid action " << action << "\n";
            break;
        }
    }

    if (!accepted) {
        cout << "Input string rejected.\n";
    }

    return 0;
}










5
3
a b $
2
S A
3
S->AA
A->aA
A->b
s1 - -
- s2 -
- - acc
s3 - -
- - r2
1 2
-1 -1
-1 -1
-1 -1
-1 -1
ab
States: 0  | Symbols:  | Input: ab$ | Action: s1
States: 0 1  | Symbols: a | Input: b$ | Action: s2
States: 0 1 2  | Symbols: ab | Input: $ | Action: acc
Input string accepted.
