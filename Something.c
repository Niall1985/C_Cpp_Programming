// exp12
cat calc.l
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

cat calc.y
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



//exp13
cat infix.l
%{
#include "infix.tab.h"
#include <stdlib.h>
#include <string.h>
%}

%%
[0-9]+      { yylval.str = strdup(yytext); return NUMBER; }
[+\-*/()]   { return yytext[0]; }
[ \t]+      ;
\n          { return '\n'; }
.           { return yytext[0]; }
%%

int yywrap(void) { return 1; }

cat infix.y
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
int yyerror(const char *s);
%}

%union {
    char* str;
}

%token <str> NUMBER
%type <str> expr

%left '+' '-'
%left '*' '/'
%right UMINUS

%%

input:
      /* empty */
    | input line
    ;

line:
      expr '\n'  { printf("%s\n", $1); free($1); }
    | '\n'       { }
    ;

expr:
      expr '+' expr   { asprintf(&$$, "%s %s +", $1, $3); free($1); free($3); }
    | expr '-' expr   { asprintf(&$$, "%s %s -", $1, $3); free($1); free($3); }
    | expr '*' expr   { asprintf(&$$, "%s %s *", $1, $3); free($1); free($3); }
    | expr '/' expr   { asprintf(&$$, "%s %s /", $1, $3); free($1); free($3); }
    | '-' expr %prec UMINUS { asprintf(&$$, "%s neg", $2); free($2); }
    | '(' expr ')'    { $$ = $2; }
    | NUMBER          { $$ = $1; }
    ;

%%

int main() {
    yyparse();
    return 0;
}

int yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}


// exp14
cat g1.l
%{
#include "g1.tab.h"
%}

%%
a   { return 'a'; }
b   { return 'b'; }
\n  { return '\n'; }
[ \t] ;
.   ;
%%

int yywrap() { return 1; }

cat g1.y
%{
#include <stdio.h>
int acount=0, bcount=0;
%}

%%

start:
      line_list
    ;

line_list:
      line_list line
    | /* empty */
    ;

line:
      a_seq b_seq '\n' {
          if (acount != bcount)
              printf("Accepted: a^n b^m with n != m\n");
          else
              printf("Rejected\n");
          acount=0; bcount=0;
      }
    ;

a_seq:
      /* empty */
    | a_seq 'a' { acount++; }
    ;

b_seq:
      /* empty */
    | b_seq 'b' { bcount++; }
    ;

%%

int main() { return yyparse(); }
int yyerror(const char *s) { printf("Rejected\n"); return 0; }


cat g2.l
%{
#include "g2.tab.h"
%}

%%
a   { return 'a'; }
b   { return 'b'; }
\n  { return '\n'; }
[ \t] ;
.   ;
%%

int yywrap() { return 1; }

cat g2.l
%{
#include "g2.tab.h"
%}

%%
a   { return 'a'; }
b   { return 'b'; }
\n  { return '\n'; }
[ \t] ;
.   ;
%%

int yywrap() { return 1; }
student@AB1605B025:~$ cat g2.y
%{
#include <stdio.h>
%}

%%

start:
      line_list
    ;

line_list:
      line_list line
    | /* empty */
    ;

line:
      'a' 'b' bb_seq 'b' 'b' 'a' ba_seq '\n' { printf("Accepted\n"); }
    ;

bb_seq:
      /* empty */
    | bb_seq 'b' 'b' 'a' 'a'
    ;

ba_seq:
      /* empty */
    | ba_seq 'b' 'a'
    ;

%%

int main() { return yyparse(); }
int yyerror(const char *s) { printf("Rejected\n"); return 0; }
