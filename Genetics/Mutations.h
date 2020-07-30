//
// Created by sean on 28/07/2020.
//

#include "../Language/AST.h"

#ifndef GLYNTH_MUTATIONS_H
#define GLYNTH_MUTATIONS_H

namespace Genetics {

// ----------------------------------------------------------------------

    // a mutation is a type of change that can occur over a tree
    // some mutations occur within a node (PointMutation),
    // others grow the tree, others substitute tree parts


// ----------------------------------------------------------------------


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


// ----------------------------------------------------------------------

//
// NUMBER MUTATION
//
// any  number can be tweaked into another number

//    class NumberMutation :  {
//        // SET TO ARBITRARY RANDOM NUMBER, let the context handle the result
//    public:
//        void Mutate(NumberAST & T) {
//            T.val = rand();
//        }
//    };

//    class NudgeNumberMutation : public NumberMutation {
//        // PLUS ONE, MINUS ONE, OR NOTHING +1, 0, -1
//    public:
//        void Mutate(NumberAST & T) {
//            T.val += (rand()%3)-1;
//        }
//    };

//    class DistNumberMutation : public NumberMutation {
//        // RANDOM OFFSET IN THE ORDER OF THE NUMBER ITSELF i.e. +N or -N
//    public:
//        void Mutate(NumberAST& T) {
//            T.val += (rand()%T.val)-(rand()%T.val);
//        }
//    };

// ----------------------------------------------------------------------

//
// MATH MUTATION
//
// a maths op can be tweaked into another, with limits...
//      an +-*/ can be tweaked into another  +-*/
//      an > >= == <= < can be tweaked into another > >= == <= <

//class MathMutation : public PointMutation {
//public:
//    Mutate(ASTNode* T) {
//    }
//};
//
//class MathOpMutation : public MathMutation {
//public:
//    Mutate(ASTNode* T) {
//    }
//};
//
//class MathCompMutation : public MathMutation {
//public:
//    Mutate(ASTNode* T) {
//    }
//};

// ----------------------------------------------------------------------


}


#endif //GLYNTH_MUTATIONS_H
