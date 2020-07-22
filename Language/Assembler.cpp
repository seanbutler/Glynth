//
// Created by sean on 09/07/2020.
//

#include "metainstructions.h"


#include "Assembler.h"
#include <string>
#include <algorithm>
#include <iostream>



INS Assembler::ScanInstruction() {

    char currentChar = assemblyStr[assemblyPos++];

    START_OF_SCAN:

    //
    // skip whitespace
    //
    while (currentChar == ' ' || currentChar == '\t' || currentChar == '\n') {
        if (currentChar == '\n') {
            currentLine++;
        }
        currentChar = assemblyStr[assemblyPos++];
        goto START_OF_SCAN;
    }

    //
    // comments begin with a semicolon (;) skip them
    //
    if (currentChar == '#') {
        do {
            currentChar = assemblyStr[assemblyPos++];
        } while (currentChar != '\n');
        currentLine++;
        goto START_OF_SCAN;
    }

    //
    // assembly instructions
    //
    if (isalpha(currentChar)) {

        // starting a new token ...
        std::string tokenString;

        // get the next character
        tokenString += currentChar;
        currentChar = assemblyStr[assemblyPos++];

        // scan forward letters and underscore
        while (isalnum(currentChar) || currentChar == '_') {
            tokenString += currentChar;
            currentChar = assemblyStr[assemblyPos++];
        }
        --assemblyPos;

        std::cout << "asm got op/lab\t\t" << tokenString << std::endl;

        // TODO - turn this whole logic into a lookup or polymorphism

        if (tokenString.compare("NOP") == 0) {
            this->instructions.push_back((int) INS::NOP);
            return INS::NOP;
        }

        if (tokenString.compare("HALT") == 0) {
            this->instructions.push_back((int) INS::HALT);
            return INS::HALT;
        }

        if (tokenString.compare("YIELD") == 0) {
            this->instructions.push_back((int) INS::YIELD);
            return INS::YIELD;
        }

        if (tokenString.compare("SAVE") == 0) {
            this->instructions.push_back((int) INS::SAVE);
            return INS::SAVE;
        }

        if (tokenString.compare("LOAD") == 0) {
            this->instructions.push_back((int) INS::LOAD);
            return INS::LOAD;
        }

        if (tokenString.compare("PUSH") == 0) {
            this->instructions.push_back((int) INS::PUSH);
            return INS::PUSH;
        }

        if (tokenString.compare("POP") == 0) {
            this->instructions.push_back((int) INS::POP);
            return INS::POP;
        }

        if (tokenString.compare("ADD") == 0) {
            this->instructions.push_back((int) INS::ADD);
            return INS::ADD;
        }

        if (tokenString.compare("SUB") == 0) {
            this->instructions.push_back((int) INS::SUB);
            return INS::SUB;
        }

        if (tokenString.compare("MUL") == 0) {
            this->instructions.push_back((int) INS::MUL);
            return INS::MUL;
        }
        if (tokenString.compare("DIV") == 0) {
            this->instructions.push_back((int) INS::DIV);
            return INS::DIV;
        }

        if (tokenString.compare("EQU") == 0) {
            this->instructions.push_back((int) INS::EQU);
            return INS::EQU;
        }
        if (tokenString.compare("NE") == 0) {
            this->instructions.push_back((int) INS::NE);
            return INS::NE;
        }
        if (tokenString.compare("GT") == 0) {
            this->instructions.push_back((int) INS::GT);
            return INS::GT;
        }
        if (tokenString.compare("GTE") == 0) {
            this->instructions.push_back((int) INS::GTE);
            return INS::GTE;
        }
        if (tokenString.compare("LT") == 0) {
            this->instructions.push_back((int) INS::LT);
            return INS::LT;
        }
        if (tokenString.compare("LTE") == 0) {
            this->instructions.push_back((int) INS::LTE);
            return INS::LTE;
        }

        if (tokenString.compare("RAND") == 0) {
            this->instructions.push_back((int) INS::RAND);
            return INS::RAND;
        }
        if (tokenString.compare("OUTPUT") == 0) {
            this->instructions.push_back((int) INS::OUTPUT);
            return INS::OUTPUT;
        }
        if (tokenString.compare("INPUT") == 0) {
            this->instructions.push_back((int) INS::INPUT);
            return INS::INPUT;
        }

        if (tokenString.compare("JMP") == 0) {
            this->instructions.push_back((int) INS::JMP);
            return INS::JMP;
        }
        if (tokenString.compare("BRT") == 0) {
            this->instructions.push_back((int) INS::BRT);
            return INS::BRT;
        }
        if (tokenString.compare("BRF") == 0) {
            this->instructions.push_back((int) INS::BRF);
            return INS::BRF;
        }

//        if (tokenString.back() == ':') {
//            // declaration of a location in the instructions (a label)
//            labels.insert(std::make_pair(tokenString, this->instructions.size()));
//            return INS::LABEL;
//        }
//
//        if (tokenString[0] == '@') {
//            // reference to a location in the instructions (again a label)
//            this->instructions.push_back((int) INS::NOP);
//            labels.insert(std::make_pair(tokenString, this->instructions.size()));
//            return INS::LABEL;
//        }
//
//        // otherwise we are a data address label i.e. a variable
//        this->instructions.push_back((int) INS::NOP);
//        data.insert(std::make_pair(tokenString, data.size()));
//        return INS::ADDRESS;
    }

    //
    // numbers
    //
    // def: start with [0-9], follow by [0-9.]
    // number currently turns into a int in the VM
    if (isdigit(currentChar)) {

        std::string numberStr;
        numberStr += currentChar;
        currentChar = assemblyStr[assemblyPos++];
        while (isdigit(currentChar) || currentChar == '.') {
            numberStr += currentChar;
            currentChar = assemblyStr[assemblyPos++];
        }
        --assemblyPos;

        std::cout << "asm got number\t\t" << numberStr << "\n";

        this->instructions.push_back(std::stoi(numberStr));
        return INS::NUMBER;
    }

    //
    // :LABELS (they indicate jump destinations, no instructions emitted, instead add them to a map)
    //
    if (currentChar == ':') {

        // starting a new token ...
        std::string tokenString;

        // get the next character
        tokenString += currentChar;
        currentChar = assemblyStr[assemblyPos++];

        // scan forward letters and underscore
        while (isalnum(currentChar) || currentChar == '_') {
            tokenString += currentChar;
            currentChar = assemblyStr[assemblyPos++];
        }
        --assemblyPos;

        std::cout << "asm got op/lab\t\t" << tokenString << std::endl;

        labels.insert(std::make_pair(tokenString, this->instructions.size()));
        return INS::LABEL;
    }

    //
    // @LABELS addresses to be jumped to, emit a NOP (or NaN) for now and patch them up later
    //
    if (currentChar == '@') {

        // starting a new token ... probably an instruction address
        std::string tokenString;

        // get the next character
        tokenString += currentChar;
        currentChar = assemblyStr[assemblyPos++];

        // scan forward letters, numbers and underscores only
        while (isalnum(currentChar) || currentChar == '_') {
            tokenString += currentChar;
            currentChar = assemblyStr[assemblyPos++];
        }
        --assemblyPos;

        // add it to a map indexed on the string
        std::cout << "asm got @ label\t\t" << tokenString << "\n";

        // reference to a location in the instructions (again a label)
        this->instructions.push_back((int) INS::NOP);
        labels.insert(std::make_pair(tokenString, this->instructions.size()));
        return INS::LABEL;
    }



    //
    // other symbols...
    //
    if (currentChar == '\0') {
        instructions.push_back((int) INS::END_OF_FILE);
        return INS::END_OF_FILE;
    }
}