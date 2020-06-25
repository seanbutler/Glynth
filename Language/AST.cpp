//
// Created by sean on 17/06/2020.
//

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

void FunctionDeclarationAST::print() {
    std::cout << "var: \"" << name << "\"" << std::endl;
}

void FunctionDeclarationAST::diag(unsigned int parentID) {
    std::cout << "node" << ASTNode::id << " [ label = \"func: " << name << "\"];" << std::endl;
    std::cout << "node" << parentID << " -> " << "node" << ASTNode::id << ";" << std::endl;

}

std::string FunctionDeclarationAST::eval() {
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

