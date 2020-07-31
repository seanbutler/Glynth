//
// Created by sean on 28/07/2020.
//

#ifndef GLYNTH_MUTATOR_H
#define GLYNTH_MUTATOR_H

#include "./Mutations.h"

namespace Genetics {

    // ----------------------------------------------------------------------

    class Mutation {

        /// Declares all the interfaces/methods for the mutators

    public:
        virtual void Apply(ASTNode* node) {};

        virtual void Apply(IdentifierAST* node) {};
        virtual void Apply(AlienVarAST* node) {};
        virtual void Apply(VariableDeclarationAST* node) {};

        virtual void Apply(IfStatementAST* node) {};
        virtual void Apply(WhileStatementAST* node) {};
        virtual void Apply(AssignmentStatementAST* node) {};

        virtual void Apply(BlockAST* node) {};

        virtual void Apply(OutputAST* node) {};
        virtual void Apply(MoveAST* node) {};

        virtual void Apply(NumberAST* node) {};
        virtual void Apply(BinOperandAST* node) {};

        virtual void Apply(YieldAST* node) {};

//        virtual void Apply(StdFuncAST* node) {};
//        virtual void Apply(RandAST* node) {};

    };

    // Terminals...

    class RandomizeNumberMutation : public Mutation {

        // TODO MAYBE THIS SHOULD BE PART OF THE MUTAGEN RATHER THAN THE MUTATION
        const float probability = 0.5;
        virtual bool Condition(NumberAST& node) {
            return ((rand() / RAND_MAX) >= probability);
        };

        virtual void Effect(NumberAST& node) {
            /// Overwrites the existing value (number) with an integer generated from rand()
            node.setNumber(rand());
        };

        virtual void Apply(NumberAST& node) {
            if ( Condition(node) ) {
                Effect(node);
            }
        };
    };

    // ----------------------------------------------------------------------

    class Mutagen {
        /// Passes over the tree and applies appropriate Mutations to each node
    public:
        Mutagen() {}

        void SetMutation(Mutation& M) {
            mutation = M;
        }

        void Apply(ASTNode* node) {
            this->mutation.Apply(node);
            for(auto c : node->children) {
                this->Apply(c);
            }
        }

    public:
        Mutation mutation;
    };


};

// ----------------------------------------------------------------------

#endif //GLYNTH_MUTATOR_H
