#include "l2.h"
#include "board.h"
#include "game.h"

#include <utility>
#include <vector>
#include <iostream>

using namespace std;

pair<pair<int, int>, pair<int, int>> L2::computerMove(char color, Board &board, Game &game) {
  vector<pair<int, int>> myPieces;

  // find all pieces which belong to this bot
  for (int i = 0; i <= 7; i++) {
    for (int j = 0; j <= 7; j++) {
      auto position = make_pair(i,j);
      if (board.getPiece(position)->getColor() == color) {
        myPieces.push_back(position);
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
  auto PIECE_USED_TO_CHECK = make_pair(-1,-1);
  auto CAN_CHECK_KING = make_pair(-1,-1);
  int CHECK_VALUE = 0;

  vector<pair<pair<int, int>, pair<pair<int, int>, vector<pair<int, int>>>>> potentialChecks;
  // <start, vector<end, potentialKing>>
  for (auto firstMove : allPiecesMoves) {
    auto piece = board.getPiece(firstMove.first);
    
    // vector<pair<int, int>>
    auto pieceMoves = piece->getValidMoves(firstMove.first, board);

    for (auto predictCheck : pieceMoves) {
      // temporarily move the piece to the position
      board.movePieceTo(piece, firstMove.first, predictCheck);
      auto predictPiece = board.getPiece(predictCheck);
      
      // vector<pair<int, int>>
      auto predictValidMoves = predictPiece->getValidMoves(predictCheck, board);
      potentialChecks.push_back(make_pair( firstMove.first, make_pair(predictCheck, predictValidMoves)));
      board.undo();
    }
  }
  
  // o
  for (auto piecePos : myPieces) {
    auto piece = board.getPiece(piecePos);
    
    // vector<pair<int, int>>
    auto pieceMoves = piece->getValidMoves(piecePos, board);

    for (auto predictCheck : pieceMoves) {
      // temporarily move the piece to the position
      board.movePieceTo(piece, piecePos, predictCheck);
      auto predictPiece = board.getPiece(predictCheck);
      
      // vector<pair<int, int>>
      auto predictValidMoves = predictPiece->getValidMoves(predictCheck, board);
      potentialChecks.push_back(make_pair( piecePos, make_pair(predictCheck, predictValidMoves)));
      board.undo();
    }
  } 
  
  if (potentialChecks.size() > 0) {
    for (auto startMove : potentialChecks) {
      for (auto nextMove : startMove.second.second) {
        auto potentialKing = board.getPiece(nextMove);
        if ((potentialKing->getType() == 'k' || potentialKing->getType() == 'K') &&
            potentialKing->getColor() != color) {
            CHECK_VALUE = 10;
            PIECE_USED_TO_CHECK = startMove.first;
            CAN_CHECK_KING = startMove.second.first;
        }
      }
    }
  }
  
  // if there's a check available, we would want to check over capturing
  if (CHECK_VALUE > HIGHEST_VALUE_TO_CAPTURE) {  
    return make_pair(PIECE_USED_TO_CHECK, CAN_CHECK_KING);
  }  

  return make_pair(HIGHEST_PIECE_TO_MOVE, HIGHEST_PIECE_TO_CAPTURE);
}

L2::~L2() {}




    /* for (auto pieceMove : allPiecesMoves) {
      // find the next moves
      auto piece = board.getPiece(pieceMove.first);
      // temporarily move the piece to the position
      board.movePieceTo(piece, pieceMove.first, pieceMove.second);
      auto nextMoves = piece->getValidMoves(pieceMove.second, board);
      for (auto nextMove : nextMoves) {
        potentialChecks.push_back(make_pair(pieceMove, nextMove));
      }
      board.undo();
    }
    
    // find the next move that targets the opposite king
    for (auto potentialCheck : potentialChecks) {
      auto potentialKing = board.getPiece(potentialCheck.second);
      if ((potentialKing->getType() == 'k' || potentialKing->getType() == 'K') &&
          potentialKing->getColor() != color) {
        CHECK_VALUE = 10;
        BEST_MOVE = potentialCheck.first;
        BEST_MOVE_INDEX = 
      }
    } */

    /* if (CHECK_VALUE > HIGHEST_VALUE_TO_CAPTURE) {
      return CHECK_A_KING;
    } else {
      return 
    } */