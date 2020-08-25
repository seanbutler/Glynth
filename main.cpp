#include <iostream>

#include "./Test/SeanTest.h"
#include "Test/TobyTest.h"

int main(int argc, char **argv) {
    std::cout << "GLYNTH - Game Language Program Synthesis" << std::endl;

    //TobyTest::TestPopulation();
    TobyTest::TestRandomAST();
    //SeanTest::Test1();
    return 0;
}

