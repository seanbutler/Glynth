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

        virtual void Visit_IdentifierAST( IdentifierAST* node)   {};
        virtual void Visit_VariableDeclarationAST( VariableDeclarationAST* node)  {};
        virtual void Visit_YieldAST( YieldAST* node)  {};
        virtual void Visit_BlockAST( BlockAST* node) {};
        virtual void Visit_OutputAST( OutputAST* node)  {};
        virtual void Visit_MoveAST( MoveAST* node) {};
        virtual void Visit_RandFuncAST( RandFuncAST* node) {};
        virtual void Visit_SenseFuncAST( SenseFuncAST* node) {};
        virtual void Visit_IfStatementAST( IfStatementAST* node) {};
        virtual void Visit_WhileStatementAST( WhileStatementAST* node) {};
        virtual void Visit_AssignmentStatementAST( AssignmentStatementAST* node) {};
        virtual void Visit_ExpressionAST( AssignmentStatementAST* node) {};

        virtual void Visit_BinOperandAST( BinOperandAST* node){};
        virtual void Visit_NumberAST(NumberAST* node){};

//        const virtual void Visit_AlienVarAST(const AlienVarAST* node) {};
//        const virtual void Visit_OutputAST(const OutputAST* node) {};
//        const virtual void Visit_StdFuncAST(const StdFuncAST* node) {};

    };

    class RandomizeNumberMutation : public MutationVisitor {
    public:
        RandomizeNumberMutation(const float P)
        : probability(P) {
        }

    public:
        virtual bool Condition(const NumberAST* node) const;
        virtual void Effect(NumberAST* node);
        virtual void Visit_NumberAST(NumberAST* node) override;

    private:
        const float probability;
    };


    class RandomizeComparisonMutation : public MutationVisitor {
    public:
        RandomizeComparisonMutation(const float P)
            : probability(P) {
        }

    public:
        virtual bool Condition(const BinOperandAST* node) const;
        virtual void Effect(BinOperandAST* node);
        virtual void Visit_BinOperandAST(BinOperandAST* node) override;

    private:
        const float probability;

    };

    class RandomizeArithmeticMutation : public MutationVisitor {
    public:
        RandomizeArithmeticMutation(const float P)
            : probability(P) {
        }

    public:
        virtual bool Condition(const BinOperandAST* node) const;
        virtual void Effect(BinOperandAST* node);
        virtual void Visit_BinOperandAST(BinOperandAST* node) override;

    private:
        const float probability;
    };

};

// ----------------------------------------------------------------------
