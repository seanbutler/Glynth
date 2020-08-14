//
// Created by sean on 28/07/2020.
//

#include "../../Language/AST.h"
#include "Mutagen.h"
#include "MutationVisitor.h"

namespace Genetics {

    void Mutagen::Apply(ASTNode *node) {

        for(MutationVisitor* M : this->mutations) {
            node->Accept(M);
            //for (auto *c : node->children) {
            //    c->Accept(M);
            //}
        }

    }
};


// ----------------------------------------------------------------------
