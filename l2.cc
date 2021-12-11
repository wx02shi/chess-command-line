#include "l2.h"

#include <utility>
#include <vector>
#include <iostream>

#include "isCheckVisitor.h"

using namespace std;

pair<pair<int, int>, pair<int, int>> L2::computerMove(char color, Board &board){
  vector<pair<int, int>> myPieces;
  vector<pair<int, int>> opponentPieces;

  // find all pieces which belong to this bot
  for (int i = 0; i <= 7; i++) {
    for (int j = 0; j <= 7; j++) {
      auto position = make_pair(i,j);
      if (board.getPiece(position)->getColor() == color) {
        myPieces.push_back(position);
      } else if (board.getPiece(position)->getColor() != 0) {
        // this is the opposite color piece that's NOT empty
        opponentPieces.push_back(position);
      }
    }
  }
  
  // find all valid moves of all my pieces
  vector<pair<pair<int, int>, vector<pair<int, int>>>> allPiecesMoves;
  for (auto piecePos : myPieces) {
    auto thePiece = board.getPiece(piecePos);
    // Generate all moves by that piece
    auto pieceMoves = thePiece->getValidMoves(piecePos, board);
    allPiecesMoves.push_back(make_pair(piecePos, pieceMoves));
  }

  // computes best piece to capture
  int HIGHEST_VALUE_TO_CAPTURE = 0;
  auto HIGHEST_PIECE_TO_CAPTURE = make_pair(-1,-1);
  auto HIGHEST_PIECE_TO_MOVE = make_pair(-1,-1);
  for (auto pieceMoves : allPiecesMoves) {
    for (auto move : pieceMoves.second) {
      auto thePiece = board.getPiece(move);
      if (thePiece->getColor() != color) {
        int pieceValue = thePiece->getValue();
        if (pieceValue > HIGHEST_VALUE_TO_CAPTURE) {
          HIGHEST_VALUE_TO_CAPTURE = pieceValue;
          HIGHEST_PIECE_TO_CAPTURE = make_pair(move.first, move.second);
          HIGHEST_PIECE_TO_MOVE = pieceMoves.first;
        }
      }
    }
  }

  cout << "HIGHEST VALUE: " << HIGHEST_VALUE_TO_CAPTURE << endl;

  // find check
  IsCheckVisitor checkVisitor{board};
  auto PIECE_USED_TO_CHECK = make_pair(-1,-1);
  auto OPPONENT_KING_PIECE = make_pair(-1,-1);
  int CHECK_VALUE = 0;
  for (auto piecePos : myPieces) {
    auto piece = board.getPiece(piecePos);
    piece->accept(checkVisitor, piecePos);
    char gState = checkVisitor.getCheck();
    if (gState != color && gState != 0) {
      PIECE_USED_TO_CHECK = piecePos;
      CHECK_VALUE = 10;
    }
  }

  // cout << "CHECK VALUE: " << CHECK_VALUE << endl;

  // if we can do a check, go find the opponent's king
  if (CHECK_VALUE == 10) {
    for (auto oppPiecePos : opponentPieces) {
      auto thePiece = board.getPiece(oppPiecePos);
      char type = thePiece->getType();
      if (type == 'K' || type == 'k') {
        OPPONENT_KING_PIECE = oppPiecePos;
      }
    }
  } 

  // if there's a check available, we would
  // want to check over capturing, since we assign
  // king a value of 10, it's the highest of all pieces
  if (CHECK_VALUE > HIGHEST_VALUE_TO_CAPTURE) {  
    return make_pair(PIECE_USED_TO_CHECK, OPPONENT_KING_PIECE);
  }  

  return make_pair(HIGHEST_PIECE_TO_MOVE, HIGHEST_PIECE_TO_CAPTURE);
}

L2::~L2() {}