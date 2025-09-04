#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <unordered_map>
#include <limits>
#include <iomanip>

using namespace std;

const string EPS = "eps";
const string DOLLAR = "$";

vector<string> split_tokens(const string &s) {
    vector<string> out;
    string token;
    stringstream ss(s);
    while (ss >> token) out.push_back(token);
    return out;
}

struct Production {
    string lhs;
    vector<string> rhs;
    
    string toString() const {
        string r = lhs + " ->";
        if (rhs.empty()) r += " eps";
        else for (auto &t : rhs) r += " " + t;
        return r;
    }
};

void print_parse_table(const vector<string> &nonterm_v,
                       const set<string> &terminals,
                       const unordered_map<string,int> &idx,
                       const vector<unordered_map<string,int>> &table,
                       const vector<Production> &prods) {
    // Prepare terminals + $
    vector<string> terms_vec(terminals.begin(), terminals.end());
    terms_vec.push_back(DOLLAR);

    cout << "LL(1) Parsing Table:\n";
    
    // Header row
    cout << setw(12) << "";
    for (auto &t : terms_vec) cout << setw(12) << t;
    cout << "\n";

    // Rows per non-terminal
    for (auto &nt : nonterm_v) {
        cout << setw(12) << nt;
        int row = idx.at(nt);
        for (auto &t : terms_vec) {
            if (table[row].count(t)) {
                int pidx = table[row].at(t);
                cout << setw(12) << ("P" + to_string(pidx));
            } else {
                cout << setw(12) << "-";
            }
        }
        cout << "\n";
    }
    cout << "\n";
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Fixed the issue

    vector<Production> prods;
    set<string> nonterminals;
    vector<string> lhs_order;

    // Parse productions
    for (int i = 0; i < n; ++i) {
        string line;
        getline(cin, line);
        if (line.empty()) { --i; continue; }
        
        auto trim = [](string s) {
            while (!s.empty() && isspace((unsigned char)s.back())) s.pop_back();
            while (!s.empty() && isspace((unsigned char)s.front())) s.erase(s.begin());
            return s;
        };
        
        line = trim(line);
        size_t arrow = line.find("->");
        if (arrow == string::npos) { cerr << "Invalid production: " << line << "\n"; return 1; }
        
        string LHS = trim(line.substr(0, arrow));
        string RHSs = trim(line.substr(arrow + 2));
        vector<string> rhs = split_tokens(RHSs);

        Production p{LHS, {}};
        if (!(rhs.size() == 1 && rhs[0] == EPS)) {
            p.rhs = rhs;
        }

        prods.push_back(p);
        if (!nonterminals.count(LHS)) {
            nonterminals.insert(LHS);
            lhs_order.push_back(LHS);
        }
    }

    // Identify terminals
    set<string> terminals;
    for (auto &p : prods)
        for (auto &sym : p.rhs)
            if (sym != EPS && !nonterminals.count(sym))
                terminals.insert(sym);

    string start = prods.front().lhs;
    vector<string> nonterm_v(lhs_order.begin(), lhs_order.end());
    unordered_map<string, int> idx;
    for (int i = 0; i < (int)nonterm_v.size(); ++i) idx[nonterm_v[i]] = i;

    cout << "\nGrammar (start symbol = " << start << ")\n";
    for (auto &p : prods) cout << "  " << p.toString() << "\n";
    cout << "\nNon-terminals: ";
    for (auto &s : nonterm_v) cout << s << " ";
    cout << "\nTerminals: ";
    for (auto &t : terminals) cout << t << " ";
    cout << "\n\n";

    unordered_map<string, set<string>> FIRST;
    for (auto &t : terminals) FIRST[t] = {t};
    FIRST[EPS] = {EPS};
    for (auto &A : nonterm_v) FIRST[A] = {};

    // Calculate FIRST sets
    auto first_of_sequence = [&](const vector<string> &alpha) {
        set<string> res;
        if (alpha.empty()) {
            res.insert(EPS);
            return res;
        }
        bool all_eps = true;
        for (auto &sym : alpha) {
            for (auto &f : FIRST[sym])
                if (f != EPS) res.insert(f);
            if (!FIRST[sym].count(EPS)) {
                all_eps = false;
                break;
            }
        }
        if (all_eps) res.insert(EPS);
        return res;
    };

    bool changed = true;
    while (changed) {
        changed = false;
        for (auto &p : prods) {
            auto before = FIRST[p.lhs];
            auto add = first_of_sequence(p.rhs);
            for (auto &x : add) FIRST[p.lhs].insert(x);
            if (FIRST[p.lhs].size() != before.size()) changed = true;
        }
    }

    // Print FIRST sets
    cout << "FIRST sets:\n";
    for (auto &A : nonterm_v) {
        cout << "FIRST(" << A << ") = { ";
        bool firstout = true;
        for (auto &x : FIRST[A]) {
            if (!firstout) cout << ", ";
            cout << x;
            firstout = false;
        }
        cout << " }\n";
    }
    cout << "\n";

    unordered_map<string, set<string>> FOLLOW;
    for (auto &A : nonterm_v) FOLLOW[A] = {};
    FOLLOW[start].insert(DOLLAR);

    // Calculate FOLLOW sets
    changed = true;
    while (changed) {
        changed = false;
        for (auto &p : prods) {
            for (int i = 0; i < (int)p.rhs.size(); ++i) {
                string B = p.rhs[i];
                if (!nonterminals.count(B)) continue;
                vector<string> beta(p.rhs.begin() + i + 1, p.rhs.end());
                auto firstBeta = first_of_sequence(beta);
                for (auto &f : firstBeta)
                    if (f != EPS && !FOLLOW[B].count(f)) {
                        FOLLOW[B].insert(f); changed = true;
                    }
                if (firstBeta.count(EPS) || beta.empty()) {
                    for (auto &f : FOLLOW[p.lhs])
                        if (!FOLLOW[B].count(f)) { FOLLOW[B].insert(f); changed = true; }
                }
            }
        }
    }

    // Print FOLLOW sets
    cout << "FOLLOW sets:\n";
    for (auto &A : nonterm_v) {
        cout << "FOLLOW(" << A << ") = { ";
        bool firstout = true;
        for (auto &x : FOLLOW[A]) {
            if (!firstout) cout << ", ";
            cout << x;
            firstout = false;
        }
        cout << " }\n";
    }
    cout << "\n";

    set<string> terms_dollar = terminals;
    terms_dollar.insert(DOLLAR);

    // LL(1) parsing table
    vector<unordered_map<string, int>> table(nonterm_v.size());
    bool isLL1 = true;
    vector<string> conflicts;

    for (int pi = 0; pi < (int)prods.size(); ++pi) {
        auto &p = prods[pi];
        auto firstAlpha = first_of_sequence(p.rhs);
        for (auto &a : firstAlpha) {
            if (a == EPS) continue;
            int Ai = idx[p.lhs];
            if (table[Ai].count(a)) {
                isLL1 = false;
                conflicts.push_back("Conflict at table[" + p.lhs + "][" + a + "]");
            } else table[Ai][a] = pi;
        }
        if (firstAlpha.count(EPS)) {
            for (auto &b : FOLLOW[p.lhs]) {
                int Ai = idx[p.lhs];
                if (table[Ai].count(b)) {
                    isLL1 = false;
                    conflicts.push_back("Conflict at table[" + p.lhs + "][" + b + "]");
                } else table[Ai][b] = pi;
            }
        }
    }
    
    cout << (isLL1 ? "Grammar is LL(1).\n" : "Grammar not LL(1):\n");
    for (auto &c : conflicts) cout << "  " << c << "\n";
    cout << "\nProductions:\n";
    for (int i = 0; i < (int)prods.size(); ++i) cout << "P" << i << ": " << prods[i].toString() << "\n";
    cout << "\n";

    // Parsing step
    string inLine;
    getline(cin, inLine);
    if (inLine.empty()) getline(cin, inLine);
    vector<string> input = split_tokens(inLine);
    input.push_back(DOLLAR);
    
    print_parse_table(nonterm_v, terminals, idx, table, prods);
     
    cout << "\nParsing Steps\n";
    vector<string> stack_;
    stack_.push_back(DOLLAR);
    stack_.push_back(start);

    auto print_stack = [&](const vector<string> &st) {
        for (int i = (int)st.size() - 1; i >= 0; --i) {
            cout << st[i] << (i > 0 ? " " : "");
        }
    };

    auto print_input = [&](const vector<string> &inp, int pos) {
        for (int i = pos; i < (int)inp.size(); ++i) {
            cout << inp[i] << (i + 1 < (int)inp.size() ? " " : "");
        }
    };

    int ip = 0, step = 0;
    bool accept = false, error = false;

    // Parsing loop
    while (!error && !accept) {
        cout << setw(4) << step++ << " | Stack: [";
        print_stack(stack_);
        cout << "] | Input: ";
        print_input(input, ip);
        cout << "\n";

        string top = stack_.back();
        string current = input[ip];

        if (top == current) {
            stack_.pop_back();
            ip++;
            if (top == DOLLAR) accept = true;
        } else if (nonterminals.count(top)) {
            int idx_ = idx[top];
            if (table[idx_].count(current)) {
                int prod_idx = table[idx_][current];
                auto &prod = prods[prod_idx];
                stack_.pop_back();
                if (!(prod.rhs.size() == 1 && prod.rhs[0] == EPS)) {
                    for (auto it = prod.rhs.rbegin(); it != prod.rhs.rend(); ++it) {
                        stack_.push_back(*it);
                    }
                }
            } else {
                error = true;
                cout << "Error: No rule for " << top << " with input " << current << "\n";
            }
        } else {
            error = true;
            cout << "Error: Unexpected terminal " << top << " in stack, expected " << current << "\n";
        }
    }

    if (accept) cout << "Parsing accepted.\n";
    else cout << "Parsing failed.\n";
    return 0;
}

