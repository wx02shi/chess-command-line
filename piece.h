#ifndef __PIECE_H__
#define __PIECE_H__

#include <memory>
#include <vector>
#include <utility>

#include "board.h"

class Piece {
    char color;
    protected:
    char type; //type of piece

    public:
        Piece(char color);
        // std::vector<std::pair<int, int>> getValidMoves(std::pair<int, int> position, Board b*);
        bool canHop();
        // TODO: to incorporate PIECEVISITOR
        // void accept(PieceVisitor *pv);
        char getType();
        ~Piece();
};
#endif
