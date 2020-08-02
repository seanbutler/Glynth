//
// Created by sean on 30/07/2020.
//

#include "Evolution.h"

namespace Genetics {

    void Evolution::MutateIndividual(Agent* agent)
    {
        MutationVisitor* mutation = new RandomizeNumberMutation();

        Mutagen mutagen;
        mutagen.AddMutation(mutation);

        for (auto node : agent->parser.abstractSyntaxTree ) {
            mutagen.Apply(node);
        }
    }

//    void Evolution::MutatePopulation() {
//        Mutagen mutagen;
//        MutationVisitor* mutation = new RandomizeNumberMutation();
//        mutagen.AddMutation(mutation);
//
//        for(auto I : population.individuals) {
//            mutagen.Apply(I->parser.abstractSyntaxTree[0]);
//        }
//    }
}
