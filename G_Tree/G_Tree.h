#ifndef G_TREE
#define G_TREE

#include <vector>
#include <memory>
#include <string>
#include "../G_Lex/G_Lex.h"

// Type of numbers in tree
typedef long double Tree_T;

class CNode {
public:
    // virtual CNode* derivate();
    virtual void show();
    virtual void print(uint level = 0);
};

class CTree {
private:
    shared_ptr<CNode> root_;
public:
    CTree(shared_ptr<CNode> root);
    void show();
    CTree derivate();
};

/*
// nodes with one child
class CNodeOne : CNode {
private:
    shared_ptr <CNode> child_;
};
*/

// leaf node
class CNodeLeaf : CNode {
public:
    void print(uint level = 0);
};

// node with two children
class CNodeTwo : CNode {
public:
    void print(uint level = 0);
private:
    shared_ptr <CNode> left_;
    shared_ptr <CNode> right_;
};

class CArithmOp : CNodeTwo {
private:
    char type_; // * | / | - | +
public:
    CArithmOp(char type, \
            shared_ptr<CNode> left, \
            shared_ptr<CNode> right);
    void show();
};

class CVar : CNodeLeaf {
private:
    string name;
    uint ind_;
    Tree_T val_;
public:
    void show();
    Tree_T getval();
    Tree_T setval(Tree_T newval);
};

class CVal : CNodeLeaf {
public:
    void show();
private:
    Tree_T val_;
};

class CTreeBuilder {
public:
    explicit CTreeBuilder();
    CTree construct();
    vector<CLex> lex_seq_;

private:
    shared_ptr<CNode> GetExp();
    shared_ptr<CNode> GetSum();
    shared_ptr<CNode> GetMul();
    shared_ptr<CNode> GetTok();

    vector<CLex>::iterator pos_;
};

#endif
