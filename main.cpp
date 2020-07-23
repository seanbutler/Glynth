#include <iostream>
#include <fstream>
#include<stdlib.h>
#include<time.h>

#include "./Language/Lexer.h"
#include "./Language/Parser.h"
#include "./Language/Assembler.h"
#include "./Language/VirtualMachine.h"

#include "./Engine/Engine.h"

#include "./Simulation/Agent.h"


int main(int argc, char **argv) {
    std::cout << "GLYNTH - Game Language Program Synthesis" << std::endl;

    Engine engine;

    srand(time(NULL));


    Agent* tmpAgent1Ptr = new Agent("./Assets/agent1.lang", sf::Color(255, 64, 0));
    engine.entityScheduler.entities.push_back((Entity*)tmpAgent1Ptr);
    tmpAgent1Ptr->SetAlienVar("x", (int)rand()%32);
    tmpAgent1Ptr->SetAlienVar("y", (int)rand()%32);

    Agent* tmpAgent2Ptr = new Agent("./Assets/agent2.lang", sf::Color(32, 255, 32));
    engine.entityScheduler.entities.push_back((Entity*)tmpAgent2Ptr);
    tmpAgent2Ptr->SetAlienVar("x", (int)rand()%32);
    tmpAgent2Ptr->SetAlienVar("y", (int)rand()%32);

    Agent* tmpAgent3Ptr = new Agent("./Assets/agent3.lang", sf::Color(0, 64, 255));
    engine.entityScheduler.entities.push_back((Entity*)tmpAgent3Ptr);
    tmpAgent3Ptr->SetAlienVar("x", (int)rand()%32);
    tmpAgent3Ptr->SetAlienVar("y", (int)rand()%32);

    engine.MainLoop();
    return 0;
}
