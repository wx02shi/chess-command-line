#include "computer.h"
#include "board.h"
#include "game.h"

#include "Difficulty.h"
#include "l1.h"
#include "l2.h"

#include <utility>
#include <memory>
#include <iostream>

using namespace std;

Computer::Computer(char color, int level, shared_ptr<Difficulty> difficulty): 
  Player{color, 'c'}, level{level}, difficultyOption{difficulty} {}

void Computer::set_difficulty(shared_ptr<Difficulty> difficulty) {
  difficultyOption = difficulty;
}

pair<pair<int, int>, pair<int, int>> Computer::autoMove(Board &board, Game &game) {
  pair<pair<int, int>, pair<int, int>> rngMove;
  int tempLevel = level;

  while (true) {
    rngMove = difficultyOption->computerMove(color, board, game);
        
    // if rngMove is empty, setDifficulty() 1 level lower
    auto start = rngMove.first;
    auto end = rngMove.second;
    if (start.first == -1 && start.second == -1 && end.first == -1 && end.second == -1) {
      if (tempLevel == 3) {
        set_difficulty(make_shared<L2>());
        tempLevel--;
      } else if (tempLevel == 2) {
        set_difficulty(make_shared<L1>());
        tempLevel--;
      } else {
        break;
      }
    } else {
      break;
    }
  }
  
  // reset the bot's level back to original state
  if (level == 2) {
    set_difficulty(make_shared<L2>());
  }

  return rngMove;
}

Computer::~Computer() {}

