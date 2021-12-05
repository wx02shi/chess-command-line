#include "board.h"
#include "piece.h"
#include "empty.h"
#include "queen.h"

#include <utility>
#include <memory>

using namespace std;


Board::Board() {
    auto empty = make_shared<Empty>();
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            pieces[i][j] = empty;
        }
    }

    pieces[3][0] = make_shared<Queen>('w');
    pieces[3][7] = make_shared<Queen>('b');
}

Board::~Board() {}

// <int, int> = <col, row>
shared_ptr<Piece> Board::getPiece(std::pair<int, int> position){
    return pieces[position.first][position.second];
}


void Board::movePieceTo(Piece *piece, std::pair<int, int> position){
    // uses setPiece twice: once to place the piece in the end spot,
    // a second time to set the starting point to null.
    return;
}

void Board::setPiece(shared_ptr<Piece> piece, pair<int, int> position) {
    pieces[position.first][position.second] = piece;
}

bool Board::isValidMove(Piece &piece, std::pair<int, int> position) {
    return true;
}

/*
BoardIterator Board::begin() {
    return BoardIterator{make_shared<Board>((*this)), make_pair(0,0)};
}

BoardIterator Board::end() {
    return;
}
*/