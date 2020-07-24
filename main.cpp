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
    tmpAgent1Ptr->SetAlienVar(0, 8 + (int)rand()%16);
    tmpAgent1Ptr->SetAlienVar(1, 8 + (int)rand()%16);

    Agent* tmpAgent2Ptr = new Agent("./Assets/agent2.lang", sf::Color(32, 255, 32));
    engine.entityScheduler.entities.push_back((Entity*)tmpAgent2Ptr);
    tmpAgent2Ptr->SetAlienVar(0, 8 + (int)rand()%16);
    tmpAgent2Ptr->SetAlienVar(1, 8 + (int)rand()%16);

    Agent* tmpAgent3Ptr = new Agent("./Assets/agent3.lang", sf::Color(0, 64, 255));
    engine.entityScheduler.entities.push_back((Entity*)tmpAgent3Ptr);
    tmpAgent3Ptr->SetAlienVar(0, 8 + (int)rand()%16);
    tmpAgent3Ptr->SetAlienVar(1, 8 + (int)rand()%16);

    engine.MainLoop();
    return 0;
}
