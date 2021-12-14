#include "PieceVisitor.h"
#include "queen.h"
#include "king.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "pawn.h"
#include "empty.h"

PieceVisitor::PieceVisitor(Board &board) : board{board} {}

PieceVisitor::~PieceVisitor() {}

