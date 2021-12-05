#ifndef __ISCHECKVISITOR_H__
#define __ISCHECKVISITOR_H__

#include "PieceVisitor.h"

struct isCheckVisitor : public PieceVisitor {
    virtual void visit(Queen &queen) override;

};

#endif