Experiment-9(a) Construct Simple LR (SLR) parse table using C language.
Aim: To a construct the SLR Action and Goto Table using the grammar productions given in the input
Algorithm:
1. Augment the grammar with the new start symbol.
2. Construct the canonical collection of LR(0) items.
3. Find FOLLOW sets for each non-terminal.
4. Compute closure() and goto() step by step.
5. Draw the DFA of LR(0) items. 6. Construct the SLR parsing table (ACTION and GOTO).
Code:
#include <bits/stdc++.h>
using namespace std;
struct Production {
 string lhs;
 vector<string> rhs;
};
struct Item {
 int prod;
 int dot;
 bool operator<(Item const& o) const {
 if (prod != o.prod) return prod < o.prod;
 return dot < o.dot;
 }
 bool operator==(Item const& o) const {
 return prod==o.prod && dot==o.dot;
 }
};
int main() {
 int n;
 // cout << "Enter number of productions: ";
 cin >> n;
 vector<Production> P;
 string startSymbol;
 // cout << "Enter productions (LHS RHS, space separated, ε for empty):\n";
 cin.ignore();
 for (int i=0;i<n;i++) {
 string line; getline(cin, line);
 stringstream ss(line);
 string lhs; ss >> lhs;
 if (i==0) startSymbol = lhs;
 vector<string> rhs;
 string sym;
 while (ss >> sym) {
 if (sym=="ε") continue;
 rhs.push_back(sym);
 }
 P.push_back({lhs, rhs});
 }
 // augment grammar
 P.insert(P.begin(), {startSymbol+"'", {startSymbol}});
 // collect symbols
 set<string> nonterminals, terminals;
 for (auto &pr: P) nonterminals.insert(pr.lhs);
 for (auto &pr: P) for (auto &s: pr.rhs)
 if (!nonterminals.count(s) && s!="ε") terminals.insert(s);
 terminals.insert("$");
 // prods by LHS
 unordered_map<string, vector<int>> prods_by_lhs;
 for (int i=0;i<(int)P.size();i++) prods_by_lhs[P[i].lhs].push_back(i);
 auto closure=[&](set<Item> I){
 set<Item> C=I; bool changed=true;
 while(changed){
 changed=false;
 vector<Item> cur(C.begin(), C.end());
 for(auto it:cur){
 if(it.dot < (int)P[it.prod].rhs.size()){
 string B=P[it.prod].rhs[it.dot];
 if(nonterminals.count(B)){
 for(int pi:prods_by_lhs[B]){
 Item newit{pi,0};
 if(!C.count(newit)){ C.insert(newit); changed=true; }
 }
 }
 }
 }
 }
 return C;
 };
 auto goto_set=[&](set<Item> I,string X){
 set<Item> J;
 for(auto it:I){
 if(it.dot<(int)P[it.prod].rhs.size() && P[it.prod].rhs[it.dot]==X)
 J.insert({it.prod,it.dot+1});
 }
 return closure(J);
 };
 vector< set<Item> > states;
 map< set<Item>, int > state_id;
 set<Item> I0; I0.insert({0,0}); I0=closure(I0);
 states.push_back(I0); state_id[I0]=0;
 queue<int>q; q.push(0);
 while(!q.empty()){
 int idx=q.front(); q.pop();
 set<string> symbols;
 for(auto it:states[idx]){
 if(it.dot<(int)P[it.prod].rhs.size())
 symbols.insert(P[it.prod].rhs[it.dot]);
 }
 for(auto X:symbols){
 set<Item> J=goto_set(states[idx],X);
 if(J.empty()) continue;
 if(!state_id.count(J)){
 int nid=states.size();
 states.push_back(J); state_id[J]=nid; q.push(nid);
 }
 }
 }
 // build FOLLOW sets
 unordered_map<string,set<string>> FIRST,FOLLOW;
 for(auto &t:terminals) FIRST[t]={t};
 for(auto &N:nonterminals) FIRST[N]={};
 FOLLOW[P[0].lhs].insert("$");
 bool changed=true;
 while(changed){
 changed=false;
 for(auto &prod:P){
 string A=prod.lhs;
 for(int i=0;i<(int)prod.rhs.size();i++){
 string B=prod.rhs[i];
 if(!nonterminals.count(B)) continue;
 bool nullable=true;
 for(int k=i+1;k<(int)prod.rhs.size();k++){
 string sym=prod.rhs[k];
 for(auto &x:FIRST[sym]) if(x!="ε")
 if(!FOLLOW[B].count(x)){ FOLLOW[B].insert(x); changed=true; }
 nullable=false; break;
 }
 if(i+1==(int)prod.rhs.size()||nullable){
 for(auto &x:FOLLOW[A])
 if(!FOLLOW[B].count(x)){ FOLLOW[B].insert(x); changed=true; }
 }
 }
 }
 }
 // transitions
 map<pair<int,string>,int> trans;
 for(int i=0;i<(int)states.size();i++){
 set<string> symbols;
 for(auto it:states[i])
 if(it.dot<(int)P[it.prod].rhs.size())
 symbols.insert(P[it.prod].rhs[it.dot]);
 for(auto X:symbols){
 set<Item> J=goto_set(states[i],X);
 if(J.empty()) continue;
 int to=state_id[J];
 trans[{i,X}]=to;
 }
 }
 // ACTION & GOTO
 map<pair<int,string>,string> ACTION;
 map<pair<int,string>,int> GOTO;
 for(int i=0;i<(int)states.size();i++){
 for(auto it:states[i]){
 if(it.dot<(int)P[it.prod].rhs.size()){
 string a=P[it.prod].rhs[it.dot];
 if(terminals.count(a)&&a!="$"){
 if(trans.count({i,a})) ACTION[{i,a}]="s"+to_string(trans[{i,a}]);
 } else if(nonterminals.count(a)){
 if(trans.count({i,a})) GOTO[{i,a}]=trans[{i,a}];
 }
 } else {
 if(P[it.prod].lhs==P[0].lhs) ACTION[{i,"$"}]="acc";
 else for(auto &a:FOLLOW[P[it.prod].lhs])
 ACTION[{i,a}]="r"+to_string(it.prod);
 }
 }
 }
 // print table
 vector<string> terms(terminals.begin(),terminals.end());
 vector<string> nonterms;
 for(auto &N:nonterminals) if(N!=P[0].lhs) nonterms.push_back(N);
 cout<<"State";
 for(auto &t:terms) cout<<"\t"<<t;
 for(auto &nt:nonterms) cout<<"\t"<<nt;
 cout<<"\n";
 for(int i=0;i<(int)states.size();i++){
 cout<<i;
 for(auto &t:terms){
 string cell="";
 if(ACTION.count({i,t})) cell=ACTION[{i,t}];
 cout<<"\t"<<cell;
 }
 for(auto &nt:nonterms){
 string cell="";
 if(GOTO.count({i,nt})) cell=to_string(GOTO[{i,nt}]);
 cout<<"\t"<<cell;
 }
 cout<<"\n";
 }
}
Output:
Experiment-9(b) Implement the LR parsing algorithm, get both parse table and input string are inputs. Use C
language for implementation.
Aim: To parse an input string based on the parse table generated. The input will be the action goto parse table,
along with the input string and the output will be the stack tracing of the parsing of the string.
Code:
#include <bits/stdc++.h>
using namespace std;
struct Production {
 string lhs;
 vector<string> rhs;
 string to_string() const {
 string s = lhs + " ->";
 if (rhs.empty()) s += " ε";
 else for (auto &t: rhs) s += " " + t;
 return s;
 }
};
struct Item {
 int prod;
 int dot;
 bool operator<(Item const& o) const {
 if (prod != o.prod) return prod < o.prod;
 return dot < o.dot;
 }
 bool operator==(Item const& o) const {
 return prod==o.prod && dot==o.dot;
 }
};
int main() {
 int n;
 cout << "Enter number of productions: ";
 cin >> n;
 vector<Production> P;
 string startSymbol;
 cout << "Enter productions in the form: LHS RHS (space separated, use ε for empty):\n";
 cin.ignore();
 for (int i=0;i<n;i++) {
 string line;
 getline(cin, line);
 stringstream ss(line);
 string lhs;
 ss >> lhs;
 if (i==0) startSymbol = lhs; // first LHS is start
 vector<string> rhs;
 string sym;
 while (ss >> sym) {
 if (sym=="ε") continue;
 rhs.push_back(sym);
 }
 P.push_back({lhs, rhs});
 }
 // augment grammar
 P.insert(P.begin(), {startSymbol+"'", {startSymbol}});
 // collect terminals and nonterminals
 set<string> nonterminals;
 set<string> terminals;
 for (auto &pr : P) nonterminals.insert(pr.lhs);
 for (auto &pr : P) {
 for (auto &sym : pr.rhs) {
 if (!nonterminals.count(sym) && sym!="ε")
 terminals.insert(sym);
 }
 }
 terminals.insert("$");
 unordered_map<string, vector<int>> prods_by_lhs;
 for (int i=0;i<(int)P.size();++i) prods_by_lhs[P[i].lhs].push_back(i);
 auto closure = [&](const set<Item>& I) {
 set<Item> C = I;
 bool changed = true;
 while (changed) {
 changed = false;
 vector<Item> cur(C.begin(), C.end());
 for (auto it: cur) {
 const Production &prod = P[it.prod];
 if (it.dot < (int)prod.rhs.size()) {
 string B = prod.rhs[it.dot];
 if (nonterminals.count(B)) {
 for (int pi : prods_by_lhs[B]) {
 Item newit{pi, 0};
 if (!(C.count(newit))) {
 C.insert(newit);
 changed = true;
 }
 }
 }
 }
 }
 }
 return C;
 };
 auto goto_set = [&](const set<Item>& I, const string &X) {
 set<Item> J;
 for (auto it: I) {
 const Production &prod = P[it.prod];
 if (it.dot < (int)prod.rhs.size() && prod.rhs[it.dot] == X) {
 J.insert(Item{it.prod, it.dot + 1});
 }
 }
 return closure(J);
 };
 // Build canonical collection of LR(0) states
 vector< set<Item> > states;
 map< set<Item>, int > state_id;
 set<Item> I0;
 I0.insert(Item{0,0});
 I0 = closure(I0);
 states.push_back(I0);
 state_id[I0] = 0;
 queue<int> q;
 q.push(0);
 while (!q.empty()) {
 int idx = q.front(); q.pop();
 set<string> symbols;
 for (auto it : states[idx]) {
 const Production &prod = P[it.prod];
 if (it.dot < (int)prod.rhs.size()) {
 symbols.insert(prod.rhs[it.dot]);
 }
 }
 for (auto X : symbols) {
 set<Item> J = goto_set(states[idx], X);
 if (J.empty()) continue;
 if (!state_id.count(J)) {
 int nid = states.size();
 states.push_back(J);
 state_id[J] = nid;
 q.push(nid);
 }
 }
 }
 // FOLLOW sets
 unordered_map<string, set<string>> FOLLOW;
 unordered_map<string, set<string>> FIRST;
 for (auto &t: terminals) FIRST[t] = {t};
 for (auto &N: nonterminals) FIRST[N] = {};
 bool fchg=true;
 while (fchg) {
 fchg=false;
 for (auto &prod: P) {
 string A = prod.lhs;
 if (prod.rhs.empty()) {
 FIRST[A].insert("ε");
 } else {
 string firstSym = prod.rhs[0];
 for (auto &x: FIRST[firstSym]) {
 if (!FIRST[A].count(x)) { FIRST[A].insert(x); fchg=true; }
 }
 }
 }
 }
 for (auto &N: nonterminals) FOLLOW[N] = {};
 FOLLOW[P[0].lhs].insert("$");
 bool f2chg = true;
 while (f2chg) {
 f2chg = false;
 for (auto &prod: P) {
 string A = prod.lhs;
 for (int i=0;i<(int)prod.rhs.size();++i) {
 string B = prod.rhs[i];
 if (!nonterminals.count(B)) continue;
 set<string> firstBeta;
 bool allNullable = true;
 for (int k=i+1;k<(int)prod.rhs.size();++k) {
 string sym = prod.rhs[k];
 for (auto &x: FIRST[sym]) firstBeta.insert(x);
 allNullable = false;
 break;
 }
 for (auto &t: firstBeta) {
 if (!FOLLOW[B].count(t)) {
 FOLLOW[B].insert(t);
 f2chg = true;
 }
 }
 if (i+1 >= (int)prod.rhs.size() || allNullable) {
 for (auto &t: FOLLOW[A]) {
 if (!FOLLOW[B].count(t)) {
 FOLLOW[B].insert(t);
 f2chg = true;
 }
 }
 }
 }
 }
 }
 // Build ACTION & GOTO tables
 map<pair<int,string>, string> ACTION;
 map<pair<int,string>, int> GOTO;
 for (int i=0;i<(int)states.size();++i) {
 for (auto it : states[i]) {
 const Production &prod = P[it.prod];
 if (it.dot < (int)prod.rhs.size()) {
 string a = prod.rhs[it.dot];
 if (terminals.count(a) && a!="$") {
 // shift action
 set<Item> J = goto_set(states[i], a);
 if (!J.empty()) {
 int j = state_id[J];
 ACTION[{i,a}] = "s" + to_string(j);
 }
 } else if (nonterminals.count(a)) {
 set<Item> J = goto_set(states[i], a);
 if (!J.empty()) {
 int j = state_id[J];
 GOTO[{i,a}] = j;
 }
 }
 } else {
 if (P[it.prod].lhs == P[0].lhs) {
 ACTION[{i,"$"}] = "acc";
 } else {
 string A = P[it.prod].lhs;
 for (auto &a : FOLLOW[A]) {
 ACTION[{i,a}] = "r" + to_string(it.prod);
 }
 }
 }
 }
 }
 // Display SLR parsing table
 vector<string> term_list(terminals.begin(), terminals.end());
 vector<string> nonterm_list;
 for (auto &N: nonterminals) if (N != P[0].lhs) nonterm_list.push_back(N);
 cout << "SLR Parsing Table (ACTION and GOTO):\n";
 cout << setw(6) << "State";
 for (auto &t: term_list) cout << setw(8) << t;
 for (auto &nt: nonterm_list) cout << setw(8) << nt;
 cout << "\n";
 for (int i=0;i<(int)states.size();++i) {
 cout << setw(6) << i;
 for (auto &t: term_list) {
 string cell = "";
 if (ACTION.count({i,t})) cell = ACTION[{i,t}];
 cout << setw(8) << cell;
 }
 for (auto &nt: nonterm_list) {
 string cell = "";
 if (GOTO.count({i,nt})) cell = to_string(GOTO[{i,nt}]);
 cout << setw(8) << cell;
 }
 cout << "\n";
 }
 // Parse input string
 string input;
 cout << "Enter input string to parse: ";
 cin >> input;
 vector<string> tokens;
 for (char ch: input) {
 string s(1,ch);
 if (terminals.count(s)) tokens.push_back(s);
 }
 tokens.push_back("$");
 cout << "Parsing trace for input: (" << input << ")\n";
 vector<int> st; st.push_back(0);
 cout << left;
 cout << "Step | Stack(states) | Input | Action\n";
 cout << "---------------------------------------------------------------\n";
 int step=0;
 vector<string> input_buf = tokens;
 while (true) {
 int s = st.back();
 string a = input_buf.front();
 string act = "";
 if (ACTION.count({s,a})) act = ACTION[{s,a}];
 else act = "err";
 cout << setw(4) << step << " | ";
 { string ss; for(size_t i=0;i<st.size();++i){ if(i) ss+=" "; ss+=to_string(st[i]); }
 cout << setw(20) << ss << " | "; }
 { string ib; for(size_t i=0;i<input_buf.size();++i){ if(i) ib+=" "; ib+=input_buf[i]; }
 cout << setw(18) << ib << " | "; }
 cout << act << "\n";
 if (act=="acc") {
 cout << "Input accepted.\n"; break;
 } else if (act.size() && act[0]=='s') {
 int tnum = stoi(act.substr(1));
 st.push_back(tnum);
 input_buf.erase(input_buf.begin());
 } else if (act.size() && act[0]=='r') {
 int prod_idx = stoi(act.substr(1));
 int rhs_len = P[prod_idx].rhs.size();
 for (int k=0;k<rhs_len;++k) if(!st.empty()) st.pop_back();
 int top = st.back();
 string A = P[prod_idx].lhs;
 if (GOTO.count({top,A})) {
 st.push_back(GOTO[{top,A}]);
 } else {
 cout << "ERROR: no GOTO[" << top << "," << A << "]\n";
 return 0;
 }
 } else {
 cout << "ERROR: parsing table indicates no action. Aborting.\n";
 break;
 }
 step++;
 if (step>200) { cout << "Too many steps; aborting.\n"; break; }
 }
 return 0;
}
Output:
SLR Parsing Table (ACTION and GOTо):
State $ i E F T
0 s1 55 2 3 4
1 51 55 6 3 4
2 acc 57
3 r4 r4 r4 r4
4 r2 r2 58 r2
5 r6 gr r6 gu
6 59 57
7 51 55 3 10
8 s1 55 11
9 r5 r5 r5 r5
10 r1 r1 58 r1
11 r3 r3 r3 r3
Enter input string to parse: Parsing trace for input: (i+i*i)
Step | Stack(states) | Input Action
0 0 i+i* i $ 55
1 0 5 + i* i $ r6
2 0 3 + i * i$ r4
3 0 4 + i* i $ r2
4 0 2 + i* i $ 57
5 0 2 7 1
* i 55
6 0 2 7 5
* i $
7 0 2 7 3
* i $ r4
8 0 2 7 10 * i $ 58
9 0 2 7 10 8 i $ 55
10 0 2 7 10 8 5 $ r6
11 0 2 7 10 8 11 $ r3
12 e 2 7 10 $ r1
13 0 2 $ acc
Input accepted.
Experiment-10(a) Construct Canonical LR (CLR) parse table using C language.
Aim: To construct a clr parse table based on the input grammar productions
Code:
#include <bits/stdc++.h>
using namespace std;
struct Production {
 string lhs;
 vector<string> rhs;
};
struct Item {
 int prod;
 int dot;
 string lookahead;
 bool operator<(Item const& o) const {
 if(prod != o.prod) return prod < o.prod;
 if(dot != o.dot) return dot < o.dot;
 return lookahead < o.lookahead;
 }
 bool operator==(Item const& o) const {
 return prod==o.prod && dot==o.dot && lookahead==o.lookahead;
 }
};
int main(){
 int n;
 cout << "Enter number of productions: ";
 cin >> n;
 cin.ignore();
 vector<Production> P;
 set<string> terminals, nonterminals;
 cout << "Enter productions in the form: LHS RHS (use spaces, ε for empty):\n";
 for(int i=0;i<n;i++){
 string line;
 getline(cin, line);
 stringstream ss(line);
 string lhs;
 ss >> lhs;
 nonterminals.insert(lhs);
 vector<string> rhs;
 string sym;
 while(ss >> sym){
 if(sym!="ε") rhs.push_back(sym);
 else rhs.push_back("ε");
 }
 P.push_back({lhs, rhs});
 }
 // augment grammar
 string startSymbol = P[0].lhs;
 P.insert(P.begin(), {startSymbol+"'", {startSymbol}});
 nonterminals.insert(startSymbol+"'");
 // collect terminals
 for(auto &prod : P){
 for(auto &sym: prod.rhs){
 if(!nonterminals.count(sym) && sym!="ε") terminals.insert(sym);
 }
 }
 terminals.insert("$");
 unordered_map<string, vector<int>> prods_by_lhs;
 for(int i=0;i<(int)P.size();++i) prods_by_lhs[P[i].lhs].push_back(i);
 // Compute FIRST sets
 unordered_map<string,set<string>> FIRST;
 for(auto &t: terminals) FIRST[t] = {t};
 for(auto &N: nonterminals) FIRST[N] = {};
 bool changed=true;
 while(changed){
 changed=false;
 for(auto &prod: P){
 string A = prod.lhs;
 for(auto &sym: prod.rhs){
 if(terminals.count(sym)){
 if(!FIRST[A].count(sym)){ FIRST[A].insert(sym); changed=true; }
 break;
 } else {
 size_t before=FIRST[A].size();
 for(auto &x: FIRST[sym]) if(x!="ε") FIRST[A].insert(x);
 if(FIRST[A].size()!=before) changed=true;
 break;
 }
 }
 }
 }
 auto first_of_string = [&](vector<string> beta, string a){
 set<string> res;
 if(beta.empty()) res.insert(a);
 else {
 string X = beta[0];
 if(terminals.count(X)) res.insert(X);
 else res.insert(FIRST[X].begin(), FIRST[X].end());
 }
 return res;
 };
 auto closure = [&](set<Item> I){
 set<Item> C = I;
 bool changed=true;
 while(changed){
 changed=false;
 vector<Item> cur(C.begin(), C.end());
 for(auto it: cur){
 const Production &prod = P[it.prod];
 if(it.dot < (int)prod.rhs.size()){
 string B = prod.rhs[it.dot];
 if(nonterminals.count(B)){
 vector<string> beta(prod.rhs.begin()+it.dot+1, prod.rhs.end());
 beta.push_back(it.lookahead);
 set<string> lookaheads = first_of_string(beta, it.lookahead);
 for(int pi : prods_by_lhs[B]){
 for(auto &b: lookaheads){
 Item newit{pi,0,b};
 if(!C.count(newit)){
 C.insert(newit);
 changed=true;
 }
 }
 }
 }
 }
 }
 }
 return C;
 };
 auto goto_set = [&](set<Item> I, string X){
 set<Item> J;
 for(auto it: I){
 const Production &prod = P[it.prod];
 if(it.dot < (int)prod.rhs.size() && prod.rhs[it.dot]==X){
 J.insert({it.prod, it.dot+1, it.lookahead});
 }
 }
 return closure(J);
 };
 vector< set<Item> > states;
 map< set<Item>, int > state_id;
 set<Item> I0;
 I0.insert({0,0,"$"});
 I0 = closure(I0);
 states.push_back(I0);
 state_id[I0]=0;
 queue<int> q;
 q.push(0);
 while(!q.empty()){
 int i=q.front(); q.pop();
 set<string> symbols;
 for(auto it: states[i]){
 const Production &prod = P[it.prod];
 if(it.dot<(int)prod.rhs.size()) symbols.insert(prod.rhs[it.dot]);
 }
 for(auto X: symbols){
 set<Item> J = goto_set(states[i],X);
 if(J.empty()) continue;
 if(!state_id.count(J)){
 int nid=states.size();
 states.push_back(J);
 state_id[J]=nid;
 q.push(nid);
 }
 }
 }
 // CLR Parsing Table
 map<pair<int,string>,string> ACTION;
 map<pair<int,string>,int> GOTO;
 for(size_t i=0;i<states.size();++i){
 set<string> symbols;
 for(auto it: states[i]){
 const Production &prod = P[it.prod];
 if(it.dot<(int)prod.rhs.size()) symbols.insert(prod.rhs[it.dot]);
 }
 for(auto X: symbols){
 set<Item> J = goto_set(states[i],X);
 if(J.empty()) continue;
 int j=state_id[J];
 if(terminals.count(X)) ACTION[{(int)i,X}] = "s"+to_string(j);
 else GOTO[{(int)i,X}] = j;
 }
 for(auto it: states[i]){
 if(it.dot==(int)P[it.prod].rhs.size()){
 if(P[it.prod].lhs=="S'" && it.lookahead=="$"){
 ACTION[{(int)i,"$"}]="acc";
 } else {
 ACTION[{(int)i,it.lookahead}] = "r"+to_string(it.prod);
 }
 }
 }
 }
 // Print CLR Parsing Table
 cout<<"CLR Parsing Table:\n";
 vector<string> term_list(terminals.begin(), terminals.end());
 vector<string> nonterm_list;
 for(auto &nt: nonterminals) if(nt != startSymbol+"'") nonterm_list.push_back(nt);
 cout<<setw(6)<<"State";
 for(auto &t: term_list) cout<<setw(8)<<t;
 for(auto &nt: nonterm_list) cout<<setw(8)<<nt;
 cout<<"\n";
 for(size_t i=0;i<states.size();++i){
 cout<<setw(6)<<i;
 for(auto &t: term_list){
 string cell="";
 if(ACTION.count({(int)i,t})) cell=ACTION[{(int)i,t}];
 cout<<setw(8)<<cell;
 }
 for(auto &nt: nonterm_list){
 string cell="";
 if(GOTO.count({(int)i,nt})) cell=to_string(GOTO[{(int)i,nt}]);
 cout<<setw(8)<<cell;
 }
 cout<<"\n";
 }
}
Output:
Experiment-10(b) Implement the LR parsing algorithm, get both parse table and input string are
inputs. Use C language for implementation.
Aim: To construct the clr stack trace using the parse table to show whether the input string is
accepted or not.
Code:
#include <bits/stdc++.h>
using namespace std;
struct Production {
 string lhs;
 vector<string> rhs;
};
struct Item {
 int prod;
 int dot;
 string lookahead;
 bool operator<(Item const& o) const {
 if(prod != o.prod) return prod < o.prod;
 if(dot != o.dot) return dot < o.dot;
 return lookahead < o.lookahead;
 }
 bool operator==(Item const& o) const {
 return prod==o.prod && dot==o.dot && lookahead==o.lookahead;
 }
};
int main(){
 int n;
 cin >> n;
 cin.ignore();
 vector<Production> P;
 set<string> terminals, nonterminals;
 cout << "Enter productions in the form: LHS RHS (use spaces, ε for empty):\n";
 for(int i=0;i<n;i++){
 string line;
 getline(cin, line);
 stringstream ss(line);
 string lhs;
 ss >> lhs;
 nonterminals.insert(lhs);
 vector<string> rhs;
 string sym;
 while(ss >> sym){
 if(sym!="ε") rhs.push_back(sym);
 else rhs.push_back("ε");
 }
 P.push_back({lhs, rhs});
 }
 // augment grammar
 string startSymbol = P[0].lhs;
 string augStartSymbol = startSymbol + "'";
 P.insert(P.begin(), {augStartSymbol, {startSymbol}});
 nonterminals.insert(augStartSymbol);
 // collect terminals
 for(auto &prod : P){
 for(auto &sym: prod.rhs){
 if(!nonterminals.count(sym) && sym!="ε") terminals.insert(sym);
 }
 }
 terminals.insert("$");
 unordered_map<string, vector<int>> prods_by_lhs;
 for(int i=0;i<(int)P.size();++i) prods_by_lhs[P[i].lhs].push_back(i);
 // Compute FIRST sets
 unordered_map<string,set<string>> FIRST;
 for(auto &t: terminals) FIRST[t] = {t};
 for(auto &N: nonterminals) FIRST[N] = {};
 bool changed=true;
 while(changed){
 changed=false;
 for(auto &prod: P){
 string A = prod.lhs;
 bool all_eps = true;
 for(auto &sym: prod.rhs){
 if(terminals.count(sym)){
 if(!FIRST[A].count(sym)){ FIRST[A].insert(sym); changed=true; }
 all_eps = false; break;
 } else {
 size_t before=FIRST[A].size();
 for(auto &x: FIRST[sym]) if(x!="ε") FIRST[A].insert(x);
 if(!FIRST[sym].count("ε")) all_eps=false;
 if(FIRST[A].size()!=before) changed=true;
 if(!FIRST[sym].count("ε")) break;
 }
 }
 if(all_eps) { if(!FIRST[A].count("ε")) { FIRST[A].insert("ε"); changed=true; } }
 }
 }
 // fixed first_of_string
 auto first_of_string = [&](vector<string> beta, string a){
 set<string> res;
 if(beta.empty()) { res.insert(a); return res; }
 bool eps_prefix = true;
 for(auto &X : beta){
 if(terminals.count(X)){
 res.insert(X);
 eps_prefix = false;
 break;
 } else {
 for(auto &f : FIRST[X]) if(f!="ε") res.insert(f);
 if(FIRST[X].count("ε")==0) { eps_prefix=false; break; }
 }
 }
 if(eps_prefix) res.insert(a);
 return res;
 };
 auto closure = [&](set<Item> I){
 set<Item> C = I;
 bool changed=true;
 while(changed){
 changed=false;
 vector<Item> cur(C.begin(), C.end());
 for(auto it: cur){
 const Production &prod = P[it.prod];
 if(it.dot < (int)prod.rhs.size()){
 string B = prod.rhs[it.dot];
 if(nonterminals.count(B)){
 vector<string> beta(prod.rhs.begin()+it.dot+1, prod.rhs.end());
 set<string> lookaheads = first_of_string(beta, it.lookahead);
 for(int pi : prods_by_lhs[B]){
 for(auto &b: lookaheads){
 Item newit{pi,0,b};
 if(!C.count(newit)){
 C.insert(newit);
 changed=true;
 }
 }
 }
 }
 }
 }
 }
 return C;
 };
 auto goto_set = [&](set<Item> I, string X){
 set<Item> J;
 for(auto it: I){
 const Production &prod = P[it.prod];
 if(it.dot < (int)prod.rhs.size() && prod.rhs[it.dot]==X){
 J.insert({it.prod, it.dot+1, it.lookahead});
 }
 }
 return closure(J);
 };
 vector< set<Item> > states;
 map< set<Item>, int > state_id;
 set<Item> I0;
 I0.insert({0,0,"$"});
 I0 = closure(I0);
 states.push_back(I0);
 state_id[I0]=0;
 queue<int> q;
 q.push(0);
 while(!q.empty()){
 int i=q.front(); q.pop();
 set<string> symbols;
 for(auto it: states[i]){
 const Production &prod = P[it.prod];
 if(it.dot<(int)prod.rhs.size()) symbols.insert(prod.rhs[it.dot]);
 }
 for(auto X: symbols){
 set<Item> J = goto_set(states[i],X);
 if(J.empty()) continue;
 if(!state_id.count(J)){
 int nid=states.size();
 states.push_back(J);
 state_id[J]=nid;
 q.push(nid);
 }
 }
 }
 // CLR Parsing Table
 map<pair<int,string>,string> ACTION;
 map<pair<int,string>,int> GOTO;
 for(size_t i=0;i<states.size();++i){
 set<string> symbols;
 for(auto it: states[i]){
 const Production &prod = P[it.prod];
 if(it.dot<(int)prod.rhs.size()) symbols.insert(prod.rhs[it.dot]);
 }
 for(auto X: symbols){
 set<Item> J = goto_set(states[i],X);
 if(J.empty()) continue;
 int j=state_id[J];
 if(terminals.count(X)) ACTION[{(int)i,X}] = "s"+to_string(j);
 else GOTO[{(int)i,X}] = j;
 }
 for(auto it: states[i]){
 if(it.dot==(int)P[it.prod].rhs.size()){
 if(P[it.prod].lhs==augStartSymbol && it.lookahead=="$"){
 ACTION[{(int)i,"$"}]="acc";
 } else {
 ACTION[{(int)i,it.lookahead}] = "r"+to_string(it.prod);
 }
 }
 }
 }
 cout<<"CLR Parsing Table:\n";
 vector<string> term_list(terminals.begin(), terminals.end());
 vector<string> nonterm_list;
 for(auto &nt: nonterminals) if(nt != augStartSymbol) nonterm_list.push_back(nt);
 cout<<setw(6)<<"State";
 for(auto &t: term_list) cout<<setw(8)<<t;
 for(auto &nt: nonterm_list) cout<<setw(8)<<nt;
 cout<<"\n";
 for(size_t i=0;i<states.size();++i){
 cout<<setw(6)<<i;
 for(auto &t: term_list){
 string cell="";
 if(ACTION.count({(int)i,t})) cell=ACTION[{(int)i,t}];
 cout<<setw(8)<<cell;
 }
 for(auto &nt: nonterm_list){
 string cell="";
 if(GOTO.count({(int)i,nt})) cell=to_string(GOTO[{(int)i,nt}]);
 cout<<setw(8)<<cell;
 }
 cout<<"\n";
 }
 string input;
 cout<<"Enter input string: ";
 cin>>input;
 vector<string> tokens;
 for(char ch: input){
 string s(1,ch);
 if(terminals.count(s)) tokens.push_back(s);
 }
 tokens.push_back("$");
 vector<int> st; st.push_back(0);
 vector<string> input_buf = tokens;
 cout << "Parsing trace:\n";
 cout << "Step | Stack(states) | Input | Action\n";
 cout << "---------------------------------------------------------------\n";
 int step=0;
 while(true){
 int s = st.back();
 string a = input_buf.front();
 string act="";
 if(ACTION.count({s,a})) act=ACTION[{s,a}];
 else act="err";
 cout<<setw(4)<<step<<" | ";
 string ss;
 for(size_t i=0;i<st.size();++i){
 if(i) ss+=" ";
 ss+=to_string(st[i]);
 }
 cout<<setw(20)<<ss<<" | ";
 string ib;
 for(size_t i=0;i<input_buf.size();++i){
 if(i) ib+=" ";
 ib+=input_buf[i];
 }
 cout<<setw(18)<<ib<<" | ";
 cout<<act<<"\n";
 if(act=="acc"){
 cout<<"Input accepted.\n";
 break;
 } else if(act.size() && act[0]=='s'){
 int tnum=stoi(act.substr(1));
 st.push_back(tnum);
 input_buf.erase(input_buf.begin());
 } else if(act.size() && act[0]=='r'){
 int prod_idx=stoi(act.substr(1));
 int rhs_len = 0;
 if(P[prod_idx].rhs.size() == 1 && P[prod_idx].rhs[0] == "ε") {
 rhs_len = 0; // epsilon production
 } else {
 rhs_len = P[prod_idx].rhs.size();
 }
 for(int k=0;k<rhs_len;++k) if(!st.empty()) st.pop_back();
 int top=st.back();
 string A=P[prod_idx].lhs;
 if(GOTO.count({top,A})){
 st.push_back(GOTO[{top,A}]);
 } else {
 cout<<"ERROR: no GOTO["<<top<<","<<A<<"]\n";
 return 0;
 }
 } else {
 cout<<"ERROR: parsing table indicates no action.\n";
 break;
 }
 step++;
 if(step>200){ cout<<"Too many steps.\n"; break; }
 }
}
Output:
Experiment-11(a) Construct Look-Ahead LR (LALR) parse table using C language.
Aim: To construct a lalr parse table based on the input grammar productions.
Code:
#include <bits/stdc++.h>
using namespace std;
struct Production {
 string lhs;
 vector<string> rhs;
};
struct Item {
 int prod;
 int dot;
 string lookahead;
 bool operator<(const Item& o) const {
 if(prod != o.prod) return prod < o.prod;
 if(dot != o.dot) return dot < o.dot;
 return lookahead < o.lookahead;
 }
};
struct Core {
 int prod, dot;
 bool operator<(const Core& o) const {
 if(prod != o.prod) return prod < o.prod;
 return dot < o.dot;
 }
};
int main() {
 int n;
 cout << "Enter number of productions: ";
 cin >> n;
 cin.ignore();
 vector<Production> P;
 set<string> terminals, nonterminals;
 cout << "Enter productions in the form LHS->RHS (space separated symbols):\n";
 for(int i=0;i<n;i++){
 string line;
 getline(cin,line);
 stringstream ss(line);
 string lhs;
 getline(ss,lhs,'-'); // get LHS
 ss.get(); // remove '>'
 nonterminals.insert(lhs);
 string sym;
 vector<string> rhs;
 while(ss >> sym) rhs.push_back(sym);
 P.push_back({lhs,rhs});
 }
 int t;
 cout << "Enter number of terminals: ";
 cin >> t;
 cout << "Enter terminals separated by space: ";
 for(int i=0;i<t;i++){
 string term;
 cin >> term;
 terminals.insert(term);
 }
 // Build map of productions by LHS
 unordered_map<string, vector<int>> prods_by_lhs;
 for(int i=0;i<(int)P.size();i++) prods_by_lhs[P[i].lhs].push_back(i);
 // Compute FIRST sets
 unordered_map<string,set<string>> FIRST;
 for(auto &x: terminals) FIRST[x]={x};
 for(auto &nt: nonterminals) FIRST[nt]={};
 bool changed=true;
 while(changed){
 changed=false;
 for(auto &prod: P){
 string A=prod.lhs;
 for(auto &sym: prod.rhs){
 if(terminals.count(sym)){
 if(!FIRST[A].count(sym)){ FIRST[A].insert(sym); changed=true; }
 break;
 } else {
 size_t before=FIRST[A].size();
 for(auto &x: FIRST[sym]) if(x!="ε") FIRST[A].insert(x);
 if(FIRST[A].size()!=before) changed=true;
 break;
 }
 }
 }
 }
 auto first_of_string=[&](vector<string> beta, string a){
 set<string> res;
 if(beta.empty()) res.insert(a);
 else {
 string X=beta[0];
 if(terminals.count(X)) res.insert(X);
 else res.insert(FIRST[X].begin(), FIRST[X].end());
 }
 return res;
 };
 auto closure=[&](set<Item> I){
 set<Item> C=I;
 bool changed=true;
 while(changed){
 changed=false;
 vector<Item> cur(C.begin(),C.end());
 for(auto it: cur){
 const Production &prod=P[it.prod];
 if(it.dot<(int)prod.rhs.size()){
 string B=prod.rhs[it.dot];
 if(nonterminals.count(B)){
 vector<string> beta(prod.rhs.begin()+it.dot+1, prod.rhs.end());
 beta.push_back(it.lookahead);
 set<string> lookaheads=first_of_string(beta,it.lookahead);
 for(int pi: prods_by_lhs[B]){
 for(auto &b: lookaheads){
 Item newit{pi,0,b};
 if(!C.count(newit)){ C.insert(newit); changed=true; }
 }
 }
 }
 }
 }
 }
 return C;
 };
 auto goto_set=[&](set<Item> I,string X){
 set<Item> J;
 for(auto it: I){
 const Production &prod=P[it.prod];
 if(it.dot<(int)prod.rhs.size() && prod.rhs[it.dot]==X){
 J.insert({it.prod,it.dot+1,it.lookahead});
 }
 }
 return closure(J);
 };
 // Generate LR(1) states
 vector< set<Item> > lr1_states;
 map< set<Item>, int > lr1_id;
 set<Item> I0={{0,0,"$"}};
 I0=closure(I0);
 lr1_states.push_back(I0);
 lr1_id[I0]=0;
 queue<int> q; q.push(0);
 while(!q.empty()){
 int i=q.front(); q.pop();
 set<string> symbols;
 for(auto it: lr1_states[i]){
 const Production &prod=P[it.prod];
 if(it.dot<(int)prod.rhs.size()) symbols.insert(prod.rhs[it.dot]);
 }
 for(auto X: symbols){
 set<Item> J=goto_set(lr1_states[i],X);
 if(J.empty()) continue;
 if(!lr1_id.count(J)){
 int nid=lr1_states.size();
 lr1_states.push_back(J);
 lr1_id[J]=nid;
 q.push(nid);
 }
 }
 }
 // Merge LALR states
 vector< set<Item> > lalr_states;
 map< set<Core>, int > core_to_id;
 map<int,int> lr1_to_lalr;
 for(size_t i=0;i<lr1_states.size();i++){
 set<Core> core;
 for(auto it: lr1_states[i]) core.insert({it.prod,it.dot});
 if(!core_to_id.count(core)){
 int nid=lalr_states.size();
 set<Item> merged; for(auto it: lr1_states[i]) merged.insert(it);
 lalr_states.push_back(merged);
 core_to_id[core]=nid;
 } else {
 int id=core_to_id[core];
 lalr_states[id].insert(lr1_states[i].begin(), lr1_states[i].end());
 }
 lr1_to_lalr[i]=core_to_id[core];
 }
 // Build ACTION and GOTO tables
 map<pair<int,string>,string> ACTION;
 map<pair<int,string>,int> GOTO;
 for(size_t i=0;i<lr1_states.size();i++){
 int A=lr1_to_lalr[i];
 set<string> symbols;
 for(auto it: lr1_states[i]){
 const Production &prod=P[it.prod];
 if(it.dot<(int)prod.rhs.size()) symbols.insert(prod.rhs[it.dot]);
 }
 for(auto X: symbols){
 set<Item> J=goto_set(lr1_states[i],X);
 if(J.empty()) continue;
 int B=lr1_to_lalr[lr1_id[J]];
 if(terminals.count(X)) ACTION[{A,X}]="s"+to_string(B);
 else GOTO[{A,X}]=B;
 }
 for(auto it: lr1_states[i]){
 if(it.dot==(int)P[it.prod].rhs.size()){
 if(P[it.prod].lhs==P[0].lhs && it.lookahead=="$") ACTION[{A,"$"}]="acc";
 else ACTION[{A,it.lookahead}]="r"+to_string(it.prod);
 }
 }
 }
 // Print parsing table
 cout<<"\nLALR Parsing Table:\n";
 vector<string> term_list(terminals.begin(), terminals.end());
 vector<string> nonterm_list(nonterminals.begin(), nonterminals.end());
 cout<<setw(6)<<"State";
 for(auto &t: term_list) cout<<setw(8)<<t;
 for(auto &nt: nonterm_list) cout<<setw(8)<<nt;
 cout<<"\n";
 for(size_t i=0;i<lalr_states.size();i++){
 cout<<setw(6)<<i;
 for(auto &t: term_list){
 string cell=""; if(ACTION.count({(int)i,t})) cell=ACTION[{(int)i,t}];
 cout<<setw(8)<<cell;
 }
 for(auto &nt: nonterm_list){
 string cell=""; if(GOTO.count({(int)i,nt})) cell=to_string(GOTO[{(int)i,nt}]);
 cout<<setw(8)<<cell;
 }
 cout<<"\n";
 }
 return 0;
}
Output:
Experiment-11(b) Implement the LR parsing algorithm, get both parse table and input string are
inputs. Use C language for implementation.
Aim: To construct the lalr stack trace using the parse table to show whether the input string is
accepted or not.
Code:
#include <bits/stdc++.h>
using namespace std;
struct Production {
 string lhs;
 vector<string> rhs;
};
struct Item {
 int prod;
 int dot;
 string lookahead;
 bool operator<(const Item& o) const {
 if(prod != o.prod) return prod < o.prod;
 if(dot != o.dot) return dot < o.dot;
 return lookahead < o.lookahead;
 }
};
struct Core {
 int prod, dot;
 bool operator<(const Core& o) const {
 if(prod != o.prod) return prod < o.prod;
 return dot < o.dot;
 }
};
int main() {
 int n;
 cout << "Enter number of productions: ";
 cin >> n;
 cin.ignore();
 vector<Production> P;
 set<string> nonterminals;
 cout << "Enter productions (format LHS->RHS space-separated):\n";
 for(int i=0;i<n;i++){
 string line;
 getline(cin,line);
 int pos = line.find("->");
 string lhs = line.substr(0,pos);
 string rhs_string = line.substr(pos+2);
 istringstream iss(rhs_string);
 string sym;
 vector<string> rhs;
 while(iss >> sym) rhs.push_back(sym);
 P.push_back({lhs,rhs});
 nonterminals.insert(lhs);
 }
 int t_count;
 cout << "Enter number of terminals: ";
 cin >> t_count;
 cin.ignore();
 cout << "Enter terminals separated by space: ";
 set<string> terminals;
 string term;
 string line;
 getline(cin,line);
 istringstream iss(line);
 while(iss >> term) terminals.insert(term);
 // Map lhs -> productions
 unordered_map<string, vector<int>> prods_by_lhs;
 for(int i=0;i<(int)P.size();i++) prods_by_lhs[P[i].lhs].push_back(i);
 // Compute FIRST sets
 unordered_map<string,set<string>> FIRST;
 for(auto &t: terminals) FIRST[t]={t};
 for(auto &nt: nonterminals) FIRST[nt]={};
 bool changed=true;
 while(changed){
 changed=false;
 for(auto &prod: P){
 string A=prod.lhs;
 for(auto &sym: prod.rhs){
 if(terminals.count(sym)){
 if(!FIRST[A].count(sym)){ FIRST[A].insert(sym); changed=true; }
 break;
 } else {
 size_t before=FIRST[A].size();
 for(auto &x: FIRST[sym]) if(x!="ε") FIRST[A].insert(x);
 if(FIRST[A].size()!=before) changed=true;
 break;
 }
 }
 }
 }
 auto first_of_string=[&](vector<string> beta, string a){
 set<string> res;
 if(beta.empty()) res.insert(a);
 else {
 string X=beta[0];
 if(terminals.count(X)) res.insert(X);
 else res.insert(FIRST[X].begin(), FIRST[X].end());
 }
 return res;
 };
 auto closure=[&](set<Item> I){
 set<Item> C=I;
 bool changed=true;
 while(changed){
 changed=false;
 vector<Item> cur(C.begin(),C.end());
 for(auto it: cur){
 const Production &prod=P[it.prod];
 if(it.dot<(int)prod.rhs.size()){
 string B=prod.rhs[it.dot];
 if(nonterminals.count(B)){
 vector<string> beta(prod.rhs.begin()+it.dot+1, prod.rhs.end());
 beta.push_back(it.lookahead);
 set<string> lookaheads=first_of_string(beta,it.lookahead);
 for(int pi: prods_by_lhs[B]){
 for(auto &b: lookaheads){
 Item newit{pi,0,b};
 if(!C.count(newit)){ C.insert(newit); changed=true; }
 }
 }
 }
 }
 }
 }
 return C;
 };
 auto goto_set=[&](set<Item> I,string X){
 set<Item> J;
 for(auto it: I){
 const Production &prod=P[it.prod];
 if(it.dot<(int)prod.rhs.size() && prod.rhs[it.dot]==X){
 J.insert({it.prod,it.dot+1,it.lookahead});
 }
 }
 return closure(J);
 };
 // Generate LR(1) states
 vector< set<Item> > lr1_states;
 map< set<Item>, int > lr1_id;
 set<Item> I0={{0,0,"$"}};
 I0=closure(I0);
 lr1_states.push_back(I0);
 lr1_id[I0]=0;
 queue<int> q; q.push(0);
 while(!q.empty()){
 int i=q.front(); q.pop();
 set<string> symbols;
 for(auto it: lr1_states[i]){
 const Production &prod=P[it.prod];
 if(it.dot<(int)prod.rhs.size()) symbols.insert(prod.rhs[it.dot]);
 }
 for(auto X: symbols){
 set<Item> J=goto_set(lr1_states[i],X);
 if(J.empty()) continue;
 if(!lr1_id.count(J)){
 int nid=lr1_states.size();
 lr1_states.push_back(J);
 lr1_id[J]=nid;
 q.push(nid);
 }
 }
 }
 // Merge LALR states
 vector< set<Item> > lalr_states;
 map< set<Core>, int > core_to_id;
 map<int,int> lr1_to_lalr;
 for(size_t i=0;i<lr1_states.size();i++){
 set<Core> core;
 for(auto it: lr1_states[i]) core.insert({it.prod,it.dot});
 if(!core_to_id.count(core)){
 int nid=lalr_states.size();
 set<Item> merged; for(auto it: lr1_states[i]) merged.insert(it);
 lalr_states.push_back(merged);
 core_to_id[core]=nid;
 } else {
 int id=core_to_id[core];
 lalr_states[id].insert(lr1_states[i].begin(), lr1_states[i].end());
 }
 lr1_to_lalr[i]=core_to_id[core];
 }
 // Build ACTION and GOTO tables
 map<pair<int,string>,string> ACTION;
 map<pair<int,string>,int> GOTO;
 for(size_t i=0;i<lr1_states.size();i++){
 int A=lr1_to_lalr[i];
 set<string> symbols;
 for(auto it: lr1_states[i]){
 const Production &prod=P[it.prod];
 if(it.dot<(int)prod.rhs.size()) symbols.insert(prod.rhs[it.dot]);
 }
 for(auto X: symbols){
 set<Item> J=goto_set(lr1_states[i],X);
 if(J.empty()) continue;
 int B=lr1_to_lalr[lr1_id[J]];
 if(terminals.count(X)) ACTION[{A,X}]="s"+to_string(B);
 else GOTO[{A,X}]=B;
 }
 for(auto it: lr1_states[i]){
 if(it.dot==(int)P[it.prod].rhs.size()){
 if(P[it.prod].lhs=="E'" && it.lookahead=="$") ACTION[{A,"$"}]="acc";
 else ACTION[{A,it.lookahead}]="r"+to_string(it.prod);
 }
 }
 }
 // Print LALR parsing table
 cout<<"\nLALR Parsing Table:\n";
 vector<string> term_list(terminals.begin(), terminals.end());
 vector<string> nonterm_list(nonterminals.begin(), nonterminals.end());
 cout<<setw(6)<<"State";
 for(auto &t: term_list) cout<<setw(8)<<t;
 for(auto &nt: nonterm_list) cout<<setw(8)<<nt;
 cout<<"\n";
 for(size_t i=0;i<lalr_states.size();i++){
 cout<<setw(6)<<i;
 for(auto &t: term_list){
 string cell=""; if(ACTION.count({(int)i,t})) cell=ACTION[{(int)i,t}];
 cout<<setw(8)<<cell;
 }
 for(auto &nt: nonterm_list){
 string cell=""; if(GOTO.count({(int)i,nt})) cell=to_string(GOTO[{(int)i,nt}]);
 cout<<setw(8)<<cell;
 }
 cout<<"\n";
 }
 // Parsing input string
 cout<<"\nEnter input string to parse (tokens separated by space, end with $): ";
 string input_line;
 getline(cin, input_line);
 vector<string> tokens;
 istringstream iss2(input_line);
 string tok;
 while(iss2 >> tok) tokens.push_back(tok);
 vector<int> st={0};
 vector<string> input_buf=tokens;
 cout<<"\nParsing trace:\n";
 cout<<"Step | Stack(states) | Input | Action\n";
 cout<<"---------------------------------------------------------------\n";
 int step=0;
 while(true){
 int s=st.back();
 string a=input_buf.front();
 string act="err";
 if(ACTION.count({s,a})) act=ACTION[{s,a}];
 cout<<setw(4)<<step<<" | ";
 { string ss; for(size_t i=0;i<st.size();i++){ if(i) ss+=" "; ss+=to_string(st[i]); } cout<<setw(20)<<ss<<"
| "; }
 { string ib; for(size_t i=0;i<input_buf.size();i++){ if(i) ib+=" "; ib+=input_buf[i]; }
cout<<setw(18)<<ib<<" | "; }
 cout<<act<<"\n";
 if(act=="acc"){ cout<<"Input accepted.\n"; break; }
 else if(act[0]=='s'){
 int t=stoi(act.substr(1));
 st.push_back(t);
 input_buf.erase(input_buf.begin());
 } else if(act[0]=='r'){
 int prod_idx=stoi(act.substr(1));
 int rhs_len=P[prod_idx].rhs.size();
 for(int k=0;k<rhs_len;k++) st.pop_back();
 int top=st.back();
 string A=P[prod_idx].lhs;
 if(GOTO.count({top,A})) st.push_back(GOTO[{top,A}]);
 else { cout<<"ERROR: no GOTO["<<top<<","<<A<<"]\n"; break; }
 } else { cout<<"ERROR: parsing table indicates no action.\n"; break; }
 step++;
 if(step>200){ cout<<"Too many steps.\n"; break; }
 }
 return 0;
}
Output:
