//
// Created by sean on 28/06/2020.
//

#ifndef GLYNTH_ASSEMBLER_H
#define GLYNTH_ASSEMBLER_H

#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>

#include "Instructions.h"

class Assembler {

public:
    Assembler(std::string AS) : assemblyStr(AS) {}
    virtual ~Assembler() {}

    INS ScanInstruction();

    void Scan() {
        INS result;
        do {
            result = ScanInstruction();
        } while (result != INS::END_OF_FILE && result != INS::ERROR);
    }

    std::vector<int> GetInstructions() {
        return this->instructions;
    }

    void OutputInstructionList(std::string F) {
        std::ofstream instructionListFile;
        std::string filename = std::filesystem::path(F);
        filename += std::string(".instr");
        instructionListFile.open(filename);

        for (auto I : instructions) {
            instructionListFile << (int) I << std::endl;
        }
    }

    void GenerateTestBinaryInstructions() {

        int A = 1;
        int B = 2;

        instructions.push_back((int) INS::PUSH);
        instructions.push_back(A);

        instructions.push_back((int) INS::SAVE);
        instructions.push_back(1);

        instructions.push_back((int) INS::PUSH);
        instructions.push_back(B);

        instructions.push_back((int) INS::SAVE);
        instructions.push_back(2);

        instructions.push_back((int) INS::LOAD);
        instructions.push_back(1);

        instructions.push_back((int) INS::LOAD);
        instructions.push_back(2);

        instructions.push_back((int) INS::ADD);

        instructions.push_back((int) INS::SAVE);
        instructions.push_back(2);

        instructions.push_back((int) INS::LOAD);
        instructions.push_back(2);

        instructions.push_back((int) INS::OUTPUT);

        instructions.push_back((int) INS::JMP);
        instructions.push_back((int) 8);

        instructions.push_back((int) INS::HALT);

    }

    std::string assemblyStr;
    int assemblyPos = 0;
    unsigned int currentLine = 0;
    std::vector<int> instructions;

};

#endif //PLYNTH_ASSEMBLER_H
