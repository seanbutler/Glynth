//
// Created by sean on 16/06/2020.
//

#include "Lexer.h"

Token Lexer::ScanToken() {
    char currentChar = lexingStr[lexingPos++];

    //
    // skip whitespace
    //
    while (currentChar == ' ' || currentChar == '\t' || currentChar == '\n') {
        if (currentChar == '\n') {
            currentLine++;
        }
        currentChar = lexingStr[lexingPos++];
    }

    //
    // token, probably keyword maybe identifier
    //
    if (isalpha(currentChar)) {

        // starting a new token ... probably a keyword
        std::string tokenString;

        // get the next character
        tokenString += currentChar;
        currentChar = lexingStr[lexingPos++];

        // scan forward letters, numbers and underscores only
        while (isalnum(currentChar) || currentChar == '_') {
            tokenString += currentChar;
            currentChar = lexingStr[lexingPos++];
        }
        --lexingPos;
        if (tokenString == "if") {
            tokens.push_back(std::make_pair(Token::KEYWORD_IF, tokenString));
            return Token::KEYWORD_IF;
        } else if (tokenString == "while") {
            tokens.push_back(std::make_pair(Token::KEYWORD_WHILE, tokenString));
            return Token::KEYWORD_WHILE;
//        } else if (tokenString == "func") {
//            tokens.push_back(std::make_pair(Token::KEYWORD_FUNC, tokenString));
//            return Token::KEYWORD_FUNC;
        } else if (tokenString == "var") {
            tokens.push_back(std::make_pair(Token::KEYWORD_VAR, tokenString));
            return Token::KEYWORD_VAR;
//        } else if (tokenString == "return") {
//            tokens.push_back(std::make_pair(Token::KEYWORD_RETURN, tokenString));
//            return Token::KEYWORD_RETURN;
//        } else if (tokenString == "yield") {
//            tokens.push_back(std::make_pair(Token::KEYWORD_YIELD, tokenString));
//            return Token::KEYWORD_YIELD;
//        } else if (tokenString == "exit") {
//            tokens.push_back(std::make_pair(Token::KEYWORD_EXIT, tokenString));
//            return Token::KEYWORD_EXIT;
        }
        tokens.push_back(std::make_pair(Token::IDENTIFIER, tokenString));
        return Token::IDENTIFIER;
    }

    //
    // numbers
    //
    // def: start with [0-9.], follow by [0-9.]
    // number only has 'double' type
    if (isdigit(currentChar) || currentChar == '.') {
        std::string numberStr;
        numberStr += currentChar;
        currentChar = lexingStr[lexingPos++];
        while (isdigit(currentChar) || currentChar == '.') {
            numberStr += currentChar;
            currentChar = lexingStr[lexingPos++];
        }
        --lexingPos;
        tokens.push_back(std::make_pair(Token::NUMBER, numberStr));
        return Token::NUMBER;
    }

    //
    // other symbols...
    //
    switch (currentChar) {

        case '\0': {
            tokens.push_back(std::make_pair(Token::END_OF_FILE, "\0"));
            return Token::END_OF_FILE;
        }

        case '{': {
            tokens.push_back(std::make_pair(Token::SYM_LBRACES, "{"));
            return Token::SYM_LBRACES;
        }

        case '}': {
            tokens.push_back(std::make_pair(Token::SYM_RBRACES, "}"));
            return Token::SYM_RBRACES;
        }

        case '(': {
            tokens.push_back(std::make_pair(Token::SYM_LPAREN, "("));
            return Token::SYM_LPAREN;
        }

        case ')': {
            tokens.push_back(std::make_pair(Token::SYM_RPAREN, ")"));
            return Token::SYM_RPAREN;
        }

        case '[': {
            tokens.push_back(std::make_pair(Token::SYM_LBRACKET, "["));
            return Token::SYM_LBRACKET;
        }

        case ']': {
            tokens.push_back(std::make_pair(Token::SYM_RBRACKET, "]"));
            return Token::SYM_RBRACKET;
        }

        case '>': {
            tokens.push_back(std::make_pair(Token::OP_GT, ">"));
            return Token::OP_GT;
        }

        case '<': {
            tokens.push_back(std::make_pair(Token::OP_LT, "<"));
            return Token::OP_LT;
        }

        case '+': {
            tokens.push_back(std::make_pair(Token::OP_ADD, "+"));
            return Token::OP_ADD;
        }

        case '-': {
            tokens.push_back(std::make_pair(Token::OP_SUB, "-"));
            return Token::OP_SUB;
        }

        case '*': {
            tokens.push_back(std::make_pair(Token::OP_MUL, "*"));
            return Token::OP_MUL;
        }

        case '/': {
            tokens.push_back(std::make_pair(Token::OP_DIV, "/"));
            return Token::OP_DIV;
        }

        case '=': {
            char nextChar = lexingStr[lexingPos];

            if (nextChar == '=') {
                tokens.push_back(std::make_pair(Token::OP_EQ, "=="));
                ++lexingPos;
                return Token::OP_EQ;
            }
            tokens.push_back(std::make_pair(Token::SYM_ASSIGN, "="));
            return Token::SYM_ASSIGN;
        }

        case ';': {
            tokens.push_back(std::make_pair(Token::SYM_SEMICOLON, ";"));
            return Token::SYM_SEMICOLON;
        }

        case ':': {
            tokens.push_back(std::make_pair(Token::SYM_COLON, ":"));
            return Token::SYM_COLON;
        }


        default: {
            return Token::ERROR;
        }

    }
}