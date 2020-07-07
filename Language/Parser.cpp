//
// Created by sean on 17/06/2020.
//

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <stack>

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
        if ( newNode ) {
            getNextToken();
        }

    } while ( newNode != nullptr );

    return true;
}

// ----------------------------------------------------------------------

ASTNode * Parser::ParseStatement(){

    std::cout << "Parser::ParseStatement "
            << (int) currentToken.first << " "
            << currentToken.second
            << std::endl;

    switch ( currentToken.first  ) {

        case Token::KEYWORD_VAR: {
            return ParseVariableDeclaration();
        }

        case Token::KEYWORD_WHILE: {
            return ParseWhileStatement();
        }

        case Token::IDENTIFIER: {
            Token aheadTokenType = lookAhead(0).first;
            if ( aheadTokenType == Token::SYM_ASSIGN ) {
                 return ParseAssignmentStatement();
            }
        }

        case Token::SYM_SEMICOLON: {
            std::cerr << "WARNING : Parser::ParseStatement() - Skipping Extra Semicolon "
                      << (int) currentToken.first << " "
                      << currentToken.second
                      << std::endl;
            return nullptr;
        }

        case Token::END_OF_FILE: {
            return nullptr;
        }

        default: {
            std::cerr << "ERROR : Parser::ParseStatement() - Unrecognised Token "
                    << (int) currentToken.first << " "
                    << currentToken.second
                    << std::endl;
            return nullptr;
        }
    }
}

// ----------------------------------------------------------------------

ASTNode * Parser::ParseVariableDeclaration(){

    getNextToken();

    Token tokenType = currentToken.first;
    std::string tokenString = currentToken.second;

    std::cout << "Parser::ParseVariableDeclaration "
                << (int) tokenType << " "
                << tokenString << std::endl;

    ASTNode *ident = nullptr;
    ASTNode* var = nullptr;

    if ( currentToken.first == Token::IDENTIFIER)
    {
        ident = ParseIdentifier();
        var = new VariableDeclarationAST(ident);
    }
    else {
        std::cerr << "ERROR : Parser::ParseVariableDeclaration() - Unrecognised Token in Variable Declaration Found " << currentToken.second << " Expected Token::IDENTIFIER" << std::endl;
    }

    getNextToken();

    if (currentToken.first != Token::SYM_SEMICOLON)
    {
        std::cerr << "ERROR Parser::ParseVariableDeclaration() - Unrecognised Token in Variable Declaration Found " << currentToken.second << " Expected ;" << std::endl;
    }

    return var;

}

// ----------------------------------------------------------------------

ASTNode * Parser::ParseIdentifier(){
    std::cout << "Parser::ParseIdentifier currentToken = " << (int)currentToken.first << " '" << currentToken.second << "' " << std::endl;
    ASTNode* identifierNode = new IdentifierAST(currentToken.second);
    return identifierNode;
}

ASTNode * Parser::ParseNumber(){
    std::cout << "Parser::ParseNumber currentToken = " << (int)currentToken.first << " '" << currentToken.second << "' " << std::endl;
    ASTNode* numberNode =  new NumberAST(atoi(currentToken.second.c_str()));
    return numberNode;
}

// ----------------------------------------------------------------------

ASTNode *Parser::ParseBlock() {

    getNextToken();

    Token tokenType = currentToken.first;
    std::string tokenString = currentToken.second;

    ASTNode *newNode = nullptr;
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
        std::cerr << "ERROR Parser::ParseVariableDeclaration() -  Unrecognised Token Before While Statement Expression, Expected Left Parenthesis." << std::endl;
        return nullptr;
    }

    getNextToken();

    ASTNode *cond = this->ParseExpression();

    getNextToken();

    if ( currentToken.first != Token::SYM_RPAREN) {
        std::cerr << "ERROR Parser::ParseVariableDeclaration() - Unrecognised Token After While Statement Expression, Expected Right Parenthesis." << std::endl;
        return nullptr;
    }

    getNextToken();

    if ( currentToken.first != Token::SYM_LBRACES) {
        std::cerr << "ERROR Parser::ParseVariableDeclaration() - Unrecognised Token Before While Statement Block, Expected Left Braces '{'." << std::endl;
        return nullptr;
    }

    ASTNode *block = this->ParseBlock();

    WhileStatementAST *whileStatement = new WhileStatementAST(cond, block);
    return whileStatement;
}

