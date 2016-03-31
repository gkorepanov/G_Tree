#include <string.h>
#include <stdio.h>
#include "tools/alerts.h"
#include "G_lex/G_lex.h"
#include "G_tree/G_tree.h"

// make lex know input stream
void proceed(char* filename) {
    if (!strcmp(argv[1], "stdin")) 
        yyin = stdin;
    else {
        FILE* _finput = fopen(argv[1], "r");
        if (!_finput) 
            USERERR("Couldn't open file \"%s\"" argv[1])

        yyin = _finput;
    }

    vector<CLex> lex_seq;
    LEX_T res;

    while (res = static_cast<LEX_T> yylex()){
        Clex cur_lex(res, yytext);
        lex_seq.push_back(cur_lex);
        printf("%s\n", yytext);
    }

    CTree tree;
    tree.construct(lex_seq);

    fclose(_finput);

}

int main(int argc, char** argv) {
    if (argc != 2)
        USERERR("Usage: %s \"filename\"/stdin", argv[0]);
    
    proceed(argv[1]);

    return 0;
}

