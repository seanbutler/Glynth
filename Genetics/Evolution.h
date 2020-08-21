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

        void InitialisePopulation(int popSize, const std::string& agentFilePath);
        void RandomisePopulation();
        void AssessFitness();
        void GenerateNewPopulation(float crossover = 0.9f, float reproduction = 0.09f, float mutation = 0.01f);

        void AddIndividual(Agent *newIndividual);
        void AddIndividuals(const std::vector<Agent*>& newIndividuals);
        void SetFitnessFunction(const std::function<float(Agent*)> &function);
        void SetRandomiseFunction(const std::function<void(Agent*)> &function);

        std::vector<Agent*> GetTopPopulationAgents(float percent, bool clearPopulation);

    private:
        std::function<float(Agent*)> fitnessFunction;
        std::function<void(Agent*)> randomiseAgentVars;
        std::vector<Individual> population;

        std::default_random_engine randEngine;
    };

// ----------------------------------------------------------------------

}