input:
8
E -> T E'
E' -> + T E'
E' -> eps
T -> F T'
T' -> * F T'
T' -> eps
F -> ( E )
F -> id
id + id * id

output:
Grammar (start symbol = E)
  E -> T E'
  E' -> + T E'
  E' -> eps
  T -> F T'
  T' -> * F T'
  T' -> eps
  F -> ( E )
  F -> id

Non-terminals: E E' T T' F 
Terminals: ( ) * + id 

FIRST sets:
FIRST(E) = { (, id }
FIRST(E') = { +, eps }
FIRST(T) = { (, id }
FIRST(T') = { *, eps }
FIRST(F) = { (, id }

FOLLOW sets:
FOLLOW(E) = { $, ) }
FOLLOW(E') = { $, ) }
FOLLOW(T) = { $, ), + }
FOLLOW(T') = { $, ), + }
FOLLOW(F) = { $, ), *, + }

Grammar is LL(1).

Productions:
P0: E -> T E'
P1: E' -> + T E'
P2: E' -> eps
P3: T -> F T'
P4: T' -> * F T'
P5: T' -> eps
P6: F -> ( E )
P7: F -> id

LL(1) Parsing Table:
                       (           )           *           +          id           $
           E          P0           -           -           -          P0           -
          E'           -          P2           -          P1           -          P2
           T          P3           -           -           -          P3           -
          T'           -          P5          P4          P5           -          P5
           F          P6           -           -           -          P7           -


Parsing Steps
   0 | Stack: [E $] | Input: id + id * id $
   1 | Stack: [T E' $] | Input: id + id * id $
   2 | Stack: [F T' E' $] | Input: id + id * id $
   3 | Stack: [id T' E' $] | Input: id + id * id $
   4 | Stack: [T' E' $] | Input: + id * id $
   5 | Stack: [E' $] | Input: + id * id $
   6 | Stack: [+ T E' $] | Input: + id * id $
   7 | Stack: [T E' $] | Input: id * id $
   8 | Stack: [F T' E' $] | Input: id * id $
   9 | Stack: [id T' E' $] | Input: id * id $
  10 | Stack: [T' E' $] | Input: * id $
  11 | Stack: [* F T' E' $] | Input: * id $
  12 | Stack: [F T' E' $] | Input: id $
  13 | Stack: [id T' E' $] | Input: id $
  14 | Stack: [T' E' $] | Input: $
  15 | Stack: [E' $] | Input: $
  16 | Stack: [$] | Input: $
Parsing accepted.
