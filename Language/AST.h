//
// Created by sean on 17/06/2020.
//

#ifndef GLYNTH_AST_H
#define GLYNTH_AST_H

#include <string>
#include <vector>
#include <sstream>
#include "Tokens.h"

#include <uuid/uuid.h>


// ------------------------------------------------------------------------

//const std::string CONSANANTS = "BCDFGHJKLMNPQRSTVWXYZ";
//const std::string VOWELS = "AEIOU";
//
//static std::string pronouncableRandomString(unsigned int l=8){
//    std::string uuid = std::string(l,' ');
//
//    for(int i=0;i<l-1;i+=2){
//        uuid[i] = CONSANANTS[rand() % 21];
//        uuid[i+1] = VOWELS[rand() % 5];
//    }
//    return uuid;
//}

// ------------------------------------------------------------------------

static std::string getUniqueIdentifier();

// ------------------------------------------------------------------------

// class NodeType  enum : int {
//    Node,
//    Identifier,
//    AlienVar,
//    VariableDeclaration,
//
//};

// ------------------------------------------------------------------------

static unsigned int uid = 1;

class ASTNode {
public:
    ASTNode(const std::string & N="") : id(uid++), name(N) {}
    virtual ~ASTNode() = default;

    unsigned int getID()    { return id; }
    std::string &getName()  { return name; }

    int getNumber()         { return number; }
    void setNumber(int N)   { number = N; }

    virtual std::string print();                                // USED FOR SIMPLE SERIALIZATION
    virtual std::string diag(unsigned int parentID) = 0;        // USED FOR GENERATING THE GV FILE...
    virtual std::string eval() = 0;                             // USED FOR EMITTING THE ACTUAL INSTRUCTIONS...

    std::vector<ASTNode*>children;

private:
    unsigned int id;
    std::string name;
    int number;
};

// ------------------------------------------------------------------------

class IdentifierAST : public ASTNode {

public:
    explicit IdentifierAST(const std::string &N) : ASTNode(N) {}
    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();
};

// ------------------------------------------------------------------------

class AlienVarAST : public ASTNode {

public:
    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();
};

// ------------------------------------------------------------------------

class VariableDeclarationAST : public ASTNode {

public:
    explicit VariableDeclarationAST(IdentifierAST *I)
        : ASTNode()
        , identifier(I)
    {
        ASTNode::children.push_back(I);
    }

    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

private:
    IdentifierAST *identifier;
};


// ------------------------------------------------------------------------

class BlockAST : public ASTNode {

public:
    BlockAST()
        : ASTNode()
    {

    }

    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

//    std::vector<ASTNode *> statements;
};

// ------------------------------------------------------------------------

class OutputAST : public ASTNode {

public:
    OutputAST(ASTNode *E)
        : ASTNode()
        , expression(E)
    {
        ASTNode::children.push_back(E);
    }

    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

private:
    ASTNode *expression;
};

// ------------------------------------------------------------------------

class MoveAST : public ASTNode {

public:
    MoveAST(ASTNode *E)
        : ASTNode()
    {
        children.push_back(E);
    }

    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

    ASTNode * getExpression()   { return children[0];}
};


class RandFuncAST : public ASTNode {

public:
    RandFuncAST()
        : ASTNode()
    {
    }

    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

private:
};



// ------------------------------------------------------------------------

class IfStatementAST : public ASTNode {

public:
    IfStatementAST(ASTNode *E, ASTNode *B)
        : ASTNode()
    {
        children.push_back(E);
        children.push_back(B);
    }

    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

    ASTNode * getExpression()   { return children[0];}
    ASTNode * getBlock()        { return children[1];}

private:


};

// ------------------------------------------------------------------------

class WhileStatementAST : public ASTNode {

public:
    WhileStatementAST(ASTNode *E, ASTNode *B)
    : ASTNode()
    {
        children.push_back(E);
        children.push_back(B);
    }

    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

    ASTNode * getExpression()   { return children[0];}
    ASTNode * getBlock()        { return children[1];}
};


// ------------------------------------------------------------------------

class AssignmentStatementAST : public ASTNode {

public:
    AssignmentStatementAST(ASTNode *I, ASTNode *E)
        : ASTNode()
    {
        children.push_back(I);
        children.push_back(E);
    }

    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

    ASTNode * getIdentifier(){return children[0];}
    ASTNode * getExpression(){return children[1];}

};

// ------------------------------------------------------------------------

// NumberAST -

class NumberAST : public ASTNode {

public:
    NumberAST(int V) : ASTNode() {
        setNumber(V);
    }

    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

};

// ------------------------------------------------------------------------

// OperandAST - operators involved in expressions like "A * B or A + C etc"

class BinOperandAST : public ASTNode {

public:
    BinOperandAST(Token O, ASTNode *L, ASTNode *R) : ASTNode(), op(O), lhs(L), rhs(R) {}

    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

    Token op;
    ASTNode *lhs;
    ASTNode *rhs;

private:
};

// ------------------------------------------------------------------------

// YieldAST -

class YieldAST : public ASTNode {

public:
    YieldAST() = default;
    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();
};

// ------------------------------------------------------------------------

#endif //GLYNTH_AST_H
