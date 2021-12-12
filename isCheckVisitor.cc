#include "isCheckVisitor.h"

#include "queen.h"
#include "king.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "pawn.h"
#include "empty.h"

#include <utility>
#include <iostream>

using namespace std;

IsCheckVisitor::IsCheckVisitor(Board &board) : PieceVisitor{board} {}

char IsCheckVisitor::getCheck() {
    return inCheck;
}

void IsCheckVisitor::visit(Queen &queen, pair<int, int> pos) {
    auto validMoves = queen.getValidMoves(pos, board);
    for (auto position : validMoves) {
        auto potentialKing = board.getPiece(position);
        if ((potentialKing->getType() == 'k' || potentialKing->getType() == 'K') &&
            potentialKing->getColor() != queen.getColor()) {
            inCheck = potentialKing->getColor();
            break;
        }
    }
}

void IsCheckVisitor::visit(King &king, pair<int, int> pos) {
    auto validMoves = king.getValidMoves(pos, board);
    for (auto position : validMoves) {
        auto potentialKing = board.getPiece(position);
        if ((potentialKing->getType() == 'k' || potentialKing->getType() == 'K') &&
            potentialKing->getColor() != king.getColor()) {
            inCheck = potentialKing->getColor();
            break;
        }
    }
    return;
}

void IsCheckVisitor::visit(Bishop &bishop, pair<int, int> pos) {
    auto validMoves = bishop.getValidMoves(pos, board);
    for (auto position : validMoves) {
        auto potentialKing = board.getPiece(position);
        if ((potentialKing->getType() == 'k' || potentialKing->getType() == 'K') &&
            potentialKing->getColor() != bishop.getColor()) {
            inCheck = potentialKing->getColor();
            break;
        }
    }
}

void IsCheckVisitor::visit(Rook &rook, pair<int, int> pos) {
    auto validMoves = rook.getValidMoves(pos, board);
    for (auto position : validMoves) {
        auto potentialKing = board.getPiece(position);
        if ((potentialKing->getType() == 'k' || potentialKing->getType() == 'K') &&
            potentialKing->getColor() != rook.getColor()) {
            inCheck = potentialKing->getColor();
            break;
        }
    }
}

void IsCheckVisitor::visit(Knight &knight, pair<int, int> pos) {
    auto validMoves = knight.getValidMoves(pos, board);
    for (auto position : validMoves) {
        auto potentialKing = board.getPiece(position);
        if ((potentialKing->getType() == 'k' || potentialKing->getType() == 'K') &&
            potentialKing->getColor() != knight.getColor()) {
            inCheck = potentialKing->getColor();
            break;
        }
    }
}

void IsCheckVisitor::visit(Pawn &pawn, pair<int, int> pos) {
    auto validMoves = pawn.getValidMoves(pos, board);
    for (auto position : validMoves) {
        auto potentialKing = board.getPiece(position);
        if ((potentialKing->getType() == 'k' || potentialKing->getType() == 'K') &&
            potentialKing->getColor() != pawn.getColor()) {
            inCheck = potentialKing->getColor();
            break;
        }
    }
    return;
}

void IsCheckVisitor::visit(Empty &empty, pair<int, int> pos) {
    return;
}
