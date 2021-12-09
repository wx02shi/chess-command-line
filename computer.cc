#include "computer.h"
#include "board.h"

#include "Difficulty.h"

#include <utility>
#include <memory>

using namespace std;

Computer::Computer(char color, int level, shared_ptr<Difficulty> difficulty): 
  Player{color, 'c'}, level{level}, difficultyOption{difficulty} {}

void Computer::set_difficulty(shared_ptr<Difficulty> difficulty) {
  difficultyOption = difficulty;
}

pair<pair<int, int>, pair<int, int>> Computer::autoMove(Board &board) {
  auto rngMove = difficultyOption->computerMove(color, board);
  return rngMove;
}

Computer::~Computer() {}
