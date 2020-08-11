#include <iostream>
#include <fstream>
#include<stdlib.h>
#include<time.h>

#include "./Language/Lexer.h"
#include "./Language/Parser.h"
#include "./Language/Assembler.h"
#include "./Language/VirtualMachine.h"

#include "./Engine/Engine.h"
#include "./Engine/Entity.h"

#include "./Simulation/Agent.h"
#include "./Simulation/MazeEnvironment.h"
#include "./Simulation/WallEnvironment.h"
#include "./Simulation/ForestEnvironment.h"

#include "./Genetics/Evolution.h"

int main(int argc, char **argv) {
    std::cout << "GLYNTH - Game Language Program Synthesis" << std::endl;
    srand(time(nullptr));

    Engine::Engine engine(32, 32);
    Genetics::Evolution evolution;

    auto hurtfulRand = [](Agent* agent){
        agent->SetAlienVar(0, 8 + (int)rand()%16);
        agent->SetAlienVar(1, 8 + (int)rand()%16);
    };

    auto hurtfulFitness = [](Agent* agent){
        auto copy = new Agent(*agent);
        copy->Assemble();

        std::vector<std::pair<int,int>> uniqueLocations;
        auto startPos = std::pair<int,int>(copy->alienVars.get(0), copy->alienVars.get(1));
        int furthestDist = 0;

        for(int i = 0; i < 1000; i++)
        {
            copy->Update(0);
            auto newPos = std::pair<int,int>(copy->alienVars.get(0), copy->alienVars.get(1));
            if((std::find(uniqueLocations.begin(), uniqueLocations.end(), newPos)) == uniqueLocations.end())
            {
                uniqueLocations.push_back(newPos);
                int dist =  abs(startPos.first - newPos.first) + abs(startPos.second - newPos.second);
                if(dist > furthestDist)
                {
                    furthestDist = dist;
                }
            }
        }
        return uniqueLocations.size() - furthestDist;
    };

    evolution.SetRandomiseFunction(hurtfulRand);
    evolution.SetFitnessFunction(hurtfulFitness);
    evolution.InitialisePopulation(200,HurtfulAgentType(),"../Assets/agent2.c");
    evolution.RandomisePopulation();

    int maxGenerations = 30;
    for(int i = 0; i <maxGenerations; i++)
    {
        std::cout << "Creating generation " << i+1 << "/" << maxGenerations << "..." << std::endl;
        evolution.AssessFitness();
        evolution.GenerateNewPopulation(0.96f, 0.02f, 0.02f);
    }
    evolution.AssessFitness();

    int i =0;
    for(auto agent : evolution.GetTopPopulationAgents(0.05f))
    {
        agent->Assemble();
        agent->parser.OutputTreeDiagram("/home/toby/agent" + std::to_string(i));
        engine.entityScheduler.entities.push_back((Engine::Entity*)agent);
        i++;
    }



//    MazeEnvironment* environment = new MazeEnvironment(32, 32);
//    engine.entityScheduler.entities.push_back((Entity*)environment);

//    WallEnvironment* environment1 = new WallEnvironment('V', 32, 32);
//    engine.entityScheduler.entities.push_back((Engine::Entity*)environment1);
//
//    WallEnvironment* environment2 = new WallEnvironment('H', 32, 32);
//    engine.entityScheduler.entities.push_back((Engine::Entity*)environment2);

//    ForestEnvironment* environment2 = new ForestEnvironment(32, 32);
//    engine.entityScheduler.entities.push_back((Engine::Entity*)environment2);

//    Agent* goalAgentPtr = new Agent("./Assets/goal.c", GoalAgentType());
//    engine.entityScheduler.entities.push_back((Engine::Entity*)goalAgentPtr);
//    goalAgentPtr->SetAlienVar(0, 24 + (int)rand()%8);
//    goalAgentPtr->SetAlienVar(1, 24 + (int)rand()%8);
//
//    Agent* playerAgentPtr = new Agent("./Assets/player.c", PlayerAgentType());
//    engine.entityScheduler.entities.push_back((Engine::Entity*)playerAgentPtr);
//    evolution.population.individuals.push_back(playerAgentPtr);
//    playerAgentPtr->SetAlienVar(0, 2 + (int)rand()%4);
//    playerAgentPtr->SetAlienVar(1, 2 + (int)rand()%4);
//
//    Agent* tmpAgent2Ptr;
//    for (int n=0;n<4;n++) {
//        tmpAgent2Ptr = new Agent(HurtfulAgentType());
//        tmpAgent2Ptr->Compile("../Assets/agent2.c");
//
//        evolution.MutateIndividual(tmpAgent2Ptr);
//
//        tmpAgent2Ptr->Assemble();
//        tmpAgent2Ptr->SetAlienVar(0, 8 + (int)rand()%16);
//        tmpAgent2Ptr->SetAlienVar(1, 8 + (int)rand()%16);
//
//        engine.entityScheduler.entities.push_back((Engine::Entity*)tmpAgent2Ptr);
//    }

//    evolution.MutatePopulation(); // LETS TRY MUTATING EACH INDIVIDUAL IN SITU INSTEAD OF TEH WHOLE POPYLATION

    //Agent* tmpAgent3Ptr;
    //for (int n=0;n<16;n++){
    //    tmpAgent3Ptr = new Agent(HealingAgentType());
    //    tmpAgent3Ptr->Compile("../Assets/agent3.c");
//
    //    evolution.MutateIndividual(tmpAgent3Ptr);
//
    //    tmpAgent3Ptr->Assemble();
    //    tmpAgent3Ptr->SetAlienVar(0, 8 + (int)rand()%16);
    //    tmpAgent3Ptr->SetAlienVar(1, 8 + (int)rand()%16);
//
    //    engine.entityScheduler.entities.push_back((Engine::Entity*)tmpAgent3Ptr);
    //}

//    evolution.MutatePopulation();

    engine.MainLoop();
    return 0;
}

