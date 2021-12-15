#include "queen.h"
#include "PieceVisitor.h"

#include <utility>
#include <memory>
#include <vector>

using namespace std;

Queen::Queen(char color) : Piece{color} {
    type = 'q';
}

vector<pair<int, int>> Queen::getValidMoves(pair<int, int> position, Board &board) {
    vector<pair<int, int>> results; // Results is all the valid moves (attacks or just moves)
    
    if (board.getPiece(position)->getType() != 'q' && board.getPiece(position)->getType() != 'Q') {
        return results;
    }
    
    int index = 1;
    bool upLimit = false;
    bool downLimit = false;
    bool leftLimit = false;
    bool rightLimit = false;
    bool upLeftLimit = false;
    bool upRightLimit = false;
    bool downLeftLimit = false;
    bool downRightLimit = false;

    while (index < 8) {
        auto upPos = make_pair(position.first, position.second + index);
        auto downPos = make_pair(position.first, position.second - index);
        auto leftPos = make_pair(position.first - index, position.second);
        auto rightPos = make_pair(position.first + index, position.second);
        auto upLeftPos = make_pair(position.first - index, position.second + index);
        auto upRightPos = make_pair(position.first + index, position.second + index);
        auto downLeftPos = make_pair(position.first - index, position.second - index);
        auto downRightPos = make_pair(position.first + index, position.second - index);

        if (!upLimit && (upPos.first < 0 || upPos.first > 7 || upPos.second < 0 || upPos.second > 7)) {upLimit = true;} 
        if (!downLimit && (downPos.first < 0 || downPos.first > 7 || downPos.second < 0 || downPos.second > 7)) {downLimit = true;}
        if (!leftLimit && (leftPos.first < 0 || leftPos.first > 7 || leftPos.second < 0 || leftPos.second > 7)) {leftLimit = true;}
        if (!rightLimit && (rightPos.first < 0 || rightPos.first > 7 || rightPos.second < 0 || rightPos.second > 7)) {rightLimit = true;}
        if (!upLeftLimit && (upLeftPos.first < 0 || upLeftPos.first > 7 || upLeftPos.second < 0 || upLeftPos.second > 7)) {upLeftLimit = true;}
        if (!upRightLimit && (upRightPos.first < 0 || upRightPos.first > 7 || upRightPos.second < 0 || upRightPos.second > 7)) {upRightLimit = true;}
        if (!downLeftLimit && (downLeftPos.first < 0 || downLeftPos.first > 7 || downLeftPos.second < 0 || downLeftPos.second > 7)) {downLeftLimit = true;}
        if (!downRightLimit && (downRightPos.first < 0 || downRightPos.first > 7 || downRightPos.second < 0 || downRightPos.second > 7)) {downRightLimit = true;}

        if (!upLimit) {
            auto up = board.getPiece(upPos);
            /** Add valid move to any piece: 
             *  Board::MovePieceTo() undos any move that "eats" a piece of the same colour 
             */ 
            results.push_back(upPos);
            // Check empty space 
            if (up->getColor() != 0) { upLimit = true; }
        }

        if (!downLimit) {
            auto down = board.getPiece(downPos);
            results.push_back(downPos);
            if (down->getColor() != 0) { downLimit = true; }
        }

        if (!leftLimit) {
            auto left = board.getPiece(leftPos);
            results.push_back(leftPos); 
            if (left->getColor() != 0) { leftLimit = true; }
        }
        
        if (!rightLimit) {
            auto right = board.getPiece(rightPos);
            results.push_back(rightPos);
            if (right->getColor() != 0){ rightLimit = true; }
        }
        
        if(!upLeftLimit){
            auto upLeft = board.getPiece(upLeftPos);
            results.push_back(upLeftPos);
            if (upLeft->getColor() != 0) { upLeftLimit = true; }
        }
        
        if (!upRightLimit) {
            auto upRight = board.getPiece(upRightPos);
            results.push_back(upRightPos);
            if (upRight->getColor() != 0) { upRightLimit = true; }
        }
        
        if (!downLeftLimit) {
            auto downLeft = board.getPiece(downLeftPos); 
            results.push_back(downLeftPos);
            if (downLeft->getColor() != 0) { downLeftLimit = true; }
        }
        
        if (!downRightLimit) {
            auto downRight = board.getPiece(downRightPos);
            results.push_back(downRightPos); 
            if (downRight->getColor() != 0) { downRightLimit = true; }
        }

        index++;
    }
    
    return results;
}

int Queen::getValue() { return 9; }

void Queen::accept(PieceVisitor &pv, std::pair<int, int> pos) {
    pv.visit(*this, pos);
}

Queen::~Queen() {}
