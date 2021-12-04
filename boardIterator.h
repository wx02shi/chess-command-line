#ifndef _BOARD_ITERATOR_
#define _BOARD_ITERATOR_
#include "board.h"
#include "piece.h"
class BoardIterator {

    // TODO: use smart pointer
    Piece *piece;

    public:
        explicit BoardIterator(Piece *piece);



};

#endif
