//
// Created by sean on 23/07/2020.
//

#ifndef GLYNTH_ALIENVARS_H
#define GLYNTH_ALIENVARS_H

#include <array>

// ----------------------------------------------------------------------

class AlienVars{
public:
    void set(unsigned int var, int val) { values[var] = val;}
    int get(unsigned int var) { return values[var];}
    std::array<int, 32> values;
};

// ----------------------------------------------------------------------

#endif //GLYNTH_ALIENVARS_H
