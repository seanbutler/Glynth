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

bool Parser::parse() {

    getNextToken();
    ASTNode *newNode = nullptr;

    do {
        newNode = this->ParseStatement();

        if (newNode != nullptr) {
            abstractSyntaxTree.push_back(newNode);
            getNextToken();
        }

    } while (newNode != nullptr);

    return true;
}

// ----------------------------------------------------------------------

ASTNode *Parser::ParseStatement() {

//    std::cout << "\nParser::ParseStatement "
//              << (int) currentToken.first << " "
//              << currentToken.second
//              << std::endl;

    switch (currentToken.first) {

        case Token::KEYWORD_YIELD: {
            ASTNode* node = new YieldAST();
            getNextToken();
            return node;
        }

//        case Token::KEYWORD_EXIT: {
//            return new ExitAST();
//        }


        case Token::KEYWORD_EXIT: {
//            return ParseOutput();
        }

        case Token::KEYWORD_OUTPUT: {
            return ParseOutput();
        }

        case Token::KEYWORD_VAR: {
            return ParseVariableDeclaration();
        }

        case Token::KEYWORD_WHILE: {
            return ParseWhileStatement();
        }

        case Token::KEYWORD_IF: {
            return ParseIfStatement();
        }

        case Token::IDENTIFIER: {
            Token aheadTokenType = lookAhead(0).first;
            if (aheadTokenType == Token::SYM_ASSIGN) {
                return ParseAssignmentStatement();
            } else {
                std::cerr << "WARNING : Parser::ParseStatement() - Bare Identifier Outside Expression or Assignment "
                          << (int) currentToken.first << " "
                          << currentToken.second
                          << std::endl;
                return nullptr;
            }
        }

        case Token::SYM_RBRACES: {
            std::cerr << "WARNING : Parser::ParseStatement() - Skipping Extra Braces "
                      << (int) currentToken.first << " "
                      << currentToken.second
                      << std::endl;
            return nullptr;
        }

//        case Token::SYM_SEMICOLON: {
//            std::cerr << "WARNING : Parser::ParseStatement() - Skipping Extra Semicolon "
//                      << (int) currentToken.first << " "
//                      << currentToken.second
//                      << std::endl;
//            return nullptr;
//        }

        case Token::END_OF_FILE: {
            std::cerr << "WARNING : Parser::ParseStatement() - EOF " << std::endl;
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

ASTNode *Parser::ParseVariableDeclaration() {

    getNextToken();

    Token tokenType = currentToken.first;
    std::string tokenString = currentToken.second;

//    std::cout << "Parser::ParseVariableDeclaration "
//              << (int) tokenType << " "
//              << tokenString << std::endl;

    IdentifierAST *ident = nullptr;
    ASTNode *var = nullptr;

    if (currentToken.first == Token::IDENTIFIER) {
        ident = ParseIdentifier();
        var = new VariableDeclarationAST(ident);
    } else {
        std::cerr << "ERROR : Parser::ParseVariableDeclaration() - Unrecognised Token in Variable Declaration Found "
                  << currentToken.second << " Expected Token::IDENTIFIER" << std::endl;
    }

    getNextToken();

    if (currentToken.first != Token::SYM_SEMICOLON) {
        std::cerr << "ERROR Parser::ParseVariableDeclaration() - Unrecognised Token in Variable Declaration Found "
                  << currentToken.second << " Expected ;" << std::endl;
    }

    return var;
}

// ----------------------------------------------------------------------

ASTNode *Parser::ParseBlock() {

    getNextToken();

    ASTNode *newNode = nullptr;
    std::vector<ASTNode *> nodes;
    BlockAST *block = new BlockAST();

    do {
        newNode = this->ParseStatement();
        if (newNode != nullptr) {
            block->statements.push_back(newNode);
            getNextToken();
        }
    } while (newNode != nullptr);
    return block;
}


// ----------------------------------------------------------------------

ASTNode *Parser::ParseOutput() {

    Token tokenType = currentToken.first;
    std::string tokenString = currentToken.second;

//    std::cout << "Parser::ParseOutput tokenType = " << (int) tokenType
//              << " " << tokenString << std::endl;

    getNextToken();

    if (currentToken.first != Token::SYM_ASSIGN) {
        std::cerr << "ERROR Parser::ParseOutput() - Unrecognised Token Before Statement Expression, Expected Left Parenthesis."
                  << std::endl;
        return nullptr;
    }

    getNextToken();

    ASTNode *expr = this->ParseExpression();

//    getNextToken();

    OutputAST *outputStatement = new OutputAST(expr);

    return outputStatement;
}

// ----------------------------------------------------------------------

ASTNode *Parser::ParseIfStatement() {

    Token tokenType = currentToken.first;
    std::string tokenString = currentToken.second;

//    std::cout << "Parser::ParseIfStatement tokenType = " << (int) tokenType
//              << " " << tokenString << std::endl;

    getNextToken();

    if (currentToken.first != Token::SYM_LPAREN) {
        std::cerr << "ERROR Parser::ParseIfStatement() -  Unrecognised Token Before If Statement Expression, Expected Left Parenthesis."
                << std::endl;
        return nullptr;
    }

    getNextToken();

    ASTNode *cond = this->ParseExpression();

//    getNextToken();
//
//    if ( currentToken.first != Token::SYM_RPAREN) {
//        std::cerr << "ERROR Parser::ParseIfStatement() - Unrecognised Token After If Statement Expression " << (int)currentToken.first << currentToken.second << " Expected Right Parenthesis." << std::endl;
//        return nullptr;
//    }

    getNextToken();

    if (currentToken.first != Token::SYM_LBRACES) {
        std::cerr << "ERROR Parser::ParseIfStatement() - Unrecognised Token Before If Statement Block, Expected Left Braces '{'."
                << std::endl;
        return nullptr;
    }

    ASTNode *block = this->ParseBlock();

    IfStatementAST *ifStatement = new IfStatementAST(cond, block);

    if (currentToken.first != Token::SYM_RBRACES) {
        std::cerr << "ERROR Parser::ParseIfStatement() - Unrecognised Token After If Statement Block, Expected Left Braces '}'."
                << std::endl;
        return nullptr;
    }

    return ifStatement;
}

// ----------------------------------------------------------------------

ASTNode *Parser::ParseWhileStatement() {

    Token tokenType = currentToken.first;
    std::string tokenString = currentToken.second;

//    std::cout << "Parser::ParseWhileStatement tokenType = " << (int) tokenType
//              << " " << tokenString << std::endl;

    getNextToken();

    if (currentToken.first != Token::SYM_LPAREN) {
        std::cerr << "ERROR Parser::ParseWhileStatement() -  Unrecognised Token Before While Statement Expression, Expected Left Parenthesis."
                << std::endl;
        return nullptr;
    }

    getNextToken();

    ASTNode *cond = this->ParseExpression();

//    getNextToken();
//
//    if ( currentToken.first != Token::SYM_RPAREN) {
//        std::cerr << "ERROR Parser::ParseWhileStatement() - Unrecognised Token After While Statement Expression, Expected Right Parenthesis." << std::endl;
//        return nullptr;
//    }

    getNextToken();

    if (currentToken.first != Token::SYM_LBRACES) {
        std::cerr << "ERROR Parser::ParseWhileStatement() - Unrecognised Token Before While Statement Block \'"
                  << currentToken.second << "\'Expected Left Braces '}'." << std::endl;
        return nullptr;
    }

    ASTNode *block = this->ParseBlock();

    WhileStatementAST *whileStatement = new WhileStatementAST(cond, block);

    if (currentToken.first != Token::SYM_RBRACES) {
        std::cerr << "ERROR Parser::ParseWhileStatement() - Unrecognised Token After While Statement Block \'"
                  << currentToken.second << "\'Expected Right Braces '}'." << std::endl;
        return nullptr;
    }

    return whileStatement;
}

// ----------------------------------------------------------------------

ASTNode *Parser::ParseExpression() {

//    std::cout << "Parser::ParseExpression() currentToken = " << (int) currentToken.first << " " << currentToken.second
//              << std::endl;

    std::stack<ASTNode *> valueStack;
    std::stack<Token> opStack;

    ASTNode *expr = nullptr;

    bool done = false;
    while (!done) {

        switch (currentToken.first) {

            case Token::NUMBER: {
                valueStack.push(ParseNumber());
                getNextToken();
                break;
            }

            case Token::IDENTIFIER: {
                valueStack.push(ParseIdentifier());
                getNextToken();
                break;
            }

//            case Token::SYM_LPAREN: {
//                valueStack.push(ParseParenExpression());
//                getNextToken();
//                break;
//            }

            case Token::OP_GT:
            case Token::OP_GTE:
            case Token::OP_LT:
            case Token::OP_LTE:
            case Token::OP_EQ:
            case Token::OP_NE:
            case Token::OP_ADD:
            case Token::OP_SUB:
            case Token::OP_MUL:
            case Token::OP_DIV: {
//                std::cout << "Parser::ParseExpression() op = " << (int) currentToken.first << " " << currentToken.second
//                          << std::endl;
                if (!opStack.empty()) {
                    // get the last operator
                    Token op = opStack.top();
                    opStack.pop();

                    // get the last two values
                    ASTNode* right = valueStack.top();
                    valueStack.pop();

                    ASTNode *left = valueStack.top();
                    valueStack.pop();

                    // construct a binary op ast node
                    // TODO construct operator Node here...
                    ASTNode *binOpNode = new BinOperandAST(op, left, right);
                    valueStack.push(binOpNode);
                }

                opStack.push(currentToken.first);
                getNextToken();
                break;
            }

            case Token::SYM_RPAREN:
            case Token::SYM_SEMICOLON: {
                // TODO endof the whole expression so unwind the stack and return?

                while (!opStack.empty()) {
                    // get the last operator
                    Token op = opStack.top();
                    opStack.pop();

                    // get the last two values
                    ASTNode *right = valueStack.top();
                    valueStack.pop();

                    ASTNode *left = valueStack.top();
                    valueStack.pop();

                    // construct a binary op ast node
                    // TODO construct operator Node here...
                    ASTNode *binOpNode = new BinOperandAST(op, left, right);
                    valueStack.push(binOpNode);
                }

                if (!valueStack.empty()) {
                    return valueStack.top();
                } else {
                    std::cout << "empty expression!" << std::endl;
                    return nullptr;
                }
                break;
            }

            default: {
                // anything else means an error of some kind, perhaps?
                std::cerr << "ERROR : Unrecognised Token in Expression got ("
                          << (int) currentToken.first << ") \'"
                          << currentToken.second << "\' expected identifier, operand or number." << std::endl;
                return nullptr;
            }
        }
    }

    return expr;
}

// ----------------------------------------------------------------------

ASTNode *Parser::ParseParenExpression() {

    getNextToken();  // eat '('

//    std::cout << "Parser::ParseParenExpression currentToken = " << (int) currentToken.first << " "
//              << currentToken.second << std::endl;

    ASTNode *expr = nullptr;
    expr = ParseExpression();

    if (currentToken.first != Token::SYM_RPAREN) {
        std::cerr << "ERROR : Parser::ParseParenExpression - Unrecognised Token after Expression got "
                  << (int) currentToken.first << ") "
                  << currentToken.second << " expected \')\'." << std::endl;
    }

    getNextToken();  // eat ')'
    return expr;
}

// ----------------------------------------------------------------------

ASTNode *Parser::ParseAssignmentStatement() {

//    std::cout << "Parser::ParseAssignmentStatement ID currentToken = "
//              << (int) currentToken.first << " "
//              << currentToken.second << std::endl;

    // parse identifier
    ASTNode *identifierNode = ParseIdentifier();

    getNextToken();

    // parse assignment operator
    if (currentToken.first != Token::SYM_ASSIGN) {
        std::cerr
                << "ERROR Parser::ParseAssignmentStatement Unrecognised Token in Assignment Statement, Expected Assignment."
                << std::endl;
        return nullptr;
    }

//    std::cout << "Parser::ParseAssignmentStatement currentToken = " << (int) currentToken.first << " \'"
//              << currentToken.second << "\'" << std::endl;

    getNextToken();

    // parse expression
    ASTNode *expressionNode = ParseExpression();

    AssignmentStatementAST *assignmentStatementAST;
    assignmentStatementAST = new AssignmentStatementAST(identifierNode, expressionNode);
    return assignmentStatementAST;
}


// ----------------------------------------------------------------------

IdentifierAST *Parser::ParseIdentifier() {
//    std::cout << "Parser::ParseIdentifier currentToken = " << (int) currentToken.first << " '" << currentToken.second
//              << "' " << std::endl;
    IdentifierAST *identifierNode = new IdentifierAST(currentToken.second);
    return identifierNode;
}

ASTNode *Parser::ParseNumber() {
//    std::cout << "Parser::ParseNumber currentToken = " << (int) currentToken.first << " '" << currentToken.second
//              << "' " << std::endl;
    ASTNode *numberNode = new NumberAST(atoi(currentToken.second.c_str()));
    return numberNode;
}


// ----------------------------------------------------------------------

unsigned int ufid;

bool Parser::OutputTreeDiagram(std::string filename) {

    std::ofstream diagramFile;
    std::string diagramFilename = std::filesystem::path(filename);
    diagramFilename += std::string(".gv");
    diagramFile.open(diagramFilename);

    diagramFile << "digraph G {" << std::endl;
    for (auto N : abstractSyntaxTree) {
        if (N) {
            diagramFile << N->diag(0);
        }
    }
    diagramFile << std::endl << "}" << std::endl;
    diagramFile.close();
    return true;
}

// ----------------------------------------------------------------------

bool Parser::OutputAsm(std::string filename) {

    std::ofstream outFile;
    std::string outFilename = std::filesystem::path(filename);
    outFilename += std::string(".asm");
    outFile.open(outFilename);

    outFile << GetAsm();
    outFile.close();

    return true;
}


std::string Parser::GetAsm() {

    std::string assemblyCode;

    for (auto N : abstractSyntaxTree) {
        if (N) {
            assemblyCode += N->eval();
        }
    }

    return  assemblyCode;
}


// ----------------------------------------------------------------------