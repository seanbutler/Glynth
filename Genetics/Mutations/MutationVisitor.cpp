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
        const float probability = 0.5;
        return (((float)rand() / (float)RAND_MAX) <= probability);
    };

    void RandomizeNumberMutation::Effect(NumberAST* node) {
        node->setNumber( node->getNumber() + (  (rand() % 3)-1   ) );
    };

    void RandomizeNumberMutation::Visit_NumberAST(NumberAST* node)  {
        if (Condition(node) ) {
            Effect(node);
        }
    };

};

// ----------------------------------------------------------------------
