//
// Created by sean on 30/07/2020.
//

#pragma once

#include <vector>
#include "../Simulation/Agent.h"
#include "./Mutations/Mutagen.h"
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
        Evolution()             {}
        virtual ~Evolution()    {}

//        void InitialisePopulation() {}
//        void RandomizePopulation()  {}

        void MutatePopulation()  {
            Mutagen mutagen;
//            RandomizeNumberMutation mutation;
//            mutagen.AddMutation(&mutation);
//
//            for(auto I : population.individuals) {
//                mutagen.Apply(I->parser.abstractSyntaxTree[0]);
//            }
        }

//        void AssessFitness()          {}


    public:
        Population population;
    };

// ----------------------------------------------------------------------

}
