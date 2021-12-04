#include "queen.h"

Queen::Queen(char color) : Piece{color} {
    type = 'q';
}

bool Queen::canHop() {
    return false;
}

Queen::~Queen() {}
