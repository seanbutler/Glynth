//
// Created by sean on 17/06/2020.
//

#include "Tokens.h"
#include "AST.h"
#include "metainstructions.h"

#include <iostream>
#include <iomanip>

// ---------------------------------------------------------------------------

unsigned long guid = 0;

static std::string getUniqueIdentifier(){

    std::stringstream res;
    res << "LBL_" << std::setfill ('0') << std::setw (4);
    res << guid++;
    return  res.str();
}

// ---------------------------------------------------------------------------
//
//bool ASTFiler::SaveAST(std::string filename) {
//
//    std::ofstream treeFile;
//    std::string treeFileName = std::filesystem::path(filename);
//    treeFileName += std::string(".ast");
//    treeFile.open(treeFileName);
//
//    treeFile << "digraph G {" << std::endl;
//    for (auto N : abstractSyntaxTree) {
//        if (N) {
//            treeFile << N->diag(0);
//        }
//    }
//
//    treeFile.close();
//    return true;
//}
//
//bool ASTFiler::LoadAST(std::string filename) {
//}

// ---------------------------------------------------------------------------

std::string ASTNode::print() {
    std::string str = "";
//    str = "\n\"node\" : {\n";
//    str += "\"id\" : " + std::to_string(id) +",\n";
    return str;
}


// ---------------------------------------------------------------------------

std::string VariableDeclarationAST::print() {
    std::string str = "declaration: {";
    str += ASTNode::print();
    str += "\n\"type\" = \"defvar\"";

    str += this->identifier->print();
    return str;
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
    str += "\n";
    str += COMMENT + " DECLARE " + this->identifier->getName() + "\n";
    return str;
}

// ---------------------------------------------------------------------------

std::string IdentifierAST::print() {

    std::string str = "identifier: {";
    str += ASTNode::print();
    str += "\n\"value\" : \""+name+"\",";
    str += "}";
    return str;
}

std::string IdentifierAST::diag(unsigned int parentID) {
    std::string str = "";
    str += "node" + std::to_string(ASTNode::id) + " [ label = \"" + name + "\"];\n";
    str += "node" + std::to_string(parentID) + " -> node" + std::to_string(ASTNode::id) + ";\n";
    return str;
}

std::string IdentifierAST::eval() {
    std::string str = "";
    str += "\tLOAD " + VARIABLE + name + "\n";
    return str;
}


// ---------------------------------------------------------------------------

std::string AlienAST::print() {
    std::string str = "alienvar: {";
    str = ASTNode::print();
    str += "alienvar: \"" + name + "\"";
    str += "}\n";

    return str;
}

std::string AlienAST::diag(unsigned int parentID) {
    std::string str = "";
    str += "node" + std::to_string(ASTNode::id) + " [ label = \"" + name + "\"];\n";
    str += "node" + std::to_string(parentID) + " -> node" + std::to_string(ASTNode::id) + ";\n";
    return str;
}

std::string AlienAST::eval() {
    std::string str = "";
    str += "\tLOADALIEN " + VARIABLE + name + "\n";
    return str;
}

// ---------------------------------------------------------------------------

std::string BlockAST::print() {
    std::string str = "\"block\" : {\n";

    str = ASTNode::print();
    str += "label = \"block:\";";

    for (auto S : statements) {
        str += S->print();
    }
    str += "}\n";
    return str;
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
    std::string str = COMMENT + " BEGIN BLOCK\n";
    for (auto S  : statements) {
        str += S->eval();
    }
    str += "\n" + COMMENT +  " END BLOCK\n";
    return str;
}

// ---------------------------------------------------------------------------

std::string OutputAST::print() {
    std::string str;
    str = ASTNode::print();
    str +=  "output: \"" + name + "\"";
    str += this->expression->print();

    str += "}\n";
    return str;

}

std::string OutputAST::diag(unsigned int parentID) {
    std::string str;
    str += "node" + std::to_string(ASTNode::id) + " [ label = \"output:\"];\n";
    str += "node" + std::to_string(parentID) + " -> node" + std::to_string(ASTNode::id) + ";\n";

    str += this->expression->diag(ASTNode::id);
    return str;
}

std::string OutputAST::eval() {
    std::string str = "";

    str += "\n" + COMMENT + " OUTPUT EXPRESSION\n";
    str += this->expression->eval();

    str += "\tOUTPUT \n";
    return str;
}

