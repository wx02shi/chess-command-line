#ifndef __IS_STALEMATE_VISITOR__
#define __IS_STALEMATE_VISITOR__

#include "PieceVisitor.h"
#include <utility>

class IsStalemateVisitor : public PieceVisitor {
    // if the piece is in "stalemate" means theres no moves
    // else the piece has moves
    bool isPieceInStalemate = true;

    public:
        IsStalemateVisitor(Board &board);
        bool getStalemate();
        virtual void visit(Queen &queen, std::pair<int, int> pos) override;
        virtual void visit(Pawn &pawn, std::pair<int, int> pos) override;
        virtual void visit(King &king, std::pair<int, int> pos) override;
        virtual void visit(Bishop &bishop, std::pair<int, int> pos) override;
        virtual void visit(Knight &knight, std::pair<int, int> pos) override;
        virtual void visit(Rook &rook, std::pair<int, int> pos) override;
        virtual void visit(Empty &empty, std::pair<int, int> pos) override;
};

#endif
