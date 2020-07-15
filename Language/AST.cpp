//
// Created by sean on 17/06/2020.
//

#include "Tokens.h"
#include "AST.h"
#include <iostream>
#include <fstream>

// ---------------------------------------------------------------------------

void VariableDeclarationAST::print() {
    std::cout << "var: " << std::endl;
}

std::string VariableDeclarationAST::diag(unsigned int parentID) {

    std::string str = "";
    str += "node" + std::to_string(ASTNode::id) + " [ label = \"defvar:\" ];\n";
    str += "node" + std::to_string(parentID) + " -> node" + std::to_string(ASTNode::id) + ";\n";
    str += this->identifier->diag(ASTNode::id);
    return str;

}

std::string VariableDeclarationAST::eval() {
    std::string str = "";
    str += "\n; DECLARE " + this->identifier->getName() + "\n";
    str += "\tNOP\n";
    return str;
}

// ---------------------------------------------------------------------------

void IdentifierAST::print() {
    std::cout << "var: \"" << name << "\"" << std::endl;
}

std::string IdentifierAST::diag(unsigned int parentID) {
    std::string str = "";
    str += "node" + std::to_string(ASTNode::id) + " [ label = \"" + name + "\"];\n";
    str += "node" + std::to_string(parentID) + " -> node" + std::to_string(ASTNode::id) + ";\n";
    return str;
}

std::string IdentifierAST::eval() {
    std::string str = "";
    str += "\tLOAD " + name + "\n";
    return str;
}

// ---------------------------------------------------------------------------

void BlockAST::print() {
    std::cout << "node" << ASTNode::id << " [ label = \"block:\" ];" << std::endl;
    for (auto S : statements) {
        S->print();
    }
}

std::string BlockAST::diag(unsigned int parentID) {
    std::string str = "";
    str += "node" + std::to_string(ASTNode::id) + " [ label = \"block:\" ];\n";
    str += "node" + std::to_string(parentID) + " -> node" + std::to_string(ASTNode::id) + ";\n";
    for (auto S : statements) {
        str += S->diag(ASTNode::id);
    }

    return str;
}

std::string BlockAST::eval() {
    std::string str = "; BEGIN BLOCK\n";
    for (auto S  : statements) {
        str += S->eval();
    }
    str += "\n; END BLOCK\n";
    return str;
}

// ---------------------------------------------------------------------------

void IfStatementAST::print() {
    std::cout << "if: \"" << name << "\"" << std::endl;

    this->expression->print();
    this->block->print();
}

std::string IfStatementAST::diag(unsigned int parentID) {

    std::string str;
    str += "node" + std::to_string(ASTNode::id) + " [ label = \"if:\"];\n";
    str += "node" + std::to_string(parentID) + " -> node" + std::to_string(ASTNode::id) + ";\n";

    str += this->expression->diag(ASTNode::id);
    str += this->block->diag(ASTNode::id);
    return str;
}

std::string IfStatementAST::eval() {
    std::string str = "";

    str += "\n; IF EXPRESSION ""\n";
    str += this->expression->eval();

    std::string label = generateJumpLabel();

    str += "\tBRF " + label + "\n";
    str += "\n; IF BLOCK\n";
    str += this->block->eval();
    str += label + ":\n";

    return str;
}


// ---------------------------------------------------------------------------

void WhileStatementAST::print() {
    std::cout << "while: \"" << name << "\"" << std::endl;

    this->expression->print();
    this->block->print();
}

std::string WhileStatementAST::diag(unsigned int parentID) {
    std::string str;
    str += "node" + std::to_string(ASTNode::id) + " [ label = \"while:\"];\n";
    str += "node" + std::to_string(parentID) + " -> node" + std::to_string(ASTNode::id) + ";\n";

    str += this->expression->diag(ASTNode::id);
    str += this->block->diag(ASTNode::id);

    return str;
}

