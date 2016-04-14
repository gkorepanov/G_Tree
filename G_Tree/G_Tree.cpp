#include "G_Tree.h"
#include <vector>
#include <string>
#include "../G_Lex/G_Lex.h"
#include "../Tools/Utils.h"
#include "../Tools/Alerts.h"

#define INIT_LEX_SEQ_SIZE 100

CTree::CTree(shared_ptr<CNode> root):
    root_(root)
{}

void CTree::show() {
    root_->print();
}

CNodeTwo::CNodeTwo(shared_ptr<CNode> left, shared_ptr<CNode> right) :
    left_(left),
    right_(right)
{}
void CNodeTwo::print(uint_ level /* = 0 */) {
    if (right_) {
        right_->print(level + 1);
        for (uint_ i = 0; i < level; i++)
            printf("\t");
        printf("      /\n");
    }

    for (uint_ i = 0; i < level; i++)
            printf("\t");
    show();
    printf("\n");

    if (left_) {
        for (uint_ i = 0; i < level; i++)
            printf("\t");
        printf("      \\\n");

        left_->print(level + 1);
    }
}

void CNodeLeaf::print(uint_ level /* = 0 */) {
    for (uint_ i = 0; i < level; i++)
        printf("\t");

    show();
    printf("\n");
}

void CArithmOp::show() {
    printf("%c", type_);
}

void CVar::show() {
    printf("%s", name.c_str());
}

CVal::CVal(Tree_T val):
    val_(val)
{}

void CVal::show() {
    printf("%.2Lf", val_);
}
        
CArithmOp::CArithmOp(char type, \
        shared_ptr<CNode> left, \
        shared_ptr<CNode> right):

    CNodeTwo(left, right),
    type_(type)
{}

CTreeBuilder::CTreeBuilder() {
    lex_seq_.reserve(INIT_LEX_SEQ_SIZE);
    pos_ = lex_seq_.begin();
}

CTree CTreeBuilder::construct() {
    return CTree(GetStr());
}

shared_ptr<CNode> CTreeBuilder::GetStr() {
    shared_ptr<CNode> res = GetExp();

    if (pos_->type_ != END)
        throw runtime_error(string("Incorrect abruption: ") + pos_->text_);   // TODO 

    pos_++;
    return res;
}


shared_ptr<CNode> CTreeBuilder::GetExp() {
    return GetSum();
}

shared_ptr<CNode> CTreeBuilder::GetSum() {
    shared_ptr<CNode> left = GetMul();

    DBGPRINT("In getsum");
    IFDEBUG(left->print(););

    while (pos_->type_ == SUM_OP) {
        char type = pos_->text_[0];

        pos_++;
        shared_ptr<CNode> right = GetMul();

        if (!right) 
            throw runtime_error("No right side found when parsing +-"); // TODO

        left = shared_ptr<CNode> (new CArithmOp(type, left, right));
    }
    
    return left;
}


shared_ptr<CNode> CTreeBuilder::GetMul() {
    shared_ptr<CNode> left = GetTok();
    
    DBGPRINT("In getmul");
    IFDEBUG(left->print(););

    while (pos_->type_ == MUL_OP) {
        char type = pos_->text_[0];

        pos_++;
        shared_ptr<CNode> right = GetTok();

        if (!right) 
            throw runtime_error("No right side found when parsing */"); // TODO

        left = shared_ptr<CNode> (new CArithmOp(type, left, right));
    }

    return left;
}

shared_ptr<CNode> CTreeBuilder::GetTok() {
    if (pos_->type_ == LBRACKET) {
        DBGPRINT("In GetTok");
        pos_++;
        shared_ptr<CNode> res = GetExp();

        if (pos_->type_ != RBRACKET) 
            throw 0; // TODO #1: no closing bracket found
        pos_++;
        DBGPRINT("VAL: %s", pos_->text_.c_str());
        return res;
    }
    
    if (pos_->type_ != VALUE) 
        throw 0; // Excpected Value found something
    
    DBGPRINT("In GetTok, got %s", pos_->text_.c_str());
    
    shared_ptr<CNode> res (new CVal (stod(pos_->text_)));
    pos_++;
    return res;
}


/* 
STR: EXP END
EXP: SUM END
SUM: MUL {[+-] MUL}*
MUL: TOK {[*\] TOK}*
TOK: (EXP) | NUM
*/
