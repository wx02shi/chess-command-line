#ifndef __BOARD_H__
#define __BOARD_H__

#include <memory>
#include <utility>
#include <vector>
#include "piece.h"

class Piece;

class Board {
    std::vector<std::vector<std::shared_ptr<Piece>>> pieces{8, std::vector<std::shared_ptr<Piece>>(8)};
    std::pair<Piece *, std::pair<int, int>> lastMoved;
    public:
        Board();
        std::shared_ptr<Piece> getPiece(std::pair<int, int> position);
        // std::vector<std::vector<std::shared_ptr<Piece>>> getPieces();
        // void movePieceTo(Piece *piece, std::pair<int, int> position);
        void movePieceTo(std::shared_ptr<Piece> piece, std::pair<int, int> from, std::pair<int, int> to);
        void setPiece(std::shared_ptr<Piece> piece, std::pair<int, int> position);
        bool isValidMove(Piece &piece, std::pair<int, int> position);
        void clear();
        // getState(); ???
        // BoardIterator begin();
        // BoardIterator end();
        ~Board();
};

#endif
