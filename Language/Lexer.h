//
// Created by sean on 16/06/2020.
//

#ifndef GLYNTH_LEXER_H
#define GLYNTH_LEXER_H

#include "Tokens.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>

class Lexer {

public:

    Lexer(const std::string &str, int pos = 0) :
        lexingStr(str),
        lexingPos(pos) {
    }

    virtual ~Lexer() {
    }

    Token ScanToken();

    Token Scan() {
        Token result;
        do {
            result = ScanToken();
        } while (result != Token::END_OF_FILE && result != Token::ERROR);

        return result;
    }

    std::vector<std::pair<Token, std::string>> GetTokenList() {
        return tokens;
    }

    void OutputTokenList(std::string filename) {
        std::ofstream tokenListFile;
        std::string tokenListFilename = std::filesystem::path(filename);
        tokenListFilename += std::string(".tokens");
        tokenListFile.open(tokenListFilename);
        for (auto it = tokens.begin(); it != tokens.end(); ++it) {
            tokenListFile << (int) it->first << "\t" << it->second << std::endl;
        }
        tokenListFile.close();
    }

private:
    std::string lexingStr;
    int lexingPos = 0;
    unsigned int currentLine = 0;
    std::vector<std::pair<Token, std::string>> tokens;
};


#endif //GLYNTH_LEXER_H
