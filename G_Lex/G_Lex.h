#ifndef G_LEX
#define G_LEX

#include <string>

using namespace std;

extern int yylex(void);
extern char* yytext;
extern FILE* yyin;

enum LEX_T {
    OPERATOR = 1,
    VALUE = 2,
    WORD = 3, // either variable or function
    LBRACKET = 4,
    RBRACKET = 5
};

class CLex {
private:
    LEX_T type_;
    string text_;

public:
    CLex(LEX_T type, char* text):
        type_(type),
        text_(text)
    {}
};

#endif
