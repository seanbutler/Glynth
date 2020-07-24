//
// Created by sean on 27/06/2020.
//

#ifndef GLYNTH_VM_H
#define GLYNTH_VM_H

#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <map>

#include "Instructions.h"

class VM {

public:
    VM(std::vector<int> I, std::array<int, 32> & alienVars)
    : running(true)
    , instructions(I)
    , alien(alienVars)
    {
        for (int n = 0; n < 16; n++) {
            data.push_back(0);
        }
        programCounter = 0;
    }

    ~VM() {
    }

    unsigned int running;
    bool done;

private:

    std::vector<int> instructions;
    std::vector<int> data;
    std::stack<int> stack;

    std::array<int, 32> & alien;

    int programCounter = 0;

    void incrProgramCounter()       { programCounter++; }
    int getCurrentInstruction()     { return instructions[programCounter]; }

public:
    void DumpInstructions() {
        for (auto V : this->instructions) {
            std::cout << V << std::endl;
        }
    }

    void DumpData() {
        if (this->data.size() != 0) {
            for (auto V : this->data) {
                std::cout << V << std::endl;
            }
        }
    }

    void Execute(unsigned int slice);
};


#endif //PLYNTH_VM_H
