#ifndef G_LEX
#define G_LEX

extern int yylex(void);
extern char* yytext;

enum LEX_T {
    OPERATOR,
    VALUE,
    WORD, // either variable or function
    LBRACKET,
    RBRACKET
}

class CLex {
private:
    LEX_T type_;
    string text_;

public:
    Clex(LEX_T type, char* text):
        type_(type),
        text_(text)
    {}
}

#endif
