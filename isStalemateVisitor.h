#ifndef __IS_STALEMATE_VISITOR__
#define __IS_STALEMATE_VISITOR__

#include "PieceVisitor.h"

struct isStalemateVisitor : public PieceVisitor{
    virtual void visit(Queen &queen) override;

};


#endif