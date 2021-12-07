#include "knight.h"

#include <utility>
#include <memory>
#include <vector>
#include <iostream>

using namespace std;

Knight::Knight(char color) : Piece{color} {
  type = 'n';
}

bool Knight::canHop() {
  return true;
}

vector<pair<int, int>> Knight::getValidMoves(pair<int, int> position, Board &board) {
  vector<pair<int, int>> results;

  cout << "KNIGHT PIECE TYPE: " << board.getPiece(position)->getType()  << endl;
  if (board.getPiece(position)->getType() != 'n' && board.getPiece(position)->getType() != 'N') {
    cout << "LOL XD" << endl;
    return results;
  }

  bool upLeftTopLimit = false;
  bool upLeftBottomLimit = false;
  bool upRightTopLimit = false;
  bool upRightBottomLimit = false;
  bool downLeftTopLimit = false;
  bool downLeftBottomLimit = false;
  bool downRightTopLimit = false;
  bool downRightBottomLimit = false;

  auto upLeftTopPos = make_pair(position.first - 1, position.second + 2);
  auto upLeftBottomPos = make_pair(position.first - 2, position.second + 1);
  auto upRightTopPos = make_pair(position.first + 1, position.second + 2);
  auto upRightBottomPos = make_pair(position.first + 2, position.second + 1);
  auto downLeftTopPos = make_pair(position.first - 2, position.second - 1);
  auto downLeftBottomPos = make_pair(position.first - 1, position.second - 2);
  auto downRightTopPos = make_pair(position.first + 2, position.second - 1);
  auto downRightBottomPos = make_pair(position.first + 1, position.second - 2);

  if (!upLeftTopLimit && (upLeftTopPos.first < 0 || upLeftTopPos.first > 7 || upLeftTopPos.second < 0 || upLeftTopPos.second > 7)) { upLeftTopLimit = true; }
  if (!upLeftBottomLimit && (upLeftBottomPos.first < 0 || upLeftBottomPos.first > 7 || upLeftBottomPos.second < 0 || upLeftBottomPos.second > 7)) { upLeftBottomLimit = true; }
  if (!upRightTopLimit && (upRightTopPos.first < 0 || upRightTopPos.first > 7 || upRightTopPos.second < 0 || upRightTopPos.second > 7)) { upRightTopLimit = true; }
  if (!upRightBottomLimit && (upRightBottomPos.first < 0 || upRightBottomPos.first > 7 || upRightBottomPos.second < 0 || upRightBottomPos.second > 7)) { upRightBottomLimit = true; }
  if (!downLeftTopLimit && (downLeftTopPos.first < 0 || downLeftTopPos.first > 7 || downLeftTopPos.second < 0 || downLeftTopPos.second > 7)) { downLeftTopLimit = true; }
  if (!downLeftBottomLimit && (downLeftBottomPos.first < 0 || downLeftBottomPos.first > 7 || downLeftBottomPos.second < 0 || downLeftBottomPos.second > 7)) { downLeftBottomLimit = true; }
  if (!downRightTopLimit && (downRightTopPos.first < 0 || downRightTopPos.first > 7 || downRightTopPos.second < 0 || downRightTopPos.second > 7)) { downRightTopLimit = true; }
  if (!downRightBottomLimit && (downRightBottomPos.first < 0 || downRightBottomPos.first > 7 || downRightBottomPos.second < 0 || downRightBottomPos.second > 7)) { downRightBottomLimit = true; }

  if (!upLeftTopLimit) {
    auto upLeftTop = board.getPiece(upLeftTopPos);
    cout << "UPLEFTTOPLIMIT" << endl;
    if (upLeftTop->getColor() != getColor()) { results.push_back(upLeftTopPos); }
    // if (upLeftTop->getColor() != 0) { upLeftTopLimit = true; }
  }

  if (!upLeftBottomLimit) {
    auto upLeftBottom = board.getPiece(upLeftBottomPos);
    if (upLeftBottom->getColor() != getColor()) { results.push_back(upLeftBottomPos); }
    // if (upLeftBottom->getColor() != 0) { upLeftBottomLimit = true; }
  }

  if (!upRightTopLimit) {
    auto upRightTop = board.getPiece(upRightTopPos);
    if (upRightTop->getColor() != getColor()) { results.push_back(upRightTopPos); }
    // if (upRightTop->getColor() != 0) { upRightTopLimit = true; }
  }

  if (!upRightBottomLimit) {
    auto upRightBottom = board.getPiece(upRightBottomPos);
    if (upRightBottom->getColor() != getColor()) { results.push_back(upRightBottomPos); }
    // if (upRightBottom->getColor() != 0) { upRightBottomLimit = true; }
  }

  if (!downLeftTopLimit) {
    auto downLeftTop = board.getPiece(downLeftTopPos);
    if (downLeftTop->getColor() != getColor()) { results.push_back(downLeftTopPos); }
    // if (downLeftTop->getColor() != 0) { downLeftTopLimit = true; }
  }

  if (!downLeftBottomLimit) {
    auto downLeftBottom = board.getPiece(downLeftBottomPos);
    if (downLeftBottom->getColor() != getColor()) { results.push_back(downLeftBottomPos); }
    // if (downLeftBottom->getColor() != 0) { downLeftBottomLimit = true; }
  }

  if (!downRightTopLimit) {
    auto downRightTop = board.getPiece(downRightTopPos);
    if (downRightTop->getColor() != getColor()) { results.push_back(downRightTopPos); }
    // if (downRightTop->getColor() != 0) { downRightTopLimit = true; }
  }

  if (!downRightBottomLimit) {
    auto downRightBottom = board.getPiece(downRightBottomPos);
    if (downRightBottom->getColor() != getColor()) { results.push_back(downRightBottomPos); }
    // if (downRightBottom->getColor() != 0) { downRightBottomLimit = true; }
  }

  return results;
}

void Knight::accept(PieceVisitor &pv, std::pair<int, int> pos) {
    pv.visit(*this, pos);
}

Knight::~Knight() {}