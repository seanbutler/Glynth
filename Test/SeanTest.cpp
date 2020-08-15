//
// Created by sean on 14/08/2020.
//

#include "SeanTest.h"


#include "../Simulation/Agent.h"
#include "../Engine/Engine.h"
#include "../Genetics/Evolution.h"

void SeanTest::Test1() {

    Engine::Engine engine(32, 32);
    Genetics::Evolution evolution;

    srand(time(nullptr));

    Agent* tmpAgent1Ptr;
    tmpAgent1Ptr = new Agent(HurtfulAgentType());
    tmpAgent1Ptr->Compile("../Assets/agent1.c");
    tmpAgent1Ptr->Assemble();
    tmpAgent1Ptr->SetAlienVar(0, 8 );
    tmpAgent1Ptr->SetAlienVar(1, 8 );
    engine.entityScheduler.entities.push_back((Engine::Entity*)tmpAgent1Ptr);


    engine.MainLoop();
}