#include "bishop.h"

#include <utility>
#include <memory>
#include <vector>

using namespace std;

Bishop::Bishop(char color): Piece{color} {
    type = 'b';
}

vector<pair<int, int>> Bishop::getValidMoves(pair<int, int> position, Board &board) {
    vector<pair<int, int>> results;

    if (board.getPiece(position)->getType() != 'b' && board.getPiece(position)->getType() != 'B') {
        return results;
    }
    
    int index = 1;
    bool upLeftLimit = false;
    bool upRightLimit = false;
    bool downLeftLimit = false;
    bool downRightLimit = false;

    // bishop can move in any distance from 1 to 8
    while (index < 8) {
	// get respective directions
        auto upLeftPos = make_pair(position.first - index, position.second + index);
        auto upRightPos = make_pair(position.first + index, position.second + index);
        auto downLeftPos = make_pair(position.first - index, position.second - index);
        auto downRightPos = make_pair(position.first + index, position.second - index);

	// check to see if move still within board boundaries
        if (!upLeftLimit && (upLeftPos.first < 0 || upLeftPos.first > 7 || upLeftPos.second < 0 || upLeftPos.second > 7)) {upLeftLimit = true;}
        if (!upRightLimit && (upRightPos.first < 0 || upRightPos.first > 7 || upRightPos.second < 0 || upRightPos.second > 7)) {upRightLimit = true;}
        if (!downLeftLimit && (downLeftPos.first < 0 || downLeftPos.first > 7 || downLeftPos.second < 0 || downLeftPos.second > 7)) {downLeftLimit = true;}
        if (!downRightLimit && (downRightPos.first < 0 || downRightPos.first > 7 || downRightPos.second < 0 || downRightPos.second > 7)) {downRightLimit = true;}
        
        if (!upLeftLimit){
	    // position within the boundaries, add this as a valid potential move
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

int Bishop::getValue() { return 3; }

void Bishop::accept(PieceVisitor &pv, std::pair<int, int> pos) {
    pv.visit(*this, pos);
}

Bishop::~Bishop() {}
