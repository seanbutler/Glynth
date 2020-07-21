//
// Created by sean on 28/06/2020.
//

#ifndef GLYNTH_ASSEMBLER_H
#define GLYNTH_ASSEMBLER_H

#include <vector>
#include <map>

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

        std::cout << "Dump Labels Map" << std::endl;
        DumpLabelsMap();

        std::cout << "Dump Data Map" << std::endl;
        DumpDataMap();
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
            instructionListFile << (int) I << "\n";
        }
    }

    void DumpLabelsMap() {
        for (auto E : labels) {
            std::cout << "L " << E.first << " " << E.second << "\n";
        }
    }

    void DumpDataMap() {
        for (auto E : data) {
            std::cout << "D " << E.first << " " << E.second << "\n";
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

    std::vector<std::string> identifiers;

    std::map<std::string, int> labels;
    std::map<std::string, int> data;
};

#endif //PLYNTH_ASSEMBLER_H
