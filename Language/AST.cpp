//
// Created by sean on 17/06/2020.
//

#include "Tokens.h"
#include "AST.h"
#include <iostream>

// ---------------------------------------------------------------------------

void VariableDeclarationAST::print() {
    std::cout << "var: " << std::endl;
}

void VariableDeclarationAST::diag(unsigned int parentID) {
    std::cout << "node" << ASTNode::id << " [ label = \"defvar:\" ];" << std::endl;
    std::cout << "node" << parentID << " -> " << "node" << ASTNode::id << ";" << std::endl;
    this->identifier->diag(ASTNode::id);
}

std::string VariableDeclarationAST::eval() {
    std::string str;
    str = "VAR ";
    return str;
}

// ---------------------------------------------------------------------------

void IdentifierAST::print() {
    std::cout << "var: \"" << name << "\"" << std::endl;
}

void IdentifierAST::diag(unsigned int parentID) {
    std::cout << "node" << ASTNode::id << " [ label = \"" << name << "\"];" << std::endl;
    std::cout << "node" << parentID << " -> " << "node" << ASTNode::id << ";" << std::endl;
}

std::string IdentifierAST::eval() {
    std::string str;
    str = "VAR " + getName();
    return str;
}

// ---------------------------------------------------------------------------

void BlockAST::print() {
    std::cout << "node" << ASTNode::id << " [ label = \"block:\" ];" << std::endl;
    for (auto S : statements) {
        S->print();
    }
}

void BlockAST::diag(unsigned int parentID) {

    std::cout << "node" << ASTNode::id << " [ label = \"block:\" ];" << std::endl;
    std::cout << "node" << parentID << " -> " << "node" << ASTNode::id << ";" << std::endl;

    for (auto S : statements) {
        S->diag(ASTNode::id);
    }
}

std::string BlockAST::eval() {
    std::string str = "";
    for (auto S  : statements) {
        str += S->eval();
    }
    return str;
}

// ---------------------------------------------------------------------------



//void FunctionDeclarationAST::print() {
//    std::cout << "var: \"" << name << "\"" << std::endl;
//}


//void FunctionDeclarationAST::diag(unsigned int parentID) {
//    std::cout << "node" << ASTNode::id << " [ label = \"func: " << name << "\"];" << std::endl;
//    std::cout << "node" << parentID << " -> " << "node" << ASTNode::id << ";" << std::endl;
//
//}


//std::string FunctionDeclarationAST::eval() {
//    std::string str;
//    str = "VAR " + getName();
//    return str;
//}

// ---------------------------------------------------------------------------

void IfStatementAST::print() {
    std::cout << "if: \"" << name << "\"" << std::endl;

    this->expression->print();
    this->block->print();
}

void IfStatementAST::diag(unsigned int parentID) {
    std::cout << "node" << ASTNode::id << " [ label = \"if: " << name << "\"];" << std::endl;
    std::cout << "node" << parentID << " -> " << "node" << ASTNode::id << ";" << std::endl;

    this->expression->diag(ASTNode::id);
    this->block->diag(ASTNode::id);
}

std::string IfStatementAST::eval() {
    std::string str;
    str = "VAR " + getName();
    return str;
}


// ---------------------------------------------------------------------------

void WhileStatementAST::print() {
    std::cout << "while: \"" << name << "\"" << std::endl;

    this->expression->print();
    this->block->print();
}

void WhileStatementAST::diag(unsigned int parentID) {
    std::cout << "node" << ASTNode::id << " [ label = \"while: " << name << "\"];" << std::endl;
    std::cout << "node" << parentID << " -> " << "node" << ASTNode::id << ";" << std::endl;

    this->expression->diag(ASTNode::id);
    this->block->diag(ASTNode::id);
}

std::string WhileStatementAST::eval() {
    std::string str;
    str = "VAR " + getName();
    return str;
}

// ---------------------------------------------------------------------------

void AssignmentStatementAST::print() {
    std::cout << "assign: \"" << name << "\"" << std::endl;
}

