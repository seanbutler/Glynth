//
// Created by sean on 30/07/2020.
//

#pragma once

#include <vector>
#include "../Simulation/Agent.h"
#include "./Mutations/Mutagen.h"
#include "Mutations/MutationVisitor.h"
//#include "./Mutations/Mutator.h"

// ----------------------------------------------------------------------

namespace Genetics {


    // ----------------------------------------------------------------------

    struct Individual {
    public:
        explicit Individual(Agent* agt) : agent(agt){};
        Individual() = default;

        Agent* agent = nullptr;
        float fitness = 0;
        bool scored = false;
    };

    // ----------------------------------------------------------------------

    class Evolution {

    public:
        Evolution();

        virtual ~Evolution() {}

        void MutateIndividual(Agent *agent);

        void MutateNodeAndChildren(ASTNode *node, Mutagen &mutagen);

        Agent* CopyAgent(Agent* original);
        void CopyNodeAndChildren(ASTNode*& original, ASTNode*& copy);

        void InitialisePopulation(int popSize);
        void RandomizePopulation();
        void AssessFitness();
        void GenerateNewPopulation(float crossover = 0.9f, float reproduction = 0.09f, float mutation = 0.01f);

        void AddIndividual(Agent *newIndividual);
        void SetFitnessFunction(const std::function<float(Agent*)> &function);
        void SetInitFunction(const std::function<Agent*()> &function);

        std::vector<Agent*> GetPopulationAgents();

    private:
        std::function<float(Agent*)> fitnessFunction;
        std::function<Agent*()> initFunction;
        std::vector<Individual> population;

        std::default_random_engine randEngine;
    };

// ----------------------------------------------------------------------

}