// ---------------------------------------------------------------------------

std::string MoveAST::print() {
    std::string str;
    str = ASTNode::print();
    str +=  "move: \"" + name + "\"";
    str += this->expression->print();
    str += "}\n";

    return str;
}

std::string MoveAST::diag(unsigned int parentID) {
    std::string str;
    str += "node" + std::to_string(ASTNode::id) + " [ label = \"move:\"];\n";
    str += "node" + std::to_string(parentID) + " -> node" + std::to_string(ASTNode::id) + ";\n";

    str += this->expression->diag(ASTNode::id);
    return str;
}

std::string MoveAST::eval() {
    std::string str = "";

    str += "\n" + COMMENT + " MOVE FUNC (builtin)\n";
    str += this->expression->eval();

    str += "\tMOVE \n";
    return str;
}

// ---------------------------------------------------------------------------

std::string IfStatementAST::print() {
    std::string str;
    str = ASTNode::print();
    str +=  "if: \"" + name + "\"";
    str += this->expression->print();
    str += this->block->print();
    str += "}\n";
    return str;
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

    str += "\n" + COMMENT + " IF EXPRESSION ""\n";
    str += this->expression->eval();

    std::string label = getUniqueIdentifier();

    str += "\tBRF @" + label + "\n";
    str += "\n" + COMMENT + "IF BLOCK\n";
    str += this->block->eval();
    str += LOCATION + label + "\n";
    return str;
}

// ---------------------------------------------------------------------------

std::string WhileStatementAST::print() {
    std::string str;
    str = ASTNode::print();

    str +=  "while: \"" + name + "\"" ;

    str += this->expression->print();
    str += this->block->print();

    str += "}\n";

    return str;
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

    std::string label1 = getUniqueIdentifier();
    std::string label2 = getUniqueIdentifier();

    std::string str = "";
    str += "\n" + COMMENT + " WHILE \n";

    str += LOCATION + label1 + "\n";
    str += this->expression->eval();
    str += "\tBRF " + DESTINATION + label2 + "\n";
    str += "\n" + COMMENT + " WHILE BLOCK\n";
    str += this->block->eval();
    str += "\tJMP " + DESTINATION + label1 + "\n";
    str += LOCATION + label2 + "\n";

    return str;
}

// ---------------------------------------------------------------------------

std::string AssignmentStatementAST::print() {
    std::string str;
    str += "\"assign\" : {\n";
    str += ASTNode::print();

    str += this->identifier->print();
    str += this->expression->print();
    str += "\n}\n";
    return str;
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
    std::string str = "\n" + COMMENT + " Assignment Statement \n";
    str += this->expression->eval();
    // TODO - NASTY HACK HERE - we edit out the LOAD and insert a SAVE instead!!!
    str += "\tSAVE " + this->identifier->eval().substr(6);
    return str;
}

// ---------------------------------------------------------------------------

std::string NumberAST::print() {
    std::string str;
    str = ASTNode::print();
    str +=  "\"number\" : \"" + std::to_string(val) + "\"";
    str +=  "}\n";
    return str;
}

std::string NumberAST::diag(unsigned int parentID) {
    std::string str;
    str += "node" + std::to_string(ASTNode::id) + " [ label = \"" + std::to_string(val) + "\"];\n";
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

std::string BinOperandAST::print() {

    std::string str;

    str = ASTNode::print();
    str += "\type\" : \"expression\"";

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

    str +=  "opr: " + opStr ;

    str += lhs->print();
    str += rhs->print();

    return str;
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

    str += "node" + std::to_string(ASTNode::id) + " [ label = \"op: " + opStr + "\"];\n";
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

// ---------------------------------------------------------------------------

std::string YieldAST::print() {
    std::string str;
    str = ASTNode::print();

    str += "yield";
    return str;
}

std::string YieldAST::diag(unsigned int parentID) {
    std::string str;
    str += "node" + std::to_string(ASTNode::id) + " [ label = \"yield: \"];\n";
    str += "node" + std::to_string(parentID) + " -> node" + std::to_string(ASTNode::id) + ";\n";
    return str;
}

std::string YieldAST::eval() {
    std::string str = "\tYIELD\n";
    return str;
}

// ---------------------------------------------------------------------------
