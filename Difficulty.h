#ifndef __DIFFICULTY_H__
#define __DIFFICULTY_H__

#include <utility>
#include <memory>

#include "board.h"

class Difficulty {

  public: 
    virtual ~Difficulty() {}
    // maybe board needs shared_ptr?
    virtual std::pair<std::pair<int, int>, std::pair<int, int>> computerMove(char color, Board &board) = 0;

};

#endif