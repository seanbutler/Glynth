//
// Created by sean on 28/07/2020.
//

#include "MutationVisitor.h"
#include <random>
#include <iostream>

namespace Genetics {

    // ----------------------------------------------------------------------

    // TODO MAYBE THIS SHOULD BE PART OF THE MUTAGEN RATHER THAN THE MUTATION?
    bool RandomizeNumberMutation::Condition(const NumberAST* node) const  {
        return (((float)rand() / (float)RAND_MAX) <= probability);
    };

    void RandomizeNumberMutation::Effect(NumberAST* node) {
        if ( rand()%2 )
        {
            node->setNumber( node->getNumber() + 1 );
        }
        else
        {
            node->setNumber( node->getNumber() - 1 );
        }
    };

    void RandomizeNumberMutation::Visit_NumberAST(NumberAST* node)  {
        if (Condition(node) ) {
            Effect(node);
        }
    };

    // ----------------------------------------------------------------------

    bool RandomizeComparisonMutation::Condition(const BinOperandAST* node) const {

        if ((node->op == Token::OP_LT)
            || (node->op == Token::OP_LTE)
            || (node->op == Token::OP_EQ)
            || (node->op == Token::OP_GTE)
            || (node->op == Token::OP_GT)) {

            return (((float) rand() / (float) RAND_MAX) <= probability);
        }
        return false;
    };

    void RandomizeComparisonMutation::Effect(BinOperandAST* node) {

        switch (rand()%5){

            case 0:
                node->op = Token::OP_LT;
                return;
            case 1:
                node->op = Token::OP_LTE;
                return;
            case 2:
                node->op = Token::OP_EQ;
                return;
            case 3:
                node->op = Token::OP_GTE;
                return;
            case 4:
                node->op = Token::OP_GT;
                return;
        }
    };

    void RandomizeComparisonMutation::Visit_BinOperandAST(BinOperandAST* node)  {
        if (Condition(node) ) {
            Effect(node);
        }
    };

    // ----------------------------------------------------------------------

    bool RandomizeArithmeticMutation::Condition(const BinOperandAST* node) const {

        if ((node->op == Token::OP_ADD)
            || (node->op == Token::OP_SUB)
            || (node->op == Token::OP_MUL)
            || (node->op == Token::OP_DIV) ) {

            return (((float) rand() / (float) RAND_MAX) <= probability);
        }
        return false;
    };

    void RandomizeArithmeticMutation::Effect(BinOperandAST* node) {

        switch (rand()%4) {

            case 0:
                node->op = Token::OP_ADD;
                return;
            case 1:
                node->op = Token::OP_SUB;
                return;
            case 2:
                node->op = Token::OP_MUL;
                return;
            case 3:
                node->op = Token::OP_DIV;
                return;
        }
    };

    void RandomizeArithmeticMutation:: Visit_BinOperandAST(BinOperandAST* node)  {
        if (Condition(node) ) {
            Effect(node);
        }
    };

};

// ----------------------------------------------------------------------
