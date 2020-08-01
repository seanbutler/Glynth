//
// Created by sean on 28/07/2020.
//

#pragma once

#include <random>

class MutationVisitor;
class ASTNode;

namespace Genetics {

    class Mutagen {
        /// Passes over the tree and applies appropriate Mutations to each node
    public:
        Mutagen() {}

        void AddMutation(MutationVisitor* MV) {
            mutationVisitor = MV;
        }

        void Apply(ASTNode* node);

    public:
        MutationVisitor *mutationVisitor;
    };

};

// ----------------------------------------------------------------------
