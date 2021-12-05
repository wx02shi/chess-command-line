#ifndef __PIECE_H__
#define __PIECE_H__

#include <memory>
#include <vector>
#include <utility>

#include "board.h"

class Board;

class Piece {
    char color;
    protected:
    char type; //type of piece

    public:
        Piece(char color);

        virtual std::vector<std::pair<int, int>> getValidMoves(std::pair<int, int> position, Board &board) = 0;
        bool canHop();
        // TODO: to incorporate PIECEVISITOR
        // void accept(PieceVisitor *pv);
        char getType();
        char getColor();
        ~Piece();
};
#endif
