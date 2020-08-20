//
// Created by sean on 14/08/2020.
//

#include <stdio.h>
#include "TobyTest.h"
#include "../Engine/Engine.h"
#include "../Genetics/Evolution.h"

void TobyTest::TestPopulation(Engine::Engine &engine)
{
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

        for(int i = 0; i < 500; i++)
        {
            copy->Update(0);
            auto newPos = std::pair<int,int>(copy->alienVars.get(0), copy->alienVars.get(1));
            if((std::find(uniqueLocations.begin(), uniqueLocations.end(), newPos)) == uniqueLocations.end())
            {
                uniqueLocations.push_back(newPos);
                int dist = powf(abs(startPos.first - newPos.first),3) + powf(abs(startPos.second - newPos.second),3);
                if(dist > furthestDist)
                {
                    furthestDist = dist;
                }
            }
        }
        return (uniqueLocations.size()*25) - furthestDist;
    };

    evolution.SetRandomiseFunction(hurtfulRand);
    evolution.SetFitnessFunction(hurtfulFitness);
    evolution.InitialisePopulation(200,"../Assets/agent2.c");
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
}
