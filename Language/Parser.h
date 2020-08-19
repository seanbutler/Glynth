//
// Created by sean on 17/06/2020.
//

//#ifndef GLYNTH_PARSER_H
//#define GLYNTH_PARSER_H

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

#include "Tokens.h"
#include "AST.h"

class ASTNode;

class Parser {

public:
    Parser() = default;
    Parser(Parser& rhs);
    virtual ~Parser();
    void DeleteNodeAndChildren(ASTNode* node);

//    void SetTokens(const std::vector<std::pair<Token, std::string>> &T) {
//        tokens = T;
//    }

    void SetTokensWithLines(const std::vector<std::tuple<Token, std::string, int>> &T) {
        tokensWithLines = T;
    }

//    std::pair<Token, std::string> &getNextToken()               { return currentToken = tokens[position++]; }
//    std::pair<Token, std::string> &lookAhead(int offset = 1)    { return tokens[position + offset]; }

    std::tuple<Token, std::string, int> &getNextToken() {
            return currentTokenWithLine = tokensWithLines[position++];
    }

    std::tuple<Token, std::string, int> &lookAhead(int offset = 1) {
        return tokensWithLines[position + offset];
    }

    unsigned int position = 0;
//    std::vector<std::pair<Token, std::string>> tokens;
//    std::pair<Token, std::string> currentToken;

    std::vector<std::tuple<Token, std::string, int>> tokensWithLines;
    std::tuple<Token, std::string, int> currentTokenWithLine;

// TODO MOVE THIS OUTSIDE THE PARSER

// bool SaveAST(std::string filename);
// bool LoadAST(std::string filename);

    bool parse();

    ASTNode* ParseStatement();
    ASTNode* ParseVariableDeclaration();
    ASTNode* ParseBlock();
    ASTNode* ParseWhileStatement();
    ASTNode* ParseIfStatement();
    ASTNode* ParseNumber();
    ASTNode* ParseIdentifier();
    ASTNode* ParseExpression();
    ASTNode* ParseParenExpression();
    ASTNode* ParseAssignmentStatement();
    ASTNode* ParseOutput();
    ASTNode* ParseMove();
    ASTNode* ParseTurn();
    ASTNode* ParseRandFunc();

    void CopyNodeAndChildren(ASTNode*& original, ASTNode*& copy);
    ASTNode ** GetRandomASTNode(CompatibilityType typeFilter);
    int CompatibleASTCount(CompatibilityType typeFilter);

    bool OutputTreeDiagram(std::string filename);
    bool OutputASTJSON(std::string filename);
    bool OutputAsm(std::string filename);
    std::string GetAsm();

    std::vector<ASTNode *> abstractSyntaxTree;


private:
    void ReportIssue(const std::string & typeStr,
                     const std::string & problemStr,
                     const std::string & contextStr = "",
                     const std::string & expectedStr = "");

    void ReportError(const std::string & problemStr,
                     const std::string & contextStr = "",
                     const std::string & expectedStr = "" );

    void ReportWarning(const std::string & problemStr,
                       const std::string & contextStr = "",
                       const std::string & expectedStr = "");

    ASTNode** GetASTNode(int index, CompatibilityType typeFilter);
    ASTNode** FindNodeInTree(int& currentIndex,ASTNode*& node, int targetIndex, CompatibilityType typeFilter);
    void CountNodes(int& nodeTotal, ASTNode* node, CompatibilityType typeFilter);

};

//#endif //GLYNTH_PARSER_H

