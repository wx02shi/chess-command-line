#ifndef __PIECEVISITOR_H__
#define __PIECEVISITOR_H__

// Forward declarations
class Queen;
/*
class Pawn;
class King;
class Bishop;
class Knight;
class Rook;
*/

class PieceVisitor {
  public:
    // return type void??
    virtual void visit(Queen &queen) = 0;
    virtual ~PieceVisitor();

};

#endif