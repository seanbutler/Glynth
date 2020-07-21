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
    YIELD,
    PUSH,
    POP,

    SAVE,
    LOAD,

    JMP,
    BRT,
    BRF,

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

    NUMBER,
    ADDRESS,
    LABEL,
    END_OF_FILE,
    ERROR
};

extern char* instructionNames[];

#endif //GLYNTH_INSTRUCTIONS_H
