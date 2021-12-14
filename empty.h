#ifndef __EMPTY_H__
#define __EMPTY_H__

#include "piece.h"

class Empty: public Piece {
    public:
        Empty();
        std::vector<std::pair<int, int>> getValidMoves(std::pair<int, int> position, Board &board);
        int getValue();
        void accept(PieceVisitor &pv, std::pair<int, int> pos);
        ~Empty();
};

#endif

