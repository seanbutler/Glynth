//
// Created by sean on 28/07/2020.
//

#pragma once

#include <random>
#include "../../Language/AST.h"

class ASTNode;
class IdentifierAST;
class AlienVarAST;
class VariableDeclarationAST;
class BlockAST;
class OutputAST;
class MoveAST;
class RandFuncAST;
class IfStatementAST;
class WhileStatementAST;
class AssignmentStatementAST;

class NumberAST;
class BinOperandAST;
class YieldAST;

namespace Genetics {

    // ----------------------------------------------------------------------

    class MutationVisitor {

        /// Declares all the interfaces/methods for the mutators

    public:
//        virtual void Visit(ASTNode* node) {};

        virtual void Visit_IdentifierAST(const IdentifierAST* node) const  {};
        virtual void Visit_VariableDeclarationAST(const VariableDeclarationAST* node) const {};
        virtual void Visit_YieldAST(const YieldAST* node) const {};
        virtual void Visit_BlockAST(const BlockAST* node)const {};
        virtual void Visit_OutputAST(const OutputAST* node) const {};
        virtual void Visit_MoveAST(const MoveAST* node) const{};
        virtual void Visit_RandFuncAST(const RandFuncAST* node) const{};
        virtual void Visit_IfStatementAST(const IfStatementAST* node) const{};
        virtual void Visit_WhileStatementAST(const WhileStatementAST* node) const{};
        virtual void Visit_BinOperandAST(const BinOperandAST* node)const {};
        virtual void Visit_AssignmentStatementAST(const AssignmentStatementAST* node)const  {};
        virtual void Visit_NumberAST(const NumberAST* node) const {};

//        const virtual void Visit_AlienVarAST(const AlienVarAST* node) {};
//        const virtual void Visit_OutputAST(const OutputAST* node) {};
//        const virtual void Visit_StdFuncAST(const StdFuncAST* node) {};

    };

    class RandomizeNumberMutation : public MutationVisitor {

        // TODO MAYBE THIS SHOULD BE PART OF THE MUTAGEN RATHER THAN THE MUTATION
        virtual bool Condition(NumberAST& node) {
            const float probability = 0.5;
            return ((rand() / RAND_MAX) >= probability);
        };

        virtual void Effect(NumberAST& node);
        virtual void Apply(NumberAST& node);
    };

};

// ----------------------------------------------------------------------
