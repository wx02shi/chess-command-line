#ifndef __ROOK_H__
#define __ROOK_H__

#include "piece.h"

class Rook: public Piece {
    bool moved = false;

    public:
        Rook(char color);
        std::vector<std::pair<int, int>> getValidMoves(std::pair<int, int> position, Board &board);
        void accept(PieceVisitor &pv, std::pair<int, int> pos);
        int getValue();
        ~Rook();
};

#endif
