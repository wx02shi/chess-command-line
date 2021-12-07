#ifndef __BISHOP_H__
#define __BISHOP_H__

#include "piece.h"

class Bishop : public Piece {
    public:
        Bishop(char color);
        std::vector<std::pair<int, int>> getValidMoves(std::pair<int, int> position, Board &board);
        void accept(PieceVisitor &pv, std::pair<int, int> pos);
        ~Bishop();
};

#endif