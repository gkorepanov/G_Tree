#include "G_Tree.h"
#include <vector>
#include <string>
#include "../G_Lex/G_Lex.h"
#include "../Tools/Utils.h"


#define INIT_LEX_SEQ_SIZE 100

CTree::CTree(shared_ptr<CNode> root):
    root_(root)
{}

CNodeTwo::CNodeTwo(shared_ptr<CNode> left, shared_ptr<CNode> right) :
    left_(left),
    right_(right)
{}
void CNodeTwo::print(uint_ level /* = 0 */) {
    if (right_) {
        right_->print(level + 1);
        for (uint_ i = 0; i < level; i++)
            printf("\t");
        printf("      /");
    }

    for (uint_ i = 0; i < level; i++)
            printf("\t");
    show();

    if (left_) {
        for (uint_ i = 0; i < level; i++)
            printf("\t");
        printf("     \\");

        left_->print(level + 1);
    }
}

void CNodeLeaf::print(uint_ level /* = 0 */) {
    show();
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
    printf("%Lf", val_);
}
        
CArithmOp::CArithmOp(char type, \
        shared_ptr<::CNode> left, \
        shared_ptr<::CNode> right):

    CNodeTwo(left, right),
    type_(type)
{}

CTreeBuilder::CTreeBuilder() {
    lex_seq_.reserve(INIT_LEX_SEQ_SIZE);
    pos_ = lex_seq_.begin();
}

CTree CTreeBuilder::construct() {
    return CTree(GetExp());
}

shared_ptr<CNode> CTreeBuilder::GetExp() {
    return GetSum();
}

shared_ptr<CNode> CTreeBuilder::GetSum() {
    shared_ptr<CNode> left = GetMul();
    while (pos_->type_ == SUM_OP) {
        pos_++;
        shared_ptr<CNode> right = GetMul();
        if (!right) 
            throw 0; // TODO #0: No right side found
        return make_shared<CNode> (CArithmOp(pos_->text_[0], left, right));
    }
    
    return left;
}


shared_ptr<CNode> CTreeBuilder::GetMul() {
    shared_ptr<CNode> left = GetTok();
    while (pos_->type_ == MUL_OP) {
        pos_++;
        shared_ptr<CNode> right = GetTok();
        if (!right) 
            throw 0; // TODO #0
        return make_shared<CNode> (CArithmOp(pos_->text_[0], left, right));
    }

    return left;
}

shared_ptr<CNode> CTreeBuilder::GetTok() {
    if (pos_->type_ == LBRACKET) {
        pos_++;
        shared_ptr<CNode> res = GetExp();
        if (pos_->type_ != RBRACKET) 
            throw 0; // TODO #1: no closing bracket found
        return res;
    }
    
    if (pos_->type_ != VALUE) 
        throw 0; // Excpected Value found something
    
    return make_shared<CNode> (CVal (stod(pos_->text_)));
}


/* 
EXP: SUM
SUM: MUL {[+-] MUL}*
MUL: TOK {[*\] TOK}*
TOK: (EXP) | NUM
*/
