//
// Created by sean on 17/06/2020.
//

#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "Parser.h"
#include "AST.h"

// ----------------------------------------------------------------------

bool Parser::parse(){
    getNextToken();
    ASTNode *newNode = nullptr;

    do
    {
        newNode = this->ParseStatement();
        abstractSyntaxTree.push_back(newNode);
        if ( newNode )
            getNextToken();

    } while ( newNode != nullptr );

    return true;
}

// ----------------------------------------------------------------------

ASTNode * Parser::ParseStatement(){

    std::cout << "\nParser::ParseStatement " << (int) currentToken.first << std::endl;

//    std::cout << "\nParser::ParseStatement " << (int) currentToken.first << "\t" << currentToken.second << std::endl;

    switch ( currentToken.first  ) {

        case Token::END_OF_FILE: {
            return nullptr;
        }

        case Token::SYM_RBRACES: {
            return nullptr;
        }

        case Token::KEYWORD_VAR: {
            return ParseVariableDeclaration();
        }

        case Token::KEYWORD_WHILE: {
            return ParseWhileStatement();
        }

        case Token::IDENTIFIER: {
            Token aheadTokenType = lookAhead(0).first;
            std::string aheadTokenString = lookAhead(0).second;
            if ( aheadTokenType == Token::OP_ASSIGN ) {
                 return ParseAssignmentStatement();
            }
        }

//        case Token::KEYWORD_FUNC: {
//            return nullptr;
//        }

//        case Token::KEYWORD_IF: {
//            return nullptr;
//        }



        default: {
            return nullptr;
//            return this->ParseExpression();
        }
    }
    return nullptr;
}

// ----------------------------------------------------------------------

ASTNode * Parser::ParseVariableDeclaration(){

    Token tokenType = currentToken.first;
    std::string tokenString = currentToken.second;

    Token aheadTokenType = lookAhead(0).first;
    std::string aheadTokenString = lookAhead(0).second;

    std::cout << "Parser::ParseVariableDeclaration tokenType = " << (int)tokenType << " " << tokenString
                << " (aheadTokenType = " << (int)aheadTokenType << " " << aheadTokenString << ") " << std::endl;

    getNextToken(); // eat the 'var'

    ASTNode *var = nullptr;
    ASTNode *ident = nullptr;

    switch(aheadTokenType) {
        case Token::IDENTIFIER: {
            ident = ParseIdentifier();
            break;
        }
        default: {
            std::cerr << "Unrecognised Token in Variable Declaration" << std::endl;
            return nullptr;
        }
    }

    var = new VariableDeclarationAST(ident);

    return var;
}

// ----------------------------------------------------------------------

//ASTNode * Parser::ParseFunctionDeclaration(){
//
//    Token aheadTokenType = lookAhead(0).first;
//    std::string aheadTokenString = lookAhead(0).second;
//
//    std::cout << "Parser::ParseFunctionDeclaration aheadTokenType = " << (int)aheadTokenType << " " << aheadTokenString<< std::endl;
//
//    getNextToken();S
//
//    ASTNode *var = nullptr;
//
//    switch(aheadTokenType) {
//        case Token::IDENTIFIER: {
//            var = ParseIdentifier();
//            break;
//        }
//        default: {
//            std::cerr << "Unrecognised Token in Function Declaration" << std::endl;
//            return nullptr;
//        }
//    }
//
//    return var;
//}

// ----------------------------------------------------------------------

ASTNode * Parser::ParseIdentifier(){
    std::cout << "Parser::ParseIdentifier currentToken = " << (int)currentToken.first << " '" << currentToken.second << "' " << std::endl;
    ASTNode* identifierNode = new IdentifierAST(currentToken.second);
    return identifierNode;
}

// ----------------------------------------------------------------------

ASTNode * Parser::ParseNumber(){
    ASTNode* numberNode;
    std::cout << "Parser::ParseNumber currentToken = " << (int)currentToken.first << " '" << currentToken.second << "' " << std::endl;
    return new NumberAST(atoi(currentToken.second.c_str()));
}

// ----------------------------------------------------------------------

ASTNode *Parser::ParseBlock() {
    ASTNode *newNode = nullptr;
    getNextToken();
    std::vector<ASTNode*> nodes;
    BlockAST *block = new BlockAST();

    Token aheadTokenType = lookAhead(0).first;
    std::string aheadTokenString = lookAhead(0).second;

    do {
        newNode = this->ParseStatement();
        if (newNode) {
            block->statements.push_back(newNode);
            getNextToken();
        }

//        aheadTokenType = lookAhead(0).first;

    } while (newNode);

    return block;
}

// ----------------------------------------------------------------------

