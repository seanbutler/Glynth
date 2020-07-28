//
// Created by sean on 28/07/2020.
//

#ifndef GLYNTH_MUTATIONS_H
#define GLYNTH_MUTATIONS_H

class Mutation {
    // a mutation is a type of change that can occur over a tree

};


// In point mutation, a random node is selected and the primitive
// stored there is replaced with a different random primitive of the same arity
// taken from the primitive set.

// In our case this means
//      an IF can be tweaked into a WHILE and vice versa
//      an +-*/ can be tweaked into another  +-*/
//      an > >= == <= < can be tweaked into another > >= == <= <
//      any  number can be tweaked into another number

//  perhaps some variables are a bit special
//      X Y can be tweaked into each other?
//      other normal vars perhaps can be swapped as they are indexed by numbers in memory

//  perhaps statements inside a block can be shuffled?
//      reorder within the same block, preserving some basis of existing logic


class PointMutation : public Mutation {
public:
    PointMutation(ASTNode* T) {

    }

};


class ComparisonMutation : public PointMutation {
public:
    ComparisonMutation(ASTNode* T) {

    }

};

class NumberMutation : public PointMutation {
public:
    NumberMutation(ASTNode* T) {

    }

};

class NudgeNumberMutation : public NumberMutation {
public:
    NudgeNumberMutation(ASTNode* T) {

    }

};

class RandNumberMutation : public NumberMutation {
public:
    RandNumberMutation(ASTNode* T) {

    }

};


#endif //GLYNTH_MUTATIONS_H
