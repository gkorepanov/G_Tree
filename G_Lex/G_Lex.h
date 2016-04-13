#ifndef G_LEX
#define G_LEX

#include <string>

using namespace std;

extern int yylex(void);
extern char* yytext;
extern FILE* yyin;

enum LEX_T {
    SUM_OP = 1,
    MUL_OP = 2,
    VALUE = 3,
    WORD = 4,
    LBRACKET = 5,
    RBRACKET = 6,
};

class CLex {
public:
    LEX_T type_;
    string text_;

    CLex(LEX_T type, char* text):
        type_(type),
        text_(text)
    {}
};

#endif