ASTNode * Parser::ParseWhileStatement() {

    Token tokenType = currentToken.first;
    std::string tokenString = currentToken.second;

    Token aheadTokenType = lookAhead(0).first;
    std::string aheadTokenString = lookAhead(0).second;

    std::cout << "Parser::ParseWhileStatement tokenType = " << (int)tokenType << " " << tokenString
              << " (aheadTokenType = " << (int)aheadTokenType << " " << aheadTokenString << ") " << std::endl;

    getNextToken();

    if ( currentToken.first != Token::SYM_LPAREN) {
        std::cerr << "ERROR : Unrecognised Token Before While Statement Expression, Expected Left Parenthesis." << std::endl;
        return nullptr;
    }

    getNextToken();
    ASTNode *cond = this->ParseExpression();

    getNextToken();

    if ( currentToken.first != Token::SYM_RPAREN) {
        std::cerr << "ERROR : Unrecognised Token After While Statement Expression, Expected Right Parenthesis." << std::endl;
        return nullptr;
    }

    getNextToken();

    if ( currentToken.first != Token::SYM_LBRACES) {
        std::cerr << "ERROR : Unrecognised Token Before While Statement Block, Expected Left Braces '{'." << std::endl;
        return nullptr;
    }

    ASTNode *block = this->ParseBlock();

    WhileStatementAST *whileStatement = new WhileStatementAST(cond, block);
    return whileStatement;
}

// ----------------------------------------------------------------------

ASTNode *Parser::ParseExpression() {

    std::cout << "Parser::ParseExpression currentToken = " << (int)currentToken.first << " " << currentToken.second << std::endl;

    Token tokenType = currentToken.first;
    std::string tokenString = currentToken.second;

    switch (tokenType) {

        case Token::NUMBER: {
            return ParseNumber();
        }

        case Token::IDENTIFIER: {
            return ParseIdentifier();
        }

//        case Token::SYM_LPAREN: {
//            return ParseSubExpression();
//        }

//        case Token::SYM_RPAREN: {
//            std::cerr << "ERROR Problem with Expression, found a Right Parenthesis in wrong place." << std::endl;
//            return nullptr;
//        }

        case Token::KEYWORD_FUNC:
        case Token::KEYWORD_WHILE:
        case Token::KEYWORD_VAR:
        case Token::KEYWORD_IF:
        case Token::KEYWORD_RETURN:
        case Token::KEYWORD_YIELD: {
            std::cerr << "ERROR Problem with Expression, found a Keyword in the wrong place." << std::endl;
            return nullptr;
        }

        default: {
            std::cerr << "ERROR Problem with Expression, Unknown." << std::endl;
            return nullptr;
        }
    }

}

// ----------------------------------------------------------------------

ASTNode *Parser::ParseSubExpression() {

    std::cout << "Parser::ParseSubExpression currentToken = " << (int) currentToken.first << " "
              << currentToken.second << std::endl;

    getNextToken(); // eat the left parenthesis

    ASTNode *subExpression = ParseExpression();

    if (currentToken.first != Token::SYM_RPAREN) {
        std::cerr << "ERROR : Unrecognised Token After Expression. Expected \')\' Got \'" << currentToken.second << "\'." << std::endl;
    }

    getNextToken(); // eat the right parenthesis
    return subExpression;
}

// ----------------------------------------------------------------------

ASTNode *Parser::ParseAssignmentStatement() {

    std::cout << "Parser::ParseAssignmentStatement ID currentToken = " << (int)currentToken.first << " \'" << currentToken.second << "\'" << std::endl;

    // parse identifier
    ASTNode* identifierNode = ParseIdentifier();

    // parse assignment operator
    getNextToken();
    if ( currentToken.first != Token::OP_ASSIGN) {
        std::cerr << "ERROR : Unrecognised Token in Assignment Statement, Expected Assignment." << std::endl;
        return nullptr;
    }

    std::cout << "Parser::ParseAssignmentStatement OP currentToken = " << (int)currentToken.first << " \'" << currentToken.second << "\'" << std::endl;

    // parse expression
    getNextToken();
    ASTNode* expressionNode = ParseExpression();

    AssignmentStatementAST * assignmentStatementAST;
    assignmentStatementAST = new AssignmentStatementAST(identifierNode, expressionNode);
    return assignmentStatementAST;
}

// ----------------------------------------------------------------------

unsigned int ufid;

bool Parser::debug(std::string filename) {

    std::ofstream diagramFile;
    std::string diagramFilename = std::filesystem::path(filename);
    diagramFilename += std::string(".gv");
    diagramFile.open(diagramFilename);

//    diagramFile <<


//    time_t t = time(0);   // get time now
//    struct tm * now = localtime( & t );
//    char buffer [80];
//    strftime (buffer,80,"%Y-%m-%d-%H-%M-%S",now);
//    std::ofstream out((std::string)"parsertree_" + buffer + "_" + std::to_string(ufid) + ".gv");
//    ufid++;

    std::cout.rdbuf(diagramFile.rdbuf());
    std::cout << "digraph G {" << std::endl;
    for (auto  N : abstractSyntaxTree ) {
        N->diag(0);
    }
    std::cout << std::endl << "}" << std::endl;
    return true;
}

// ----------------------------------------------------------------------
