#include "rook.h"

#include <utility>
#include <memory>
#include <vector>

using namespace std;

Rook::Rook(char color) : Piece{color} {
    type = 'r';
}

vector<pair<int, int>> Rook::getValidMoves(pair<int, int> position, Board &board) {
    // Results is all the valid moves (attacks or just moves)
    vector<pair<int, int>> results; 
        
    if (board.getPiece(position)->getType() != 'r' && board.getPiece(position)->getType() != 'R') {
        return results;
    }
    
    int index = 1;
    bool upLimit = false;
    bool downLimit = false;
    bool leftLimit = false;
    bool rightLimit = false;

    while (index < 8) {
        auto upPos = make_pair(position.first, position.second + index);
        auto downPos = make_pair(position.first, position.second - index);
        auto leftPos = make_pair(position.first - index, position.second);
        auto rightPos = make_pair(position.first + index, position.second);

        if (!upLimit && (upPos.first < 0 || upPos.first > 7 || upPos.second < 0 || upPos.second > 7)) { upLimit = true; } 
        if (!downLimit && (downPos.first < 0 || downPos.first > 7 || downPos.second < 0 || downPos.second > 7)) { downLimit = true; }
        if (!leftLimit && (leftPos.first < 0 || leftPos.first > 7 || leftPos.second < 0 || leftPos.second > 7)) { leftLimit = true; }
        if (!rightLimit && (rightPos.first < 0 || rightPos.first > 7 || rightPos.second < 0 || rightPos.second > 7)) { rightLimit = true; }

        if (!upLimit) {
            auto up = board.getPiece(upPos);
            // Add valid move to an opponent piece or empty space
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

        index++;
    }
    
    return results;
}

int Rook::getValue() { return 5; }

void Rook::accept(PieceVisitor &pv, std::pair<int, int> pos) {
    pv.visit(*this, pos);
}

Rook::~Rook() {}
