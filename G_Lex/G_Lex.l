%{
#include "G_lex.h"
%}

%%
[ \t\n]+                ;
[a-zA-Z][a-zA-Z0-9]*    return WORD;
[\(]                    return LBRACKET;
[\)]                    return RBRACKET;
[0-9]+                  return VALUE;
[*\-^+]                 return OPERATOR;

%%
