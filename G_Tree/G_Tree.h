#ifndef G_TREE
#define G_TREE

#include <vector>
#include <memory>
#include <string>
#include "../Tools/Utils.h"
#include "../G_Lex/G_Lex.h"

// One has to put that in classes if he doesn't want it
using namespace std;

// Type of numbers in tree
typedef long double Tree_T;

class CNode {
public:
    // virtual CNode* derivate();
    virtual void show() = 0;
    virtual void print(uint_ level = 0) = 0;
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
class CNodeLeaf : public CNode {
public:
    void print(uint_ level = 0);
};

// node with two children
class CNodeTwo : public CNode {
protected:
    shared_ptr<CNode> left_;
    shared_ptr<CNode> right_;
public:
    CNodeTwo(shared_ptr<CNode> left, shared_ptr<CNode> right);
    void print(uint_ level = 0);
};

class CArithmOp : public CNodeTwo {
private:
    char type_; // * | / | - | +
public:
    CArithmOp(char type, \
            shared_ptr<CNode> left, \
            shared_ptr<CNode> right);

    void show();
};

class CVar : public CNodeLeaf {
private:
    string name;
    uint_ ind_;
    Tree_T val_;
public:
    void show();
    Tree_T getval();
    Tree_T setval(Tree_T newval);
};

class CVal : public CNodeLeaf {
private:
    Tree_T val_;
public:
    CVal(Tree_T val);
    void show();
};

class CTreeBuilder {
private:
    shared_ptr<CNode> GetExp();
    shared_ptr<CNode> GetSum();
    shared_ptr<CNode> GetMul();
    shared_ptr<CNode> GetTok();
    shared_ptr<CNode> GetStr();
    vector<CLex>::iterator pos_;
public:
    explicit CTreeBuilder();
    CTree construct();
    vector<CLex> lex_seq_;
};

#endif
