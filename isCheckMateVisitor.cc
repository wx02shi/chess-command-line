/* #include "isCheckmateVisitor.h"

#include "queen.h"
#include "king.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "pawn.h"
#include "empty.h"

#include <utility>

using namespace std;

void IsCheckMateVisitor::visit(Queen &queen, pair<int, int> pos) {
    auto validMoves = queen.getValidMoves(pos, board);
    for (auto position : validMoves) {
        auto potentialKing = board.getPiece(position);
        if ((potentialKing->getType() == 'k' || potentialKing->getType() == 'K') &&
            potentialKing->getColor() != queen.getColor()) {
            char inCheck = potentialKing->getColor();
            if (inCheck != 0) {
                auto kingMoves = potentialKing->getValidMoves(position, board);
                for (auto kingMove : kingMoves) {
                    // realised: have to compare to ALL positions threatened
                    // by opponent's pieces, not just this Queen
                }
            }
            break;
        }
    }
}

void IsCheckMateVisitor::visit(King &king, pair<int, int> pos) {
    auto validMoves = king.getValidMoves(pos, board);
    for (auto pos : validMoves) {
        auto potentialKing = board.getPiece(pos);
        if ((potentialKing->getType() == 'k' || potentialKing->getType() == 'K') &&
            potentialKing->getColor() != queen.getColor()) {
            inCheck = potentialKing->getColor();
            break;
        }
    }
    return;
}

void IsCheckMateVisitor::visit(Bishop &bishop, pair<int, int> pos) {
    auto validMoves = bishop.getValidMoves(pos, board);
    for (auto pos : validMoves) {
        auto potentialKing = board.getPiece(pos);
        if ((potentialKing->getType() == 'k' || potentialKing->getType() == 'K') &&
            potentialKing->getColor() != queen.getColor()) {
            inCheck = potentialKing->getColor();
            break;
        }
    }
}

void IsCheckMateVisitor::visit(Rook &rook, pair<int, int> pos) {
    auto validMoves = rook.getValidMoves(pos, board);
    for (auto pos : validMoves) {
        auto potentialKing = board.getPiece(pos);
        if ((potentialKing->getType() == 'k' || potentialKing->getType() == 'K') &&
            potentialKing->getColor() != queen.getColor()) {
            inCheck = potentialKing->getColor();
            break;
        }
    }
}

void IsCheckMateVisitor::visit(Knight &knight, pair<int, int> pos) {
    auto validMoves = knight.getValidMoves(pos, board);
    for (auto pos : validMoves) {
        auto potentialKing = board.getPiece(pos);
        if ((potentialKing->getType() == 'k' || potentialKing->getType() == 'K') &&
            potentialKing->getColor() != queen.getColor()) {
            inCheck = potentialKing->getColor();
            break;
        }
    }
}

void IsCheckMateVisitor::visit(Pawn &pawn, pair<int, int> pos) {
    auto validMoves = pawn.getValidMoves(pos, board);
    for (auto pos : validMoves) {
        auto potentialKing = board.getPiece(pos);
        if ((potentialKing->getType() == 'k' || potentialKing->getType() == 'K') &&
            potentialKing->getColor() != queen.getColor()) {
            inCheck = potentialKing->getColor();
            break;
        }
    }
    return;
}

void IsCheckMateVisitor::visit(Empty &empty, pair<int, int> pos) {
    return;
} */