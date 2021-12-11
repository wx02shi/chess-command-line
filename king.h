#ifndef __KING_H__
#define __KING_H__

#include "piece.h"

class King: public Piece {
    bool moved = false;

    public:
        King(char color);
        std::vector<std::pair<int, int>> getValidMoves(std::pair<int, int> position, Board &board);
        void accept(PieceVisitor &pv, std::pair<int, int> pos);
        int getValue();
        ~King();
};

#endif
