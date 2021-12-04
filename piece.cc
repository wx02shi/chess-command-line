#include "piece.h"

Piece::Piece(char color) : color{color} {}

bool Piece::canHop() {
    return false;
}

char Piece::getType() {
    if (color == 'w') {
        return type - 32;
    }
    return type;
}

Piece::~Piece() {}
