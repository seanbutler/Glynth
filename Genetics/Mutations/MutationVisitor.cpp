//
// Created by sean on 28/07/2020.
//

#include "MutationVisitor.h"
#include <random>

namespace Genetics {

    // ----------------------------------------------------------------------

    void RandomizeNumberMutation::Effect(NumberAST& node) {
        /// Overwrites the existing value (number) with an integer generated from rand()
        node.setNumber(rand());
    };

    void RandomizeNumberMutation::Apply(NumberAST& node) {
        if ( Condition(node) ) {
            Effect(node);
        }
    };

};

// ----------------------------------------------------------------------
