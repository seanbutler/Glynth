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

static unsigned int uid = 1;

class ASTNode {
public:
    ASTNode(const std::string & N="") : name(N) { id = uid++; }

    virtual ~ASTNode() = default;

    unsigned int getID() { return id;}

    virtual std::string print();                                // USED FOR SIMPLE SERIALIZATION
    virtual std::string diag(unsigned int parentID) = 0;        // USED FOR GENERATING THE GV FILE...
    virtual std::string eval() = 0;                             // USED FOR EMITTING THE ACTUAL INSTRUCTIONS...

    std::string &getName()  { return name; }
    int getNumber()         { return number; }

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

//    std::string &getName() { return name; }
//    std::string name;
};

// ------------------------------------------------------------------------

// AlienAST - statements like "var a"

class AlienAST : public ASTNode {

public:
//    explicit AlienAST(const std::string &N) {}
//    explicit AlienAST(const std::string &N) : name(N) {}
//    std::string &getName() { return name; }
    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

private:
//    std::string name;
};


// ------------------------------------------------------------------------

class VariableDeclarationAST : public ASTNode {

public:
    explicit VariableDeclarationAST(IdentifierAST *I) : ASTNode(""),identifier(I) {}
    virtual std::string print();
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
    BlockAST() = default;
    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

};


// ------------------------------------------------------------------------

// OutputAST - statements like "output(expression);"

class OutputAST : public ASTNode {

public:
    OutputAST(ASTNode *E) : ASTNode(""), expression(E){}

    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

private:
    ASTNode *expression;
};


// ------------------------------------------------------------------------

// MoveAST - statements like "move(expression);"

class MoveAST : public ASTNode {

public:

    MoveAST(ASTNode *E) : ASTNode(""), expression(E){}

    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

private:
    ASTNode *expression;
};



// ------------------------------------------------------------------------

// IfStatementAST - statements like "if(expression){statements}"

class IfStatementAST : public ASTNode {

public:
    ASTNode *expression;
    ASTNode *block;

    IfStatementAST(ASTNode *E, ASTNode *B) : ASTNode(""), expression(E), block(B) {}

//    std::string &getName() { return name; }

    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

private:
//    std::string name;
};

// ------------------------------------------------------------------------

// WhileStatementAST - statements like "while(expression){statements}"

class WhileStatementAST : public ASTNode {

public:
    ASTNode *expression;
    ASTNode *block;

    WhileStatementAST(ASTNode *E, ASTNode *B) : ASTNode(""), expression(E), block(B) {}

//    std::string &getName() { return name; }
    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

private:
//    std::string name;
};


// ------------------------------------------------------------------------

// AssignmentStatementAST -

class AssignmentStatementAST : public ASTNode {

public:
    ASTNode *identifier;
    ASTNode *expression;

    AssignmentStatementAST(ASTNode *I, ASTNode *E) : ASTNode(""), identifier(I), expression(E) {}
    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

private:
};

// ------------------------------------------------------------------------

// NumberAST -

class NumberAST : public ASTNode {

public:
    int val;

    NumberAST(int V) : ASTNode(""), val(V) {}

    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

private:
};

// ------------------------------------------------------------------------

// OperandAST - operators involved in expressions like "A * B or A + C etc"

class BinOperandAST : public ASTNode {

public:
    BinOperandAST(Token O, ASTNode *L, ASTNode *R) : ASTNode(""), op(O), lhs(L), rhs(R) {}

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
