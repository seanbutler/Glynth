#include <iostream>

#include "./Engine/Engine.h"
#include "./Test/SeanTest.h"
#include "./Engine/Entity.h"

#include "./Simulation/Agent.h"
#include "./Simulation/MazeEnvironment.h"
#include "./Simulation/WallEnvironment.h"
#include "./Simulation/ForestEnvironment.h"

#include "./Genetics/Evolution.h"
#include "Test/TobyTest.h"

int main(int argc, char **argv) {
    std::cout << "GLYNTH - Game Language Program Synthesis" << std::endl;
    srand(time(nullptr));

//    TobyTest::Test1();
    SeanTest::Test1();
    return 0;
}

