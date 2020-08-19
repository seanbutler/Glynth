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

    bool xAxis = false;
    auto axisFitness = [&xAxis](Agent* agent){

        auto copy = new Agent(*agent);
        copy->Assemble();

        std::vector<int> uniqueLocations;
        auto startPos = std::pair<int,int>(copy->alienVars.get(0), copy->alienVars.get(1));
        int lastPos = xAxis ? startPos.first : startPos.second;
        int furthestDist = 0;
        int moveCount = 0;

        for(int i = 0; i < 10000; i++)
        {
            copy->Update(0);
            auto newPos = std::pair<int,int>(copy->alienVars.get(0), copy->alienVars.get(1));
            if((xAxis ? newPos.first : newPos.second) != lastPos)
                moveCount++;
            if((std::find(uniqueLocations.begin(), uniqueLocations.end(), xAxis ? newPos.first : newPos.second)) == uniqueLocations.end())
            {
                uniqueLocations.push_back(xAxis ? newPos.first : newPos.second);
            }
            float xDist = powf((float)fabs((double)startPos.first - (double)newPos.first),2.0f);
            float yDist = powf((float)fabs((double)startPos.second - (double)newPos.second),2.0f);
            int dist = (int)(xDist + (yDist));
            if(dist > furthestDist)
            {
                furthestDist = dist;
            }
            lastPos = xAxis ? newPos.first : newPos.second;
        }
        return ((int)(uniqueLocations.size()*5) +(moveCount*2) ) - furthestDist;
    };

    auto combinedFitness = [](Agent* agent){
        auto copy = new Agent(*agent);
        copy->Assemble();

        std::vector<std::pair<int,int>> uniqueLocations;
        auto startPos = std::pair<int,int>(copy->alienVars.get(0), copy->alienVars.get(1));
        auto lastPos = startPos;
        int furthestDist = 0;
        int moveCount = 0;

        for(int i = 0; i < 50000; i++)
        {
            copy->Update(0);
            auto newPos = std::pair<int,int>(copy->alienVars.get(0), copy->alienVars.get(1));
            if(newPos != lastPos)
                moveCount++;
            if((std::find(uniqueLocations.begin(), uniqueLocations.end(), newPos)) == uniqueLocations.end())
            {
                uniqueLocations.push_back(newPos);
                float xDist = powf((float)fabs((double)startPos.first - (double)newPos.first),3.0f);
                float yDist = powf((float)fabs((double)startPos.second - (double)newPos.second),3.0f);
                int dist = (int)sqrtf(xDist + (yDist));
                if(dist > furthestDist)
                {
                    furthestDist = dist;
                }
            }
        }
        return ((int)(uniqueLocations.size()*3) + moveCount) - furthestDist;
    };

    evolution.SetRandomiseFunction(hurtfulRand);
    evolution.SetFitnessFunction(axisFitness);
    evolution.InitialisePopulation(400,HurtfulAgentType(),"../Assets/agent2.c");
    evolution.RandomisePopulation();

    int maxGenerations = 30;
    for(int i = 0; i <maxGenerations; i++)
    {
        std::cout << "xAxis Pop: Creating generation " << i+1 << "/" << maxGenerations << "..." << std::endl;
        evolution.AssessFitness();
        evolution.GenerateNewPopulation(0.96f, 0.02f, 0.02f);
    }
    evolution.AssessFitness();

    auto xPop = evolution.GetTopPopulationAgents(0.25f, true);

    xAxis = false;
    evolution.InitialisePopulation(400, HurtfulAgentType(), "../Assets/agent2.c");
    evolution.RandomisePopulation();

    for(int i = 0; i <maxGenerations; i++)
    {
        std::cout << "yAxis Pop: Creating generation " << i+1 << "/" << maxGenerations << "..." << std::endl;
        evolution.AssessFitness();
        evolution.GenerateNewPopulation(0.96f, 0.02f, 0.02f);
    }

    auto yPop = evolution.GetTopPopulationAgents(0.25f, true);

    evolution.AddIndividuals(xPop);
    evolution.AddIndividuals(yPop);
    evolution.SetFitnessFunction(combinedFitness);

    maxGenerations = 20;
    for(int i = 0; i <maxGenerations; i++)
    {
        std::cout << "Combined Pop: Creating generation " << i+1 << "/" << maxGenerations << "..." << std::endl;
        evolution.AssessFitness();
        evolution.GenerateNewPopulation(0.96f, 0.02f, 0.02f);
    }

    int i =0;
    for(auto agent : evolution.GetTopPopulationAgents(0.1f, true))
    {
        agent->Assemble();
        agent->parser.OutputTreeDiagram("/home/toby/agent" + std::to_string(i));
        engine.entityScheduler.entities.push_back((Engine::Entity*)agent);
        i++;
    }
}