// ----------------------------------------------------------------------

ASTNode *Parser::ParseExpression() {

    std::cout << "Parser::ParseExpression() currentToken = " << (int)currentToken.first << " " << currentToken.second << std::endl;

    ASTNode* expr = nullptr;

    bool done = false;
    while(!done) {

        switch (currentToken.first) {

            case Token::NUMBER: {
                expr = ParseNumber();
                getNextToken();
                if ( currentToken.first == Token::SYM_SEMICOLON) {
                    done = true;
                }
                break;
            }

            case Token::IDENTIFIER: {
                return ParseIdentifier();
            }

            case Token::SYM_LPAREN: {
                return ParseParenExpression();
            }

            case Token::SYM_SEMICOLON: {
                getNextToken();
                // TODO now transform the parsed things into a tree or something
                return nullptr;
            }

            default: {
                std::cerr <<"ERROR : Unrecognised Token in Expression Expected number, identifier or brackets."<< std::endl;
            }
        }
    }

    return expr;
}

// ----------------------------------------------------------------------

ASTNode *Parser::ParseParenExpression() {

    std::cout << "Parser::ParseParenExpression currentToken = " << (int)currentToken.first << " " << currentToken.second << std::endl;

    bool insideexpression = true;
    while(insideexpression) {

        switch (currentToken.first) {

            case Token::NUMBER: {
                return ParseNumber();
                break;
            }

            case Token::IDENTIFIER: {
                return ParseIdentifier();
                break;
            }

            case Token::SYM_LPAREN: {
                return ParseParenExpression();
                break;
            }



//            case Token::SYM_LPAREN: {
//                getNextToken();  // eat '('
//                ASTNode *expr = ParseExpression();
//
//                if (currentToken.first != Token::SYM_RPAREN ) {
//                    std::cerr <<"ERROR - expected \')\'"<< std::endl;
//                }
//                getNextToken();  // eat ')'
//                valueStack.push(expr);
//                break;
//            }

//            case Token::SYM_RPAREN: {
//                while(!opStack.empty()) {
//                    Token op = opStack.top();
//                    opStack.pop();
//                }
//                ASTNode *expr = ParseExpression();
//
//                if (currentToken.first != Token::SYM_RPAREN ) {
//                    std::cerr <<"ERROR - expected \')\'"<< std::endl;
//                }
//                getNextToken();  // eat ')'
//                valueStack.push(expr);
//                break;
//            }

            default: {
                getNextToken();
                break;

            }
        }
    }
}

// ----------------------------------------------------------------------

ASTNode * Parser::ParseAssignmentStatement() {

    std::cout << "Parser::ParseAssignmentStatement ID currentToken = "
            << (int)currentToken.first << " "
            << currentToken.second << std::endl;

    // parse identifier
    ASTNode* identifierNode = ParseIdentifier();

    getNextToken();

    // parse assignment operator
    if ( currentToken.first != Token::SYM_ASSIGN) {
        std::cerr << "ERROR Parser::ParseAssignmentStatement Unrecognised Token in Assignment Statement, Expected Assignment." << std::endl;
        return nullptr;
    }

    std::cout << "Parser::ParseAssignmentStatement OP currentToken = " << (int)currentToken.first << " \'" << currentToken.second << "\'" << std::endl;

    getNextToken();

    // parse expression
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

    std::cout.rdbuf(diagramFile.rdbuf());
    std::cout << "digraph G {" << std::endl;
    for (auto  N : abstractSyntaxTree ) {
        N->diag(0);
    }
    std::cout << std::endl << "}" << std::endl;
    return true;
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