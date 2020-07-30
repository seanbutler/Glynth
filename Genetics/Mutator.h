//
// Created by sean on 28/07/2020.
//

#ifndef GLYNTH_MUTATOR_H
#define GLYNTH_MUTATOR_H

#include "./Mutations.h"

namespace Genetics {

    // ----------------------------------------------------------------------

    class Mutation {

    public:
        Mutation() = default;
        ~Mutation() = default;

        virtual bool Condition(ASTNode& node) = 0;
        virtual void Effect(ASTNode& node) = 0;
    };


    class NumberMutation : public Mutation {

    public:
        virtual bool Condition(ASTNode& node) {
            if ( (rand() / RAND_MAX) >= probability ) {
                this->Effect(node);
            }
        };
        virtual void Effect(ASTNode& node) {
            static_cast<NumberAST&>(node).val = rand();
        };

    private:
        const float probability = 0.5;
    };

    // ----------------------------------------------------------------------

    class Mutator {

        // a parameterised tree walker/visitor
        // visits each node in a tree

    public:
        Mutator(const Mutation & M)
            : mutation(M) {
        }

        void Mutate(ASTNode* tree) {
        }

    private:
        const Mutation& mutation;
    };


};

// ----------------------------------------------------------------------


#endif //GLYNTH_MUTATOR_H
