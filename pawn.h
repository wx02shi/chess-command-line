#ifndef _PAWN_
#define _PAWN_

#include "piece.h"


class Pawn: public Piece {
    public:
    Pawn(char color);
    std::vector<std::pair<int, int>> getValidMoves(std::pair<int, int> position, Board &board);
    bool canHop();
    void accept(PieceVisitor &pv, std::pair<int, int> pos);
    ~Pawn();

};






#endif