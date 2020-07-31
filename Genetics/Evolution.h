//
// Created by sean on 30/07/2020.
//

#ifndef GLYNTH_EVOLUTION_H
#define GLYNTH_EVOLUTION_H

#include <vector>
#include "../Simulation/Agent.h"

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

        const unsigned int MAX_POPULATION_SIZE = 32;

        void InitialisePopulation() {
            if (population.individuals.size() < MAX_POPULATION_SIZE) {

            }
        }


        void RandomizePopulation() {}

        void AssessFitness() {}

    public:
        Population population;
    };

// ----------------------------------------------------------------------

}

#endif //GLYNTH_EVOLUTION_H
