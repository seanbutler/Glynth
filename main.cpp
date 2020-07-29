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
#include "./Simulation/MazeEnvironment.h"
#include "./Simulation/WallEnvironment.h"

#include "./Simulation/ForestEnvironment.h"

int main(int argc, char **argv) {
    std::cout << "GLYNTH - Game Language Program Synthesis" << std::endl;

    Engine engine(32, 32);

    srand(time(NULL));

//    MazeEnvironment* environment = new MazeEnvironment(32, 32);
//    engine.entityScheduler.entities.push_back((Entity*)environment);

//    WallEnvironment* environment1 = new WallEnvironment('V', 32, 32);
//    engine.entityScheduler.entities.push_back((Entity*)environment1);

//    WallEnvironment* environment2 = new WallEnvironment('H', 32, 32);
//    engine.entityScheduler.entities.push_back((Entity*)environment2);

    ForestEnvironment* environment2 = new ForestEnvironment(32, 32);
    engine.entityScheduler.entities.push_back((Entity*)environment2);

//    Agent* goalAgentPtr = new Agent("./Assets/goal.c", GoalAgentType());
//    engine.entityScheduler.entities.push_back((Entity*)goalAgentPtr);
//    goalAgentPtr->SetAlienVar(0, 24 + (int)rand()%8);
//    goalAgentPtr->SetAlienVar(1, 24 + (int)rand()%8);
//
//    Agent* playerAgentPtr = new Agent("./Assets/player.c", PlayerAgentType());
//    engine.entityScheduler.entities.push_back((Entity*)playerAgentPtr);
//    playerAgentPtr->SetAlienVar(0, 2 + (int)rand()%4);
//    playerAgentPtr->SetAlienVar(1, 2 + (int)rand()%4);

    Agent* tmpAgent2Ptr = new Agent("./Assets/agent2.c", HurtfulAgentType());
    engine.entityScheduler.entities.push_back((Entity*)tmpAgent2Ptr);
    tmpAgent2Ptr->SetAlienVar(0, 8 + (int)rand()%16);
    tmpAgent2Ptr->SetAlienVar(1, 8 + (int)rand()%16);

    Agent* tmpAgent3Ptr = new Agent("./Assets/agent3.c", HealingAgentType());
    engine.entityScheduler.entities.push_back((Entity*)tmpAgent3Ptr);
    tmpAgent3Ptr->SetAlienVar(0, 8 + (int)rand()%16);
    tmpAgent3Ptr->SetAlienVar(1, 8 + (int)rand()%16);

    engine.MainLoop();
    return 0;
}
