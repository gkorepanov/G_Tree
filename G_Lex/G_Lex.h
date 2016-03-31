#ifndef G_LEX
#define G_LEX

#include <string>

using namespace std;

extern int yylex(void);
extern char* yytext;

enum LEX_T {
    OPERATOR,
    VALUE,
    WORD, // either variable or function
    LBRACKET,
    RBRACKET
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
