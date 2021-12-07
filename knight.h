#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "piece.h"

class Knight: public Piece {
  public:
    Knight(char color);
    std::vector<std::pair<int, int>> getValidMoves(std::pair<int, int> position, Board &board);
    bool canHop();
    void accept(PieceVisitor &pv, std::pair<int, int> pos);
    ~Knight();
};

#endif