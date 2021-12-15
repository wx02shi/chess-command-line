#include "isStalemateVisitor.h"

#include "queen.h"
#include "king.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "pawn.h"
#include "empty.h"

#include <utility>

using namespace std;

IsStalemateVisitor::IsStalemateVisitor(Board &board) : PieceVisitor{board} {}

bool IsStalemateVisitor::getStalemate() {
    return isPieceInStalemate;
}

void IsStalemateVisitor::visit(Queen &queen, pair<int, int> pos) {
    auto validMoves = queen.getValidMoves(pos, board);
    // if validMoves is NOT empty, then there exists a move
    if (validMoves.size() != 0) {
        // by that logic, that particular piece makes the player have SOME legal move 
        isPieceInStalemate = false;
    } 
    return;
}

void IsStalemateVisitor::visit(King &king, pair<int, int> pos) {
    auto validMoves = king.getValidMoves(pos, board);
    if (validMoves.size() != 0) {
        isPieceInStalemate = false;
    } 
    return;
}

void IsStalemateVisitor::visit(Bishop &bishop, pair<int, int> pos) {
    auto validMoves = bishop.getValidMoves(pos, board);
    if (validMoves.size() != 0) {
        isPieceInStalemate = false;
    } 
    return;
}

void IsStalemateVisitor::visit(Rook &rook, pair<int, int> pos) {
    auto validMoves = rook.getValidMoves(pos, board);
    if (validMoves.size() != 0) {
        isPieceInStalemate = false;
    } 
    return;
}

void IsStalemateVisitor::visit(Knight &knight, pair<int, int> pos) {
    auto validMoves = knight.getValidMoves(pos, board);
    if (validMoves.size() != 0) {
        isPieceInStalemate = false;
    } 
    return;
}

void IsStalemateVisitor::visit(Pawn &pawn, pair<int, int> pos) {
    auto validMoves = pawn.getValidMoves(pos, board);
    if (validMoves.size() != 0) {
        isPieceInStalemate = false;
    } 
    return;
}

void IsStalemateVisitor::visit(Empty &empty, pair<int, int> pos) {
    return;
}
