//
// Created by sean on 17/06/2020.
//

#pragma once

//#include <uuid/uuid.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "Tokens.h"

//#include "../Genetics/Evolution.h"
//#include "../Genetics/Mutations/Mutator.h"
//#include "../Genetics/Mutations/Mutagen.h"

namespace Genetics {
    class MutationVisitor;
}

static std::string getUniqueIdentifier();

enum class CompatibilityType
{
    none,
    all,
    blockStart,
    var

};

// ------------------------------------------------------------------------

static unsigned int uid = 1;

class ASTNode {
public:
    ASTNode(const std::string & N="") : id(uid++), name(N), number(0){

    }

    virtual ~ASTNode() = default;

    virtual void Accept( Genetics::MutationVisitor* visitor)  {
        std::cout << "Accept( Genetics::MutationVisitor* visitor)" << std::endl;
    };

    unsigned int getID()            { return id; }
    void GenerateNewID()            {id = uid++;}
    std::string &getName()          { return name; }

    int getNumber() const           { return number; }
    void setNumber(int N)           { number = N; }
    CompatibilityType GetCompType() {return compatibility; };

    virtual std::string print();                                // USED FOR SIMPLE SERIALIZATION
    virtual std::string diag(unsigned int parentID) {};        // USED FOR GENERATING THE GV FILE...
    virtual std::string eval() {};                             // USED FOR EMITTING THE ACTUAL INSTRUCTIONS...

    std::vector<ASTNode*>children;

protected:
    CompatibilityType compatibility = CompatibilityType::none;

private:
    unsigned int id;
    std::string name;
    int number;

};

// ------------------------------------------------------------------------

class IdentifierAST : public ASTNode {

public:
    IdentifierAST() {};

    explicit IdentifierAST(const std::string &N) : ASTNode(N) {}

    virtual void Accept( Genetics::MutationVisitor *visitor)  override ;

    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();
};

// ------------------------------------------------------------------------

class AlienVarAST : public ASTNode {

public:
    AlienVarAST()
    {
        compatibility = CompatibilityType::var;
    }

    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();
};

// ------------------------------------------------------------------------

class VariableDeclarationAST : public ASTNode {

public:
    explicit VariableDeclarationAST(ASTNode *I)
        : ASTNode()
        , identifier(I)
    {
        ASTNode::children.push_back(I);
    }


    virtual void Accept( Genetics::MutationVisitor *visitor) ;

    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

private:
    ASTNode *identifier;
};


// ------------------------------------------------------------------------

class BlockAST : public ASTNode {

public:
    BlockAST()
        : ASTNode()
    {

    }

    virtual void Accept( Genetics::MutationVisitor *visitor) ;

    virtual std::string print() override;
    virtual std::string diag(unsigned int parentID) override;
    virtual std::string eval() override;

//    std::vector<ASTNode *> statements;
};

// ------------------------------------------------------------------------

class OutputAST : public ASTNode {

public:
    OutputAST(ASTNode *E)
        : ASTNode()
    {
        ASTNode::children.push_back(E);
    }

    virtual void Accept( Genetics::MutationVisitor *visitor) ;

    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

    ASTNode * getExpression()   { return children[0];}

};

// ------------------------------------------------------------------------

class MoveAST : public ASTNode {

public:
    MoveAST(ASTNode *E)
        : ASTNode()
    {
        ASTNode::children.push_back(E);
    }

    virtual void Accept( Genetics::MutationVisitor *visitor) ;

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

    virtual void Accept( Genetics::MutationVisitor *visitor) override;

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
        compatibility = CompatibilityType::blockStart;
        children.push_back(E);
        children.push_back(B);
    }

    virtual void Accept( Genetics::MutationVisitor *visitor) override;

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
        compatibility = CompatibilityType::blockStart;
        children.push_back(E);
        children.push_back(B);
    }

    virtual void Accept( Genetics::MutationVisitor *visitor) override;

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

    virtual void Accept( Genetics::MutationVisitor *visitor) override;
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
        compatibility = CompatibilityType::var;
        setNumber(V);
    }

    virtual void Accept( Genetics::MutationVisitor *visitor) ;


    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();

};

// ------------------------------------------------------------------------

// OperandAST - operators involved in expressions like "A * B or A + C etc"

class BinOperandAST : public ASTNode {

public:
    BinOperandAST(Token O, ASTNode *L, ASTNode *R) : ASTNode(), op(O), lhs(L), rhs(R) {}

    virtual void Accept( Genetics::MutationVisitor *visitor) override ;

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
    YieldAST() : ASTNode() { }

    virtual void Accept( Genetics::MutationVisitor *visitor) override;

    virtual std::string print();
    virtual std::string diag(unsigned int parentID);
    virtual std::string eval();
};

// ------------------------------------------------------------------------

