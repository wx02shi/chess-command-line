#ifndef __L2_H__
#define __L2_H__

#include "Difficulty.h"

#include <utility>

class L2 : public Difficulty {

  public:
    std::pair<std::pair<int, int>, std::pair<int, int>> computerMove(char color, Board &board, Game &game) override;
    ~L2();
};

#endif

