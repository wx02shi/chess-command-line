#include "l3.h"
#include "board.h"

#include <utility>
#include <random>
#include <iostream>

using namespace std;

pair<pair<int, int>, pair<int, int>> L3::computerMove(char color, Board &board) {
  vector<pair<int, int>> myPieces;
  vecotr<pair<int, int>> opponentPieces;

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

  // find my highest piece that's at risk to the opponent
  int MY_HIGHEST_PIECE_VAL = 0;
  auto MY_PIECE_AT_RISK = make_pair(-1,-1);
  for (auto oppPiecePos : opponentPieces) {
    auto oppPiece = board->getPiece(oppPiecePos);
    auto oppMoves = oppPiece->getValidMoves(oppPiecePos, board);
    for (auto oppMove : oppMoves) {
      auto oppAttack = board->getPiece(oppMove);
      // oppAttack is the bot's color, so it needs to attack our color
      int oppValue = oppAttack->getValue();
      if (oppAttack->getColor() == color && oppValue > MY_HIGHEST_PIECE_VAL) { 
        MY_HIGHEST_PIECE_VAL = oppValue;
      }
    }
  }
}

L3::~L3() {}