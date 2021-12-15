#ifndef __PIECE_H__
#define __PIECE_H__

#include <memory>
#include <vector>
#include <utility>

#include "board.h"
#include "PieceVisitor.h"

// Forward Declarations
class Board;
class PieceVisitor;

class Piece {
    char color;
    int moved = 0;

    protected:
    	char type; //type of piece

    public:
        Piece(char color);

        virtual std::vector<std::pair<int, int>> getValidMoves(std::pair<int, int> position, Board &board) = 0;
        bool hasMoved();
        void move();
        void undoMove();
        char getType();
        char getColor();
        virtual int getValue() = 0;
        virtual void accept(PieceVisitor &pv, std::pair<int, int> pos) = 0;
        ~Piece();
};

#endif

