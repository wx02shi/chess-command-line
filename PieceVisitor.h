#ifndef __PIECEVISITOR_H__
#define __PIECEVISITOR_H__

#include <utility>

// Forward declarations
class Queen;
class Pawn;
class King;
class Bishop;
class Knight;
class Rook;
class Empty;
class Board;

class PieceVisitor {
  protected:
    Board &board;

  public:
    PieceVisitor(Board &board);
    virtual void visit(Queen &queen, std::pair<int, int> pos) = 0;
    virtual void visit(Pawn &pawn, std::pair<int, int> pos) = 0;
    virtual void visit(King &king, std::pair<int, int> pos) = 0;
    virtual void visit(Bishop &bishop, std::pair<int, int> pos) = 0;
    virtual void visit(Knight &knight, std::pair<int, int> pos) = 0;
    virtual void visit(Rook &rook, std::pair<int, int> pos) = 0;
    virtual void visit(Empty &empty, std::pair<int, int> pos) = 0;
    virtual ~PieceVisitor();

};

#endif

