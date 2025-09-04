#include <bits/stdc++.h>
using namespace std;

set<char> terminals, nonTerminals;
map<char, vector<string>> productions;
map<char, set<char>> leading, trailing;
map<char, map<char, char>> precedenceTable; // relation: <,=,>
char startSymbol;
const char endMarker = '$';

// Check if terminal
bool isTerminal(char c) {
    return !(c >= 'A' && c <= 'Z');
}

// Compute leading recursively
void computeLeading(char nt) {
    for (auto &prod : productions[nt]) {
        if (prod.empty()) continue;
        char first = prod[0];
        if (isTerminal(first)) {
            leading[nt].insert(first);
        } else {
            if (first != nt) {
                if (leading[first].empty())
                    computeLeading(first);
                leading[nt].insert(leading[first].begin(), leading[first].end());
            }
        }
    }
}

// Compute trailing recursively
void computeTrailing(char nt) {
    for (auto &prod : productions[nt]) {
        if (prod.empty()) continue;
        char last = prod.back();
        if (isTerminal(last)) {
            trailing[nt].insert(last);
        } else {
            if (last != nt) {
                if (trailing[last].empty())
                    computeTrailing(last);
                trailing[nt].insert(trailing[last].begin(), trailing[last].end());
            }
        }
    }
}

// Build initial precedence table from grammar productions
void buildPrecedenceTable() {
    for (auto &p : productions) {
        for (auto &prod : p.second) {
            for (char c : prod) {
                if (isTerminal(c))
                    terminals.insert(c);
            }
        }
    }
    terminals.insert(endMarker);

    for (auto &p : productions) {
        char A = p.first;
        for (auto &prod : p.second) {
            int len = (int)prod.size();
            for (int i = 0; i < len - 1; i++) {
                char a = prod[i];
                char b = prod[i + 1];

                if (isTerminal(a) && isTerminal(b)) {
                    precedenceTable[a][b] = '=';
                }
                if (isTerminal(a) && !isTerminal(b)) {
                    for (char l : leading[b]) {
                        precedenceTable[a][l] = '<';
                    }
                }
                if (!isTerminal(a) && isTerminal(b)) {
                    for (char t : trailing[a]) {
                        precedenceTable[t][b] = '>';
                    }
                }
                if (i < len - 2) {
                    char c = prod[i + 2];
                    if (isTerminal(a) && !isTerminal(b) && isTerminal(c)) {
                        precedenceTable[a][c] = '=';
                    }
                }
            }
        }
    }

    // Relations with end marker
    for (char t : terminals) {
        if (t != endMarker) {
            precedenceTable[endMarker][t] = '<';
            precedenceTable[t][endMarker] = '>';
        }
    }
    precedenceTable[endMarker][endMarker] = '=';

    // Parentheses relations
    for (char t : terminals) {
        if (t != endMarker) {
            if (t != ')') precedenceTable['('][t] = '<';
            if (t != '(') precedenceTable[t][')'] = '>';
        }
    }
    precedenceTable['('][')'] = '=';
}

// Return precedence level of operator for adding missing entries
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '(' || op == ')') return 0;
    if (op == 'i') return 3; // operand
    return -1;
}

// Add explicit operator precedence relations to fix missing entries
void addOperatorPrecedenceRelations() {
    vector<char> ops;
    for (char t : terminals) {
        if (t != '(' && t != ')' && t != endMarker)
            ops.push_back(t);
    }

    for (char a : ops) {
        for (char b : ops) {
            if (a == b) {
                precedenceTable[a][b] = '>';
            } else if (precedence(a) < precedence(b)) {
                precedenceTable[a][b] = '<';
            } else if (precedence(a) > precedence(b)) {
                precedenceTable[a][b] = '>';
            }
        }
    }
}

// Print leading/trailing sets
void printSets(const map<char, set<char>> &sets, const string &name) {
    cout << "\n" << name << " sets:\n";
    for (char nt : nonTerminals) {
        cout << nt << ": { ";
        for (char c : sets.at(nt)) cout << c << " ";
        cout << "}\n";
    }
}

// Print precedence table
void printPrecedenceTable() {
    cout << "\nOperator Precedence Table:\n   ";
    for (char t : terminals) cout << t << "  ";
    cout << "\n";
    for (char a : terminals) {
        cout << a << " ";
        for (char b : terminals) {
            char rel = precedenceTable[a][b];
            if (rel == 0) cout << "   ";
            else cout << " " << rel << " ";
        }
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "Enter number of productions:\n";
    int n; cin >> n;
    cout << "Enter productions (eg: E->E+T|T):\n";

    for (int i = 0; i < n; i++) {
        string line; cin >> line;
        char lhs = line[0];
        if (i == 0) startSymbol = lhs;
        nonTerminals.insert(lhs);

        string rhs = line.substr(3);
        string prodStr = "";
        for (char c : rhs) {
            if (c == '|') {
                productions[lhs].push_back(prodStr);
                prodStr = "";
            } else {
                prodStr += c;
            }
        }
        if (!prodStr.empty())
            productions[lhs].push_back(prodStr);
    }

    // Compute leading/trailing sets
    for (char nt : nonTerminals) {
        if (leading[nt].empty()) computeLeading(nt);
        if (trailing[nt].empty()) computeTrailing(nt);
    }

    printSets(leading, "Leading");
    printSets(trailing, "Trailing");

    buildPrecedenceTable();
    addOperatorPrecedenceRelations();
    printPrecedenceTable();

    return 0;
}
