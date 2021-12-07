#include "pawn.h"

#include <utility>
#include <memory>
#include <vector>
#include <iostream>

using namespace std;

Pawn::Pawn(char color) : Piece(color) {
    type = 'p';
}

Pawn::~Pawn() {}


bool Pawn::canHop(){
    return false;
}

vector<pair<int, int>> Pawn::getValidMoves(pair<int, int> position, Board &board){
    vector<pair<int, int>> results; //stores all pawn valid moves

    // cout << "The pawn type is :" << board.getPiece(position)->getType() << endl;
    if (board.getPiece(position)->getType() != 'p' && board.getPiece(position)->getType() != 'P') {
        return results;
    }

    bool upLimit1 = false;
    bool upLimit2 = false;
    bool upLeftLimit = false;
    bool upRightLimit = false;
    int dir = getColor() == 'w' ? 1 : -1;

    if (!hasMoved()){ //if pawn hasn't moved, let the pawn move 2 up.
        auto upPos1 = make_pair(position.first, position.second + dir);
        auto upPos2 = make_pair(position.first, position.second + 2 * dir);
        auto upLeftPos = make_pair(position.first - 1, position.second + dir);
        auto upRightPos = make_pair(position.first + 1, position.second + dir);

        if (!upLimit1 && (upPos1.first < 0 || upPos1.first > 7 || upPos1.second < 0 || upPos1.second > 7)) {upLimit1 = true;} 
        if (!upLimit2 && (upPos2.first < 0 || upPos2.first > 7 || upPos2.second < 0 || upPos2.second > 7)) {upLimit2 = true;} 
        if (!upLeftLimit && (upLeftPos.first < 0 || upLeftPos.first > 7 || upLeftPos.second < 0 || upLeftPos.second > 7)) {upLeftLimit = true;}
        if (!upRightLimit && (upRightPos.first < 0 || upRightPos.first > 7 || upRightPos.second < 0 || upRightPos.second > 7)) {upRightLimit = true;}

        if (!upLimit1){
            auto up = board.getPiece(upPos1);
            if(up->getColor() == 0){ results.push_back(upPos1); } 
        }
        if (!upLimit2){
            auto up = board.getPiece(upPos2);
            if(up->getColor() == 0){ results.push_back(upPos2); }
        }

        if (!upLeftLimit){
            auto upLeft = board.getPiece(upLeftPos);
            if (upLeft->getColor() != getColor() && upLeft->getColor() != 0) { results.push_back(upLeftPos); }
            // if (upLeft->getColor() != 0) { upLeftLimit = true; }
        }

        if (!upRightLimit){
            auto upRight = board.getPiece(upRightPos);
            if (upRight->getColor() != getColor() && upRight->getColor() != 0) { results.push_back(upRightPos); }
            // if (upRight->getColor() != 0) { upRightLimit = true; }
        }

    } else {

        auto upPos = make_pair(position.first, position.second + dir);
        auto upLeftPos = make_pair(position.first - 1, position.second + dir);
        auto upRightPos = make_pair(position.first + 1, position.second + dir);

        if (!upLimit1 && (upPos.first < 0 || upPos.first > 7 || upPos.second < 0 || upPos.second > 7)) {upLimit1 = true;} 
        if (!upLeftLimit && (upLeftPos.first < 0 || upLeftPos.first > 7 || upLeftPos.second < 0 || upLeftPos.second > 7)) {upLeftLimit = true;}
        if (!upRightLimit && (upRightPos.first < 0 || upRightPos.first > 7 || upRightPos.second < 0 || upRightPos.second > 7)) {upRightLimit = true;}

        if (!upLimit1){
            auto up = board.getPiece(upPos);
            if (up->getColor() != 0){ results.push_back(upPos); } 
        }

        if (!upLeftLimit){
            auto upLeft = board.getPiece(upLeftPos);
            if (upLeft->getColor() != getColor() && upLeft->getColor() != 0) { results.push_back(upLeftPos); }
            // if (upLeft->getColor() != 0) { upLeftLimit = true; }
        }

        if (!upRightLimit){
            auto upRight = board.getPiece(upRightPos);
            if (upRight->getColor() != getColor() && upRight->getColor() != 0) { results.push_back(upRightPos); }
            // if (upRight->getColor() != 0) { upRightLimit = true; }
        }
        
   }
   return results;
}

void Pawn::accept(PieceVisitor &pv, std::pair<int, int> pos) {
    pv.visit(*this, pos);
}