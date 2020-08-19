//
// Created by sean on 28/07/2020.
//

#pragma once

#include <random>


class ASTNode;


namespace Genetics {

    class MutationVisitor;

    class Mutagen {
        /// Passes over the tree and applies appropriate Mutations to each node
    public:
        Mutagen()
//        : mutationVisitor(nullptr)
        {

        }

        ~Mutagen()
        {
            for(auto visitor : mutations)
            {
                delete visitor;
            }
        }

        void AddMutation(MutationVisitor* MV) {
//            mutationVisitor = MV;
            mutations.push_back(MV);
        }

        void Apply(ASTNode* node);

    public:
//        MutationVisitor* mutationVisitor;
        std::vector<MutationVisitor*> mutations;
    };

};

// ----------------------------------------------------------------------
