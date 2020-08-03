//
// Created by sean on 30/07/2020.
//

#include "Evolution.h"

namespace Genetics {

    void Evolution::MutateIndividual(Agent* agent)
    {

        Mutagen mutagen;
//        mutagen.AddMutation(new RandomizeComparisonMutation(0.5));
//        mutagen.AddMutation(new RandomizeNumberMutation(0.5));
        mutagen.AddMutation(new RandomizeArithmeticMutation(0.5));

        for (auto node : agent->parser.abstractSyntaxTree ) {
            mutagen.Apply(node);
            for( auto child : node->children) {
                mutagen.Apply(child);
            }
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
