//
// Created by sean on 28/06/2020.
//

#ifndef GLYNTH_ASSEMBLER_H
#define GLYNTH_ASSEMBLER_H

#include <vector>
#include "Instructions.h"

class Assembler {

public:
    Assembler() {}
    virtual ~Assembler() {}

    std::vector<int> GetBinaryInstructions() {

        int A = 1;
        int B = 2;

        std::vector<int> instructions;

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

        return instructions;
    }

};

#endif //PLYNTH_ASSEMBLER_H
