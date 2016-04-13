#include "G_Tree.h"
#include <vector>
#include <string>
#include "../G_Lex/G_Lex.h"
#include "../Tools/Utils.h"


#define INIT_LEX_SEQ_SIZE 100

using namespace std;

CTree::CTree(shared_ptr<CNode> root):
    root_(root)
{}

void CNodeTwo::print(uint level /* = 0 */) {
    if (right_) {
        right_->print(level + 1);
        for (uint i = 0; i < level; i++)
            printf("\t");
        printf("      /");
    }

    for (uint i = 0; i < level; i++)
            printf("\t");
    show();

    if (left_) {
        for (uint i = 0; i < level; i++)
            printf("\t");
        printf("     \\");

        left_->print(level + 1);
    }
}

void CNodeLeaf::print(uint level /* = 0 */) {
    show();
}

void CArithmOp::show() {
    printf("%c", type_);
}

void CVar::show() {
    printf("%s", name.c_str());
}

void CVal::show() {
    printf("%Lf", val_);
}
        
CArithmOp::CArithmOp(char type, \
        shared_ptr<CNode> left, \
        shared_ptr<CNode> right):

    type_(type),
    left_(left),
    right_(right)
{}

CTreeBuilder::CTreeBuilder() {
    lex_seq.reserve(INIT_LEX_SEQ_SIZE);
    pos = lex_seq.begin();
}

shared_ptr<CNode> CTreeBuilder::construct() {
    return CTree(GetExp());
}

shared_ptr<CNode> CTreeBuilder::GetExp() {
    return GetSum();
}

shared_ptr<CNode> CTreeBuilder::GetSum() {
    CNode* left = GetMul();
    if (pos->type_ == SUM_OP) {
        pos++;
        CNode* right = GetMul();
        if (!right) 
            throw 0; // TODO #0: No right side found
        return new CArithmOp(pos->text_, left, right);
    }
    
    return left;
}


shared_ptr<CNode> CTreeBuilder::GetMul() {
    CNode* left = GetTok();
    if (pos->type_ == MUL_UP) {
        pos ++;
        CNode* right = GetTok();
        if (!right) 
            throw 0; // TODO #0
        return new CArithmOp(pos->text_, left, right);
    }

    return left;
}

shared_ptr<CNode> CTreeBuilder::GetTok() {
    if (pos->type_ == LBRACKET) {
        pos++;
        CNode* res = GetExp();
        if (pos->type_ != RBRACKET) 
            throw 0; // TODO #1: no closing bracket found
        return res;
    }
    
    if (pos->type_ != VALUE) {
        throw 0; // Excpected Value found something
    
    return new CVal (stod(pos->text_));
}





/* 
EXP: SUM
SUM: MUL {[+-] MUL}*
MUL: TOK {[*\] TOK}*
TOK: (EXP) | NUM
*/
