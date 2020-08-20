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
    for(int n=0;n<100;n++) {
        tmpAgent1Ptr = new HurtfulAgent();
        tmpAgent1Ptr->Compile("../Assets/agent1.c");
        tmpAgent1Ptr->Assemble();
        tmpAgent1Ptr->SetAlienVar(0, 8 + rand()%16 );
        tmpAgent1Ptr->SetAlienVar(1, 8 + rand()%16 );
        engine.entityScheduler.entities.push_back((Engine::Entity*)tmpAgent1Ptr);
    }




    Agent* playerAgentPtr;
    playerAgentPtr = new PlayerAgent();
//    playerAgentPtr->Compile("../Assets/player.c");
    playerAgentPtr->Compile("../Assets/test.c");
    playerAgentPtr->Assemble();
    playerAgentPtr->SetAlienVar(0, 16 );
    playerAgentPtr->SetAlienVar(1, 16 );
    engine.entityScheduler.entities.push_back((Engine::Entity*)playerAgentPtr);

    engine.MainLoop();
}