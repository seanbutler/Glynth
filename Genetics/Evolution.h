//
// Created by sean on 30/07/2020.
//

#ifndef GLYNTH_EVOLUTION_H
#define GLYNTH_EVOLUTION_H

#include <vector>
#include "../Simulation/Agent.h"
#include "./Mutations/Mutator.h"

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
        Evolution() {}
        virtual ~Evolution() {}

//        void InitialisePopulation() {}
//        void RandomizePopulation()  {}

        void MutatePopulation()  {
            Mutagen mutagen;
            RandomizeNumberMutation mutation;
            mutagen.AddMutation(mutation);
//            mutagen.Apply(population.individuals[0].);
        }

//        void AssessFitness()        {}


    public:
        Population population;
    };

// ----------------------------------------------------------------------

}

#endif //GLYNTH_EVOLUTION_H
