#ifndef __IS_CHECKMATE_VISITOR__
#define __IS_CHECKMATE_VISITOR__

#include "PieceVisitor.h"

struct isCheckmateVisitor : public PieceVisitor{
    virtual void visit(Queen &queen) override;

};


#endif