std::string WhileStatementAST::eval() {

    std::string label1 = generateJumpLabel();
    std::string label2 = generateJumpLabel();

    std::string str = "";
    str += "\n; WHILE \n";

    str += label1 + ":\n";
    str += this->expression->eval();
    str += "\tBRF " + label2 + "\n";
    str += "\n; WHILE BLOCK\n";
    str += this->block->eval();
    str += "\tJMP " + label1 + "\n";
    str += label2 + ":\n";
    return str;
}

// ---------------------------------------------------------------------------

void AssignmentStatementAST::print() {
    std::cout << "assign: \"" << name << "\"" << std::endl;
}

std::string AssignmentStatementAST::diag(unsigned int parentID) {
    std::string str;
    str += "node" + std::to_string(ASTNode::id) + " [ label = \"assign:\"];\n";
    str += "node" + std::to_string(parentID) + " -> node" + std::to_string(ASTNode::id) + ";\n";
    str += this->identifier->diag(ASTNode::id);
    str += this->expression->diag(ASTNode::id);
    return str;
}

std::string AssignmentStatementAST::eval() {
    std::string str = "\n; Assignment Statement \n";
    str += this->expression->eval();
    // TODO - NASTY HACK HERE - we edit out the LOAD and insert a SAVE instead!!!
    str += "\tSAVE " + this->identifier->eval().substr(6);
    return str;
}

// ---------------------------------------------------------------------------

void NumberAST::print() {
    std::cout << "number: \"" << val << "\"" << std::endl;
}

std::string NumberAST::diag(unsigned int parentID) {
    std::string str;
    str += "node" + std::to_string(ASTNode::id) + " [ label = \"number: " + std::to_string(val) + "\"];\n";
    str += "node" + std::to_string(parentID) + " -> node" + std::to_string(ASTNode::id) + ";\n";
    return str;
}

std::string NumberAST::eval() {
    std::string str = "";
    str += "\tPUSH " + std::to_string(val);
    str += "\n";
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

    std::cout << "opr: " << opStr << std::endl;

    lhs->print();
    rhs->print();
}

std::string BinOperandAST::diag(unsigned int parentID) {

    std::string str;
    str += lhs->diag(ASTNode::id);

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

    str += "node" + std::to_string(ASTNode::id) + " [ label = \"opr: " + opStr + "\"];\n";
    str += rhs->diag(ASTNode::id);
    str += "node" + std::to_string(parentID) + " -> node" + std::to_string(ASTNode::id) + ";\n";
    return str;
}

std::string BinOperandAST::eval() {

    std::string str = "";
    switch (op) {
        case Token::OP_ADD: {
            str += lhs->eval() + rhs->eval() + "\tADD";
            str += "\n";
            break;
        }
        case Token::OP_SUB: {
            str += lhs->eval() + rhs->eval() + "\tSUB";
            str += "\n";
            break;
        }
        case Token::OP_MUL: {
            str += lhs->eval() + rhs->eval() + "\tMUL";
            str += "\n";
            break;
        }
        case Token::OP_DIV: {
            str += lhs->eval() + rhs->eval() + "\tDIV";
            str += "\n";
            break;
        }
        case Token::OP_GT: {
            str += lhs->eval() + rhs->eval() + "\tGT";
            str += "\n";
            break;
        }
        case Token::OP_LT: {
            str += lhs->eval() + rhs->eval() + "\tLT";
            str += "\n";
            break;
        }
        case Token::OP_GTE: {
            str += lhs->eval() + rhs->eval() + "\tGTE";
            str += "\n";
            break;
        }
        case Token::OP_LTE: {
            str += lhs->eval() + rhs->eval() + "\tLTE";
            str += "\n";
            break;
        }
        case Token::OP_EQ: {
            str += lhs->eval() + rhs->eval();
            str += "\tEQU\n";
            break;
        }
        case Token::OP_NE: {
            str += lhs->eval() + rhs->eval() + "\tNE";
            str += "\n";
            break;
        }
        default: {
            std::cout << "Unknown BinaryExprAST opr: " << (int) op << std::endl;
            str += "; Unknown BinaryExprAST \n";
            break;
        }
    }
    return str;
}
