//
// Created by sean on 17/06/2020.
//

#ifndef GLYNTH_PARSER_H
#define GLYNTH_PARSER_H

#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

#include "Tokens.h"
#include "AST.h"

class Parser {

public:
//    Parser(const std::vector<std::pair<Token, std::string>> &T) : tokens(T) {}
    Parser() {

    }

    void SetTokens(const std::vector<std::pair<Token, std::string>> &T) {
        tokens = T;
    }


    std::pair<Token, std::string> &getNextToken()               { return currentToken = tokens[position++]; }
    std::pair<Token, std::string> &lookAhead(int offset = 1)    { return tokens[position + offset]; }

    unsigned int position = 0;
    std::vector<std::pair<Token, std::string>> tokens;
    std::pair<Token, std::string> currentToken;

// TODO MOVE THIS OUTSIDE THE PARSER

// bool SaveAST(std::string filename);
// bool LoadAST(std::string filename);

    bool parse();

    ASTNode *ParseStatement();
    ASTNode *ParseVariableDeclaration();
    ASTNode *ParseBlock();
    ASTNode *ParseWhileStatement();
    ASTNode *ParseIfStatement();
    ASTNode *ParseNumber();
    IdentifierAST *ParseIdentifier();
    ASTNode *ParseExpression();
    ASTNode *ParseParenExpression();
    ASTNode *ParseAssignmentStatement();
    ASTNode *ParseOutput();
    ASTNode *ParseMove();
    ASTNode *ParseTurn();
    ASTNode *ParseRandFunc();

    bool OutputTreeDiagram(std::string filename);
    bool OutputASTJSON(std::string filename);
    bool OutputAsm(std::string filename);
    std::string GetAsm();

private:
    std::vector<ASTNode *> abstractSyntaxTree;
};

#endif //GLYNTH_PARSER_H

