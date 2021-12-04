#include "board.h"
#include "piece.h"
#include "queen.h"

#include <utility>
#include <memory>

using namespace std;


Board::Board(){
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

bool Board::isValidMove(Piece *piece, std::pair<int, int> position){
    return true;
}

void begin() {
    return;
}

void end() {
    return;
}
