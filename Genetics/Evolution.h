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

        Agent* agent = nullptr;
        float fitness = 0;
        bool scored = false;
    };

    // ----------------------------------------------------------------------

    class Evolution {

    public:
        Evolution() {}

        virtual ~Evolution() {}

        void MutateIndividual(Agent *agent);

        void MutateNodeAndChildren(ASTNode *node, Mutagen &mutagen);

        Agent* CopyAgent(Agent* original);
        ASTNode* CopyNodeAndChildren(ASTNode*& original, ASTNode*& copy);

//        void InitialisePopulation()       {}
//        void RandomizePopulation()        {}
        void MutatePopulation();
        void AssessFitness();

        void AddIndividual(Agent *newIndividual);
        void SetFitnessFunction(const std::function<float(Agent*)> &function);

        std::vector<Agent*> GetPopulationAgents();

    private:
        std::function<float(Agent*)> fitnessFunction;
        std::vector<Individual> population;
    };

// ----------------------------------------------------------------------

}
