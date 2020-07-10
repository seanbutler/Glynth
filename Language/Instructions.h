//
// Created by sean on 10/07/2020.
//

#ifndef GLYNTH_INSTRUCTIONS_H
#define GLYNTH_INSTRUCTIONS_H

#include <string>
#include <map>

enum INS : int {
    NOP = 0,
    HALT,
    PUSH,
    POP,

    ADD,    //(4)
    SUB,
    MUL,
    DIV,

    EQU,    //(8)
    NE,

    RAND,

    OUTPUT,
    INPUT,  //(12)
    SAVE,
    LOAD
};

class Instructions {

};


#endif //GLYNTH_INSTRUCTIONS_H