void AssignmentStatementAST::diag(unsigned int parentID) {
    std::cout << "node" << ASTNode::id << " [ label = \"assign: " << name << "\"];" << std::endl;
    std::cout << "node" << parentID << " -> " << "node" << ASTNode::id << ";" << std::endl;

    this->identifier->diag(ASTNode::id);
    this->expression->diag(ASTNode::id);
}

std::string AssignmentStatementAST::eval() {
    std::string str;
    str = "VAR " + getName();
    return str;
}

// ---------------------------------------------------------------------------

void NumberAST::print() {
    std::cout << "number: \"" << val << "\"" << std::endl;
}

void NumberAST::diag(unsigned int parentID) {
    std::cout << "node" << ASTNode::id << " [ label = \"number: " << val << "\"];" << std::endl;
    std::cout << "node" << parentID << " -> " << "node" << ASTNode::id << ";" << std::endl;
}

std::string NumberAST::eval() {
    std::string str;
    str = "PUSH " + val;
    return str;
}

// ---------------------------------------------------------------------------

void BinOperandAST::print() {

    std::string opStr;

    switch (op) {
        case Token::OP_GT:
            opStr = ">";
            break;

        case Token::OP_GTE:
            opStr = ">=";
            break;

        case Token::OP_LT:
            opStr = "<";
            break;

        case Token::OP_LTE:
            opStr = "<=";
            break;

        case Token::OP_EQ:
            opStr = "==";
            break;

        case Token::OP_NE:
            opStr = "!=";
            break;

        case Token::OP_ADD:
            opStr = "+";
            break;

        case Token::OP_SUB:
            opStr = "-";
            break;

        case Token::OP_MUL:
            opStr = "*";
            break;

        case Token::OP_DIV:
            opStr = "/";
            break;
    }

    std::cout <<  "opr: " << opStr << std::endl;

    lhs->print();
    rhs->print();
}

void BinOperandAST::diag(unsigned int parentID) {
    lhs->diag(ASTNode::id);

    std::string opStr;

    switch (op) {
        case Token::OP_GT:
            opStr = ">";
            break;

        case Token::OP_GTE:
            opStr = ">=";
            break;

        case Token::OP_LT:
            opStr = "<";
            break;

        case Token::OP_LTE:
            opStr = "<=";
            break;

        case Token::OP_EQ:
            opStr = "==";
            break;

        case Token::OP_NE:
            opStr = "!=";
            break;

        case Token::OP_ADD:
            opStr = "+";
            break;

        case Token::OP_SUB:
            opStr = "-";
            break;

        case Token::OP_MUL:
            opStr = "*";
            break;

        case Token::OP_DIV:
            opStr = "/";
            break;
    }



    std::cout << "node" << ASTNode::id << " [ label = \"opr: " << opStr << "\"];" << std::endl;
    rhs->diag(ASTNode::id);
    std::cout << "node" << parentID << " -> " << "node" << ASTNode::id << ";" << std::endl;
}

std::string BinOperandAST::eval() {

    std::string str = "";
    switch (op) {
        case Token::OP_ADD: {
            str += lhs->eval() + rhs->eval() + "ADD";
            break;
        }
        case Token::OP_SUB: {
            str += lhs->eval() + rhs->eval() + "SUB";
            break;
        }
        case Token::OP_MUL: {
            str += lhs->eval() + rhs->eval() + "MUL";
            break;
        }
        case Token::OP_DIV: {
            str += lhs->eval() + rhs->eval() + "DIV";
            break;
        }
        case Token::OP_GT: {
            str += lhs->eval() + rhs->eval() + "GT";
            break;
        }
        case Token::OP_LT: {
            str += lhs->eval() + rhs->eval() + "LT";
            break;
        }
        case Token::OP_GTE: {
            str += lhs->eval() + rhs->eval() + "GTE";
            break;
        }
        case Token::OP_LTE: {
            str += lhs->eval() + rhs->eval() + "LTE";
            break;
        }
        case Token::OP_EQ: {
            str += lhs->eval() + rhs->eval() + "EQU";
            break;
        }
        case Token::OP_NE: {
            str += lhs->eval() + rhs->eval() + "NE";
            break;
        }
        default: {
            std::cout<<"Unknown BinaryExprAST opr: " << (int)op << std::endl;
            break;
        }
    }
    return str;
}
