#include "isCheckVisitor.h"

#include "queen.h"
#include "king.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "pawn.h"
#include "empty.h"

#include <utility>

using namespace std;

IsCheckVisitor::IsCheckVisitor(Board &board) : PieceVisitor{board} {}

char IsCheckVisitor::getCheck() {
    return inCheck;
}

void IsCheckVisitor::visit(Queen &queen, pair<int, int> pos) {
    auto validMoves = queen.getValidMoves(pos, board);
    for (auto pos : validMoves) {
        auto potentialKing = board.getPiece(pos);
        if ((potentialKing->getType() == 'k' || potentialKing->getType() == 'K') &&
            potentialKing->getColor() != queen.getColor()) {
            inCheck = potentialKing->getColor();
            break;
        }
    }
}

void IsCheckVisitor::visit(King &king, pair<int, int> pos) {
    return;
}

void IsCheckVisitor::visit(Bishop &bishop, pair<int, int> pos) {
    return;
}

void IsCheckVisitor::visit(Rook &rook, pair<int, int> pos) {
    return;
}

void IsCheckVisitor::visit(Knight &knight, pair<int, int> pos) {
    return;
}

void IsCheckVisitor::visit(Pawn &pawn, pair<int, int> pos) {
    return;
}

void IsCheckVisitor::visit(Empty &empty, pair<int, int> pos) {
    return;
}
