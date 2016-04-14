#include <string.h>
#include <stdio.h>
#include "Tools/Alerts.h"
#include "G_Lex/G_Lex.h"
#include "G_Tree/G_Tree.h"
#include <vector>

// make lex know input stream
void proceed(char* filename) {
    FILE* _finput = NULL;

    if (!strcmp(filename, "stdin")) 
        yyin = stdin;
    else {
        _finput = fopen(filename, "r");
        if (!_finput) 
            USERERR("Couldn't open file \"%s\"", filename)

        yyin = _finput;
    }

    vector<CLex> lex_seq;
    int res;
    
    CTreeBuilder TreeBuilder;

    while ( (res = yylex()) ) {
        CLex cur_lex(static_cast<LEX_T> (res), yytext);
        TreeBuilder.lex_seq_.push_back(cur_lex);
        printf("\"%s\"\n", yytext);
    }
    TreeBuilder.lex_seq_.push_back(CLex(static_cast<LEX_T> (END), ""));

    CTree Tree = TreeBuilder.construct();
	
    print_line();
    Tree.show();

    if (_finput)
        fclose(_finput);
}

int main(int argc, char** argv) {
    if (argc != 2)
        USERERR("Usage: %s \"filename\"/stdin", argv[0]);
    
    proceed(argv[1]);

    return 0;
}

