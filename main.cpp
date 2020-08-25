#include <iostream>

#include "./Test/SeanTest.h"
#include "Test/TobyTest.h"    evolution.InitialiseRandomPopulation(500, 6, 4);

int main(int argc, char **argv) {
    std::cout << "GLYNTH - Game Language Program Synthesis" << std::endl;

    TobyTest::TestPopulation();
    //TobyTest::TestRandomAST();
    //SeanTest::Test1();
    return 0;
}

