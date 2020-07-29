//
// Created by sean on 28/07/2020.
//

#ifndef GLYNTH_MUTATOR_H
#define GLYNTH_MUTATOR_H

// ----------------------------------------------------------------------

class Mutator {

    // a parameterised tree walker/visitor
    // visits each node in a tree

public:
    Mutator(MutationScheme S, Mutation M)
    : mutationScheme(M)
    , mutation(M){

    }

    void Mutate(ASTNode* tree) {

    }

private:
    MutationScheme* mutationScheme;
    Mutation* mutation;
};

// ----------------------------------------------------------------------

class MutationScheme {

public:
    MutationScheme(float P, unsigned int MIN, unsigned int MAX)
    : probability(P)
    , minDepth(MIN)
    , maxDepth(MAX) {

    }

private:
    float probability;
    int minDepth, maxDepth;
};

// ----------------------------------------------------------------------

#endif //GLYNTH_MUTATOR_H
