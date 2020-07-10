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

        int A = 11;
        int B = 13;
        int C = 17;
        int D = 19;

        std::vector<int> instructions;

        instructions.push_back((int) INS::PUSH);
        instructions.push_back(A);

        instructions.push_back((int) INS::PUSH);
        instructions.push_back(B);

        instructions.push_back((int) INS::ADD);

        instructions.push_back((int) INS::SAVE);
        instructions.push_back(1);

        instructions.push_back((int) INS::PUSH);
        instructions.push_back(C);

        instructions.push_back((int) INS::PUSH);
        instructions.push_back(D);

        instructions.push_back((int) INS::ADD);

        instructions.push_back((int) INS::SAVE);
        instructions.push_back(2);

        instructions.push_back((int) INS::LOAD);
        instructions.push_back(1);

        instructions.push_back((int) INS::LOAD);
        instructions.push_back(2);

        instructions.push_back((int) INS::MUL);
        instructions.push_back((int) INS::OUTPUT);

        instructions.push_back((int) INS::HALT);

        return instructions;
    }

};

#endif //PLYNTH_ASSEMBLER_H
