//
// Created by sean on 17/06/2020.
//

#ifndef GLYNTH_AST_H
#define GLYNTH_AST_H

#include <string>
#include <vector>

// ------------------------------------------------------------------------

static unsigned int uid = 1;

class ASTNode {
public:
    ASTNode()           {id=uid++;}
    virtual ~ASTNode()  {}

    virtual void print() =0;
    virtual void diag(unsigned int parentID) =0;
    virtual std::string eval() =0;
    unsigned int id;
};

// ------------------------------------------------------------------------

class VariableDeclarationAST : public ASTNode {

public:
    VariableDeclarationAST(ASTNode* I) : identifier(I) {}

    virtual void print();
    virtual void diag(unsigned int parentID);
    virtual std::string eval();

private:
    ASTNode *identifier;
};

// ------------------------------------------------------------------------

// IdentifierAST - statements like "var a"
class IdentifierAST : public ASTNode {

public:
    IdentifierAST(const std::string &N) : name(N) {}
    std::string &getName() {
        return name;
    }
    virtual void print();
    virtual void diag(unsigned int parentID);
    virtual std::string eval();

private:
    std::string name;
};

// ------------------------------------------------------------------------

// BlockAST - for lists of statements between BEGIN and END tokens

class BlockAST : public ASTNode {

public:
    std::vector<ASTNode*> statements;

    BlockAST()  {};
    virtual void print();
    virtual void diag(unsigned int parentID);
    virtual std::string eval();

private:
};

// ------------------------------------------------------------------------

// FunctionDeclarationAST - statements like "func id()"

class FunctionDeclarationAST : public ASTNode {

public:
    IdentifierAST *identifier;
    BlockAST *block;

    FunctionDeclarationAST(const std::string &N) : name(N) {}
    std::string &getName() {
        return name;
    }
    virtual void print();
    virtual void diag(unsigned int parentID);
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
    std::string &getName() {
        return name;
    }
    virtual void print();
    virtual void diag(unsigned int parentID);
    virtual std::string eval();

private:
    std::string name;
};

// ------------------------------------------------------------------------
// AssignmentStatementAST - statements like "while(expression){statements}"

class AssignmentStatementAST : public ASTNode {

public:
    ASTNode *identifier;
    ASTNode *expression;

    AssignmentStatementAST(ASTNode *I, ASTNode *E) : identifier(I), expression(E) {}
    std::string &getName() {
        return name;
    }
    virtual void print();
    virtual void diag(unsigned int parentID);
    virtual std::string eval();

private:
    std::string name;
};

// ------------------------------------------------------------------------
// AssignmentStatementAST - statements like "while(expression){statements}"

class NumberAST : public ASTNode {

public:
    int val;

    NumberAST(int V) : val(V){}
    std::string &getName() {
        return name;
    }
    virtual void print();
    virtual void diag(unsigned int parentID);
    virtual std::string eval();

private:
    std::string name;
};

// ------------------------------------------------------------------------

class BinOpAST : public ASTNode {

public:
    ASTNode * lhs;
    ASTNode * op;
    ASTNode * rhs;

    BinOpAST(ASTNode* L, ASTNode* O, ASTNode* R) : lhs(L), op(O), rhs(R) { }
    std::string &getName() {
        return name;
    }
    virtual void print();
    virtual void diag(unsigned int parentID);
    virtual std::string eval();

private:
    std::string name;
};


#endif //GLYNTH_AST_H
