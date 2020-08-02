//
// Created by sean on 28/07/2020.
//

#include "../../Language/AST.h"
#include "Mutagen.h"
#include "MutationVisitor.h"

namespace Genetics {

    void Mutagen::Apply(ASTNode *node) {

        node->Accept(mutationVisitor);
        for (ASTNode *c : node->children) {
            c->Accept(mutationVisitor);
        }
    }
};


// ----------------------------------------------------------------------
