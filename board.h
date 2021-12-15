#ifndef __BOARD_H__
#define __BOARD_H__

#include <memory>
#include <utility>
#include <vector>
#include "piece.h"

class Piece;

class Board {
    std::vector<std::vector<std::shared_ptr<Piece>>> pieces{8, std::vector<std::shared_ptr<Piece>>(8)};

    std::shared_ptr<Piece> lastMovedPiece;
    std::shared_ptr<Piece> lastEatenPiece;
    std::pair<int, int> lastMoveStart;
    std::pair<int, int> lastMoveEnd;

    public:
        Board();
        std::shared_ptr<Piece> getPiece(std::pair<int, int> position);
        bool movePieceTo(std::shared_ptr<Piece> piece, std::pair<int, int> from, std::pair<int, int> to);
        void setPiece(std::shared_ptr<Piece> piece, std::pair<int, int> position);
        void undo();
        void clear();
        ~Board();
};

#endif
