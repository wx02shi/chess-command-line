#ifndef __IS_CHECKMATE_VISITOR__
#define __IS_CHECKMATE_VISITOR__

#include "PieceVisitor.h"

struct isCheckmateVisitor : public PieceVisitor{
    virtual void visit(Queen &queen) override;
    virtual void visit(Knight &knight) override;
    virtual void visit(Bishop &bishop) override;
    virtual void visit(Rook &rook) override;
    virtual void visit(King &king) override;
    virtual void visit(Pawn &pawn) override;
    virtual void visit(Empty &empty) override;


};


#endif