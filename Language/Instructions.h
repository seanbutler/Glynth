//
// Created by sean on 10/07/2020.
//

#ifndef GLYNTH_INSTRUCTIONS_H
#define GLYNTH_INSTRUCTIONS_H

#include <string>
#include <array>

enum class INS : int {
    NOP = 0,
    HALT,
    PUSH,
    POP,

    SAVE,
    LOAD,


    ADD,
    SUB,
    MUL,
    DIV,


    EQU,
    NE,
    GT,
    GTE,
    LT,
    LTE,

    RAND,

    OUTPUT,
    INPUT,

    JMP,
    BNZ,
    YIELD

};

#endif //GLYNTH_INSTRUCTIONS_H
