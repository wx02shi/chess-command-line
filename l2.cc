#include "l2.h"
#include "board.h"
#include "game.h"

#include <utility>
#include <vector>
#include <iostream>

using namespace std;

pair<pair<int, int>, pair<int, int>> L2::computerMove(char color, Board &board, Game &game) {
  // Find the pieces which belong to this computer
  int BEST_MOVE_INDEX = -1;
  vector<pair<int, int>> myPieces;
  for (int i = 0; i <= 7; i++) {
    for (int j = 0; j <= 7; j++) {
      auto position = make_pair(i,j);
      if (board.getPiece(position)->getColor() == color) {
        myPieces.push_back(position);
      }
    }
  }

  // find all valid moves of all my pieces
  vector<pair<pair<int, int>, pair<int, int>>> allPiecesMoves;
  for (auto piecePos : myPieces) {
    auto thePiece = board.getPiece(piecePos);
    // Generate all moves by that piece
    auto pieceMoves = thePiece->getValidMoves(piecePos, board);
    for (auto pieceMove : pieceMoves) {
      if ((thePiece->getType() == 'p' || thePiece->getType() == 'P') &&
            (piecePos.first != pieceMove.first) &&
            (board.getPiece(pieceMove)->getColor() == color || 
            board.getPiece(pieceMove)->getColor() == 0)) {
              // ignore cases where pawns move diagonally without capturing an opponent piece
      } else if (board.getPiece(pieceMove)->getColor() != color) {
        allPiecesMoves.push_back(make_pair(piecePos, pieceMove));
      }
    }
  }

  pair<pair<int, int>, pair<int, int>> BEST_MOVE = make_pair(make_pair(-1, -1), make_pair(-1, -1));

  while (true) {
    BEST_MOVE = make_pair(make_pair(-1, -1), make_pair(-1, -1));
    BEST_MOVE_INDEX = -1;
    int HIGHEST_VALUE_TO_CAPTURE = 0;
    
    // compute the best piece to capture
    if (allPiecesMoves.size() > 0) {
      for (int i = 0; i < allPiecesMoves.size(); i++) {
        auto pieceMove = allPiecesMoves[i];
        auto thePiece = board.getPiece(pieceMove.second);
        if (thePiece->getColor() != color) {
          int pieceValue = thePiece->getValue();
          if (pieceValue > HIGHEST_VALUE_TO_CAPTURE) {
            HIGHEST_VALUE_TO_CAPTURE = pieceValue;
            BEST_MOVE = pieceMove;
            BEST_MOVE_INDEX = i;
          }
        }
      }
    } else {
      return make_pair(make_pair(-1, -1), make_pair(-1, -1));
    }
    
    // find potential check
    pair<pair<int, int>, pair<int, int>> CHECK_A_KING;
    int CHECK_A_KING_INDEX = -1;
    int CHECK_VALUE = 0;
    vector<pair<pair<pair<int, int>, pair<int, int>>, pair<int, int>>> potentialChecks;
    
    for (int i = 0; i < allPiecesMoves.size(); i++) {
      auto pieceMove = allPiecesMoves[i];
      // find the next moves
      auto piece = board.getPiece(pieceMove.first);
      // temporarily move the piece to the position
      board.movePieceTo(piece, pieceMove.first, pieceMove.second);
      auto nextMoves = piece->getValidMoves(pieceMove.second, board);
      for (auto nextMove : nextMoves) {
        auto potentialKing = board.getPiece(nextMove);
        if ((potentialKing->getType() == 'k' || potentialKing->getType() == 'K') &&
          potentialKing->getColor() != color) {
          CHECK_VALUE = 10;
          BEST_MOVE = pieceMove;
          BEST_MOVE_INDEX = i;
        }
      }
      board.undo();
    }
    
    

    /** In the while loop, we can only REMOVE items from allPiecesMoves.
     * Even after one iteration, if we don't find a move where we can
     * eat a piece or check the opposing king, then
     * this fact will still be true after every loop iteration.
     * Thus we should just immediately exit the loop and return 
     * the (-1,-1),(-1,-1) case. 
     * Note: doing this will make the computer do a Level 1 move later.
     */
    if (BEST_MOVE.first.first != -1) {
      auto thePiece = board.getPiece(BEST_MOVE.first);
      if (thePiece->getType() != 'k' && thePiece->getType() != 'K') {
        board.movePieceTo(thePiece, BEST_MOVE.first, BEST_MOVE.second);
        game.updateGameState();
        char gState = game.getGameState();
        if (gState == color || gState == color - 32) {
          allPiecesMoves.erase(allPiecesMoves.begin() + BEST_MOVE_INDEX);
        } else {
          board.undo();
          break;
        }
        board.undo();
      } else {
        allPiecesMoves.erase(allPiecesMoves.begin() + BEST_MOVE_INDEX);
      }
    } else {
      return make_pair(make_pair(-1, -1), make_pair(-1, -1));
    }
    
  }
  
  return allPiecesMoves[BEST_MOVE_INDEX];
}

L2::~L2() {}
