#ifndef _BOARD_ITERATOR_
#define _BOARD_ITERATOR_
#include "board.h"
#include "piece.h"
class BoardIterator {

    // TODO: use smart pointer
    std::shared_ptr<Board> board;
    std::shared_ptr<Piece> piece;
    std::pair<int, int> position;

    public:
        explicit BoardIterator(std::shared_ptr<Board> board);
        std::shared_ptr<Piece> &operator*();
        bool operator!=(const shared_ptr<BoardIterator> other);
        BoardIterator &operator++();

};

#endif
