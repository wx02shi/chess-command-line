#include "piece.h"

Piece::Piece(char color) : color{color} {}

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
    return (moved > 0);
}

void Piece::move() {
    moved++;
}

void Piece::undoMove() {
    if (moved > 0) {
        moved--;
    }
}

Piece::~Piece() {}
