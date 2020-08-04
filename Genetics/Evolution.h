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

    using Individual = Agent;

    // ----------------------------------------------------------------------

    class Population {
    public:
        std::vector<Individual *> individuals;
    };

    // ----------------------------------------------------------------------

    class Evolution {

    public:
        Evolution()                         {}
        virtual ~Evolution()                {}

        void MutateIndividual(Agent* agent);
        void MutateNodeAndChildren(ASTNode* node, Mutagen& mutagen);

//        void InitialisePopulation()       {}
//        void RandomizePopulation()        {}
//        void MutatePopulation();
//        void AssessFitness()              {}


    public:
//        Population population;
    };

// ----------------------------------------------------------------------

}
