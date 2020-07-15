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
    Parser(const std::vector<std::pair<Token, std::string>> &T) : tokens(T) {}
    std::vector<std::pair<Token, std::string>> tokens;
    std::pair<Token, std::string> currentToken;
    unsigned int position = 0;
    std::pair<Token, std::string> &getNextToken()               { return currentToken = tokens[position++]; }
    std::pair<Token, std::string> &lookAhead(int offset = 1)    { return tokens[position + offset]; }

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

    bool OutputTreeDiagram(std::string filename);
    std::vector<ASTNode *> abstractSyntaxTree;

    bool OutputAsm(std::string filename);
    std::string GetAsm();


};

#endif //GLYNTH_PARSER_H

