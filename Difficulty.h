#ifndef __DIFFICULTY_H__
#define __DIFFICULTY_H__

#include <utility>
#include <memory>

#include "board.h"
#include "game.h"

// Strategy
class Difficulty {

  public: 
    virtual ~Difficulty() {}
    virtual std::pair<std::pair<int, int>, std::pair<int, int>> computerMove(char color, Board &board, Game &game) = 0;

};

#endif

