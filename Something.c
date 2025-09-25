
---

Experiment 12: Simple Calculator using LEX & YACC

calc.l (LEX code)

%{
#include "y.tab.h"
%}

%%
[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[+\-*/()]   { return yytext[0]; }
[ \t\n]     { /* ignore whitespace */ }
.           { return yytext[0]; }
%%
int yywrap() { return 1; }

calc.y (YACC code for calculator)

%{
#include <stdio.h>
#include <stdlib.h>
%}

%token NUMBER
%left '+' '-'
%left '*' '/'
%right UMINUS

%%
expr:
      expr '+' expr   { printf("%d\n", $1 + $3); }
    | expr '-' expr   { printf("%d\n", $1 - $3); }
    | expr '*' expr   { printf("%d\n", $1 * $3); }
    | expr '/' expr   { printf("%d\n", $1 / $3); }
    | '-' expr %prec UMINUS { $$ = -$2; }
    | '(' expr ')'    { $$ = $2; }
    | NUMBER          { $$ = $1; }
    ;
%%
int main() { return yyparse(); }
int yyerror(char *s) { printf("Error: %s\n", s); return 0; }


---

Experiment 13: Infix to Postfix using LEX & YACC

infix.l

%{
#include "y.tab.h"
%}

%%
[0-9]+      { yylval = strdup(yytext); return NUMBER; }
[+\-*/()]   { return yytext[0]; }
[ \t\n]     ;
.           { return yytext[0]; }
%%
int yywrap() { return 1; }

infix.y

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

%token NUMBER
%left '+' '-'
%left '*' '/'
%right UMINUS

%%
expr:
      expr '+' expr   { printf("%s %s + ", $1, $3); }
    | expr '-' expr   { printf("%s %s - ", $1, $3); }
    | expr '*' expr   { printf("%s %s * ", $1, $3); }
    | expr '/' expr   { printf("%s %s / ", $1, $3); }
    | '-' expr %prec UMINUS { printf("%s ~ ", $2); }
    | '(' expr ')'    { /* parentheses ignored */ }
    | NUMBER          { printf("%s ", $1); }
    ;
%%
int main() { return yyparse(); }
int yyerror(char *s) { printf("Error: %s\n", s); return 0; }


---

Experiment 14: Recognizing CFG Languages with LEX & YACC

We must accept/reject strings based on grammar.

Grammar 1: L(G) = { aⁿ bᵐ | m ≠ n }

g1.l

%{
#include "y.tab.h"
%}

%%
a   { return 'a'; }
b   { return 'b'; }
\n  { return '\n'; }
.   ;
%%
int yywrap() { return 1; }

g1.y

%{
#include <stdio.h>
int acount=0, bcount=0;
%}

%%
start:
    string '\n' { 
        if (acount != bcount) 
            printf("Accepted: a^n b^m with n != m\n"); 
        else 
            printf("Rejected\n");
        acount=0; bcount=0;
    }
    ;

string:
      string 'a' { acount++; }
    | string 'b' { bcount++; }
    | /* empty */
    ;
%%
int main() { return yyparse(); }
int yyerror(char *s) { printf("Error: %s\n", s); return 0; }


---

Grammar 2: L(G) = { ab (bbaa)ⁿ bba (ba)ⁿ | n ≥ 0 }

g2.l

%{
#include "y.tab.h"
%}

%%
a   { return 'a'; }
b   { return 'b'; }
\n  { return '\n'; }
.   ;
%%
int yywrap() { return 1; }

g2.y

%{
#include <stdio.h>
%}

%%
start:
      'a' 'b' bbpart bbapart '\n' { printf("Accepted\n"); }
    ;

bbpart:
      /* empty */
    | bbpart 'b' 'b' 'a' 'a'
    ;

bbapart:
      'b' 'b' 'a' bapart
    ;

bapart:
      /* empty */
    | bapart 'b' 'a'
    ;
%%
int main() { return yyparse(); }
int yyerror(char *s) { printf("Rejected\n"); return 0; }


---

✅ With these .l and .y files, you can build:

lex file.l
yacc -d file.y
cc lex.yy.c y.tab.c -o output
./output


---

Do you want me to also combine experiments 12, 13, 14 into a single .l file each (standalone without YACC), or are the paired .l + .y solutions okay for your submission?

