#include "knight.h"

#include <utility>
#include <memory>
#include <vector>

using namespace std;

Knight::Knight(char color) : Piece{color} {
  type = 'n';
}

vector<pair<int, int>> Knight::getValidMoves(pair<int, int> position, Board &board) {
  vector<pair<int, int>> results;

  if (board.getPiece(position)->getType() != 'n' && board.getPiece(position)->getType() != 'N') {
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
    results.push_back(upLeftTopPos);
  }

  if (!upLeftBottomLimit) {
    auto upLeftBottom = board.getPiece(upLeftBottomPos);
    results.push_back(upLeftBottomPos);
  }

  if (!upRightTopLimit) {
    auto upRightTop = board.getPiece(upRightTopPos);
    results.push_back(upRightTopPos);
  }

  if (!upRightBottomLimit) {
    auto upRightBottom = board.getPiece(upRightBottomPos);
    results.push_back(upRightBottomPos);
  }

  if (!downLeftTopLimit) {
    auto downLeftTop = board.getPiece(downLeftTopPos);
    results.push_back(downLeftTopPos);
  }

  if (!downLeftBottomLimit) {
    auto downLeftBottom = board.getPiece(downLeftBottomPos);
    results.push_back(downLeftBottomPos);
  }

  if (!downRightTopLimit) {
    auto downRightTop = board.getPiece(downRightTopPos);
    results.push_back(downRightTopPos);
  }

  if (!downRightBottomLimit) {
    auto downRightBottom = board.getPiece(downRightBottomPos);
    results.push_back(downRightBottomPos); 
  }

  return results;
}

int Knight::getValue() { return 3; }

void Knight::accept(PieceVisitor &pv, std::pair<int, int> pos) {
    pv.visit(*this, pos);
}

Knight::~Knight() {}
