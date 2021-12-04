#ifndef __QUEEN_H__
#define __QUEEN_H__

#include "piece.h"

class Queen: public Piece {
    public:
        Queen(char color);
        bool canHop();
        ~Queen();
};

#endif
