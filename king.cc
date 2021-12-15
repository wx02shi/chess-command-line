#include "king.h"
#include "rook.h"
#include <utility>
#include <memory>
#include <vector>

using namespace std;

King::King(char color) : Piece{color} {
    type = 'k';
}

vector<pair<int, int>> King::getValidMoves(pair<int, int> position, Board &board) {
    // Results is all the valid moves (attacks or just moves)
    vector<pair<int, int>> results; 

    if (board.getPiece(position)->getType() != 'k' && board.getPiece(position)->getType() != 'K') {
        return results;
    }

    // regular moves
    bool upLimit = false;
    bool downLimit = false;
    bool leftLimit = false;
    bool rightLimit = false;
    bool upLeftLimit = false;
    bool upRightLimit = false;
    bool downLeftLimit = false;
    bool downRightLimit = false;
    auto upPos = make_pair(position.first, position.second + 1);
    auto downPos = make_pair(position.first, position.second - 1);
    auto leftPos = make_pair(position.first - 1, position.second);
    auto rightPos = make_pair(position.first + 1, position.second);
    auto upLeftPos = make_pair(position.first - 1, position.second + 1);
    auto upRightPos = make_pair(position.first + 1, position.second + 1);
    auto downLeftPos = make_pair(position.first - 1, position.second - 1);
    auto downRightPos = make_pair(position.first + 1, position.second - 1);
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

    if(!upLeftLimit) {
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

    // check for castle
    if (!moved) {
        // check for rooks in the corners of the same row
        auto lc = make_pair(0, position.second);
        auto rc = make_pair(7, position.second);
        auto lCastle = make_pair(2, position.second);
        auto rCastle = make_pair(6, position.second);
        auto leftCorner = board.getPiece(lc);
        auto rightCorner = board.getPiece(rc);
        bool leftBlocked = false;
        bool rightBlocked = false;
        shared_ptr<Rook> leftRook;
        shared_ptr<Rook> rightRook;

        // If the corner is a rook, check
        if (leftCorner->getType() == 'r' || leftCorner->getType() == 'R') {
            if (!leftCorner->hasMoved()) {
                int index = 1;
                while (!leftBlocked && index < position.first) {
                    auto checkBetween = board.getPiece(make_pair(position.first - index, position.second));
                    if (checkBetween->getType() != 0) {
                        leftBlocked = true;
                        break;
                    }
                    index++;
                }
                
                if (!leftBlocked) { results.push_back(lCastle); }
                /** NOTE: move() function should be able to tell that a 
                 * king attacking it's own rook is a castle move.
                 */
            }
        }
        if (rightCorner->getType() == 'r' || rightCorner->getType() == 'R' ) {
            if (!rightCorner->hasMoved()) {
                int index = 1;
                while (!rightBlocked && index < 7 - position.first) {
                    auto checkBetween = board.getPiece(make_pair(position.first + index, position.second));
                    if (checkBetween->getType() != 0) {
                        leftBlocked = true;
                        break;
                    }
                    index++;
                }

                if (!rightBlocked) { results.push_back(rCastle); }
            }
        }
    }

    return results;
}

int King::getValue() { return 10; }

void King::accept(PieceVisitor &pv, std::pair<int, int> pos) {
    pv.visit(*this, pos);
}

King::~King() {}
