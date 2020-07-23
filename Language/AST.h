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

const std::string CONSANANTS = "BCDFGHJKLMNPQRSTVWXYZ";
const std::string VOWELS = "AEIOU";

static std::string pronouncableRandomString(unsigned int l=8){
    std::string uuid = std::string(l,' ');

    for(int i=0;i<l-1;i+=2){
        uuid[i] = CONSANANTS[rand() % 21];
        uuid[i+1] = VOWELS[rand() % 5];
    }
    return uuid;
}
// ------------------------------------------------------------------------


static std::string getUniqueIdentifier();

// ------------------------------------------------------------------------

static unsigned int uid = 1;

class ASTNode {
public:
    ASTNode() { id = uid++; }
    virtual ~ASTNode() {}
    virtual void print() = 0;
    virtual std::string diag(unsigned int parentID) = 0;
    virtual std::string eval() = 0;
    unsigned int id;
};

// ------------------------------------------------------------------------

// IdentifierAST - statements like "var a"

class IdentifierAST : public ASTNode {

public:
    IdentifierAST(const std::string &N) : name(N) {}
    std::string &getName() { return name; }
    virtual void print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

private:
    std::string name;
};

// ------------------------------------------------------------------------

class VariableDeclarationAST : public ASTNode {

public:
    VariableDeclarationAST(IdentifierAST *I) : identifier(I) {}
    virtual void print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

private:
    IdentifierAST *identifier;
};


// ------------------------------------------------------------------------

// BlockAST - for lists of statements between { and } tokens

class BlockAST : public ASTNode {

public:
    std::vector<ASTNode *> statements;
    BlockAST() {};
    virtual void print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

private:
    std::vector<ASTNode *> children;
};


// ------------------------------------------------------------------------

// OutputAST - statements like "output(expression);"

class OutputAST : public ASTNode {

public:
    ASTNode *expression;

    OutputAST(ASTNode *E) : expression(E){}

    std::string &getName() { return name; }

    virtual void print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

private:
    std::string name;
};


// ------------------------------------------------------------------------

// IfStatementAST - statements like "if(expression){statements}"

class IfStatementAST : public ASTNode {

public:
    ASTNode *expression;
    ASTNode *block;

    IfStatementAST(ASTNode *E, ASTNode *B) : expression(E), block(B) {}

    std::string &getName() { return name; }

    virtual void print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

private:
    std::string name;
};

// ------------------------------------------------------------------------

// WhileStatementAST - statements like "while(expression){statements}"

class WhileStatementAST : public ASTNode {

public:
    ASTNode *expression;
    ASTNode *block;

    WhileStatementAST(ASTNode *E, ASTNode *B) : expression(E), block(B) {}

    std::string &getName() { return name; }
    virtual void print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

private:
    std::string name;
};


// ------------------------------------------------------------------------

// AssignmentStatementAST -

class AssignmentStatementAST : public ASTNode {

public:
    ASTNode *identifier;
    ASTNode *expression;

    AssignmentStatementAST(ASTNode *I, ASTNode *E) : identifier(I), expression(E) {}
    std::string &getName() { return name; }
    virtual void print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

private:
    std::string name;
};

// ------------------------------------------------------------------------

// NumberAST -

class NumberAST : public ASTNode {

public:
    int val;

    NumberAST(int V) : val(V) {}

    std::string &getName() { return name; }
    virtual void print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

private:
    std::string name;
};

// ------------------------------------------------------------------------

// OperandAST - operators involved in expressions like "A * B or A + C etc"

class BinOperandAST : public ASTNode {

public:
    BinOperandAST(Token O, ASTNode *L, ASTNode *R) : op(O), lhs(L), rhs(R) {}

    Token op;
    ASTNode *lhs;
    ASTNode *rhs;

    std::string &getName() { return name; }
    virtual void print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

private:
    std::string name;
};





// ------------------------------------------------------------------------

// YieldAST -

class YieldAST : public ASTNode {

public:
    YieldAST() {}

    std::string &getName() { return name; }
    virtual void print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

private:
    std::string name;
};


// ------------------------------------------------------------------------



#endif //GLYNTH_AST_H
