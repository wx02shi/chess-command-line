#include "pawn.h"

#include <utility>
#include <memory>
#include <vector>

using namespace std;

Pawn::Pawn(char color) : Piece(color) {
    type = 'p';
}

Pawn::~Pawn() {}

vector<pair<int, int>> Pawn::getValidMoves(pair<int, int> position, Board &board){
    // stores all pawn valid moves
    vector<pair<int, int>> results; 

    if (board.getPiece(position)->getType() != 'p' && board.getPiece(position)->getType() != 'P') {
        return results;
    }

    bool upLimit1 = false;
    bool upLimit2 = false;
    bool upLeftLimit = false;
    bool upRightLimit = false;
    int dir = getColor() == 'w' ? 1 : -1;

    // if pawn hasn't moved, let the pawn move 2 up.
    if (!hasMoved()) { 
        auto upPos1 = make_pair(position.first, position.second + dir);
        auto upPos2 = make_pair(position.first, position.second + 2 * dir);
        auto upLeftPos = make_pair(position.first - 1, position.second + dir);
        auto upRightPos = make_pair(position.first + 1, position.second + dir);

        if (!upLimit1 && (upPos1.first < 0 || upPos1.first > 7 || upPos1.second < 0 || upPos1.second > 7)) { upLimit1 = true; } 
        if (!upLimit2 && (upPos2.first < 0 || upPos2.first > 7 || upPos2.second < 0 || upPos2.second > 7)) { upLimit2 = true; } 
        if (!upLeftLimit && (upLeftPos.first < 0 || upLeftPos.first > 7 || upLeftPos.second < 0 || upLeftPos.second > 7)) { upLeftLimit = true; }
        if (!upRightLimit && (upRightPos.first < 0 || upRightPos.first > 7 || upRightPos.second < 0 || upRightPos.second > 7)) { upRightLimit = true; }

        if (!upLimit1) {
            auto up = board.getPiece(upPos1);
            if (up->getColor() == 0){ results.push_back(upPos1); } 
        }
        if (!upLimit2) {
            auto up2 = board.getPiece(upPos2);
            auto up1 = board.getPiece(upPos1);
            if (up2->getColor() == 0 && up1->getType() == 0){ results.push_back(upPos2); }
        }

        if (!upLeftLimit) {
            auto upLeft = board.getPiece(upLeftPos);
            results.push_back(upLeftPos);
        }

        if (!upRightLimit) {
            auto upRight = board.getPiece(upRightPos);
            results.push_back(upRightPos); 
        }
    } else {
        auto upPos = make_pair(position.first, position.second + dir);
        auto upLeftPos = make_pair(position.first - 1, position.second + dir);
        auto upRightPos = make_pair(position.first + 1, position.second + dir);

        if (!upLimit1 && (upPos.first < 0 || upPos.first > 7 || upPos.second < 0 || upPos.second > 7)) { upLimit1 = true; } 
        if (!upLeftLimit && (upLeftPos.first < 0 || upLeftPos.first > 7 || upLeftPos.second < 0 || upLeftPos.second > 7)) { upLeftLimit = true; }
        if (!upRightLimit && (upRightPos.first < 0 || upRightPos.first > 7 || upRightPos.second < 0 || upRightPos.second > 7)) { upRightLimit = true; }

        if (!upLimit1) {
            auto up = board.getPiece(upPos);
            if (up->getColor() == 0) { results.push_back(upPos); } 
        }

        if (!upLeftLimit) {
            auto upLeft = board.getPiece(upLeftPos);
            results.push_back(upLeftPos);
        }

        if (!upRightLimit) {
            auto upRight = board.getPiece(upRightPos);
            results.push_back(upRightPos);
        }
   }

   return results;
}

int Pawn::getValue() { return 1; }

void Pawn::accept(PieceVisitor &pv, std::pair<int, int> pos) {
    pv.visit(*this, pos);
}
