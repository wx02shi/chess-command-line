#include "boardIterator.h"

BoardIterator::BoardIterator(shared_ptr<Board> board) : board{board} {
    auto position = make_pair(0,0);
    while (board->getPiece(position) == nullptr) {
        position.first++;
        if (position.first > 7) {
            pos.first = 0;
            position.second++;
        }
        if (position.second > 7) {
            piece = nullptr;
            break;
        }
    }
    piece = board->getPiece(position);
}

shared_ptr<Piece> BoardIterator::&operator*() {
    return board->getPiece(position);
}

bool BoardIterator::operator!=(const shared_ptr<BoardIterator> other) {
    return (this->position != other->position);
}

BoardIterator &BoardIterator::operator++(){
    while (board->getPiece(position)->getType() == 0) {
        position.first++;
        if (position.first > 7) {
            pos.first = 0;
            position.second++;
        }
        if (position.second > 7) {
            piece = nullptr;
            return *this;
        }
    }
    
    piece = board->getPiece(position);
    return *this;
}