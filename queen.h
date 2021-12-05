#ifndef __QUEEN_H__
#define __QUEEN_H__

#include "piece.h"

class Queen: public Piece {
    public:
        Queen(char color);
        std::vector<std::pair<int, int>> getValidMoves(std::pair<int, int> position, Board &board);

        ~Queen();
};

#endif
