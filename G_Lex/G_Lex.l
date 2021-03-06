%{
#include "G_Lex.h"
#include "../Tools/Alerts.h"
%}

%option noyywrap
%option nounput


%%
[ \t]+                      ;
[\n]                        { if (yyin == stdin) return 0; }
[a-zA-Z][a-zA-Z0-9]*        return WORD;
[\(]                        return LBRACKET;
[\)]                        return RBRACKET;
[0-9]+                      return VALUE;
[*/]                        return MUL_OP;
[+\-]                       return SUM_OP;

.                           { USERERR("Unexpected symbol found: \"%s\"", yytext) }

%%
