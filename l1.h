#ifndef __L1_H__
#define __L1_H__

#include "Difficulty.h"

#include <utility>

class L1 : public Difficulty {

  public:
    std::pair<std::pair<int, int>, std::pair<int, int>> computerMove(char color, Board &board, Game &game) override;
    ~L1();

};

#endif

