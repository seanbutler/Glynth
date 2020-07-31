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
            return ((rand() / RAND_MAX) >= probability);
        };

        virtual void Effect(ASTNode& node) {
            static_cast<NumberAST&>(node).val = rand();
        };

    private:
        const float probability = 0.5;
    };

    // ----------------------------------------------------------------------

    class NullMutator {

        // Declares all the interfaces/methods for the mutators

    public:
        virtual void Mutate(ASTNode& node) {};

        virtual void Mutate(IdentifierAST& node) {};
        virtual void Mutate(AlienVarAST& node) {};
        virtual void Mutate(VariableDeclarationAST& node) {};

        virtual void Mutate(IfStatementAST& node) {};
        virtual void Mutate(WhileStatementAST& node) {};
        virtual void Mutate(AssignmentStatementAST& node) {};

        virtual void Mutate(BlockAST& node) {};

        virtual void Mutate(OutputAST& node) {};
        virtual void Mutate(MoveAST& node) {};

        virtual void Mutate(NumberAST& node) {};
        virtual void Mutate(BinOperandAST& node) {};

        virtual void Mutate(YieldAST& node) {};

//        virtual void Mutate(StdFuncAST& node) {};
//        virtual void Mutate(RandAST& node) {};


    };

    // Terminals...

    class RandomizeNumberMutator : public NullMutator {
        /// Overwrites the existing value (number) with an integer generated from rand()
        virtual void Mutate(NumberAST& node) {
            node.val = rand();
        };
    };

    // ----------------------------------------------------------------------

    // Non Terminals...

    class BlockShufflerMutator : public NullMutator {
        /// Rearranges the order of the statements within a block ()
        virtual void Mutate(BlockAST& node) {

        };
    };

};

// ----------------------------------------------------------------------

#endif //GLYNTH_MUTATOR_H
