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

char Piece::getColor() {
    return color;
}

bool Piece::hasMoved() {
    return moved;
}

Piece::~Piece() {}
