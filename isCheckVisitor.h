#ifndef __ISCHECKVISITOR_H__
#define __ISCHECKVISITOR_H__

#include "PieceVisitor.h"
#include <utility>

class IsCheckVisitor : public PieceVisitor {
    char inCheck = 0;

    public:
        IsCheckVisitor(Board &board);
        char getCheck();
        virtual void visit(Queen &queen, std::pair<int, int> pos) override;
        virtual void visit(Pawn &pawn, std::pair<int, int> pos) override;
        virtual void visit(King &king, std::pair<int, int> pos) override;
        virtual void visit(Bishop &bishop, std::pair<int, int> pos) override;
        virtual void visit(Knight &knight, std::pair<int, int> pos) override;
        virtual void visit(Rook &rook, std::pair<int, int> pos) override;
        virtual void visit(Empty &empty, std::pair<int, int> pos) override;
};

#endif
