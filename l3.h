#ifndef __L3_H__
#define __L3_H__

#include "Difficulty.h"

#include <utility>

class L3 : public Difficulty {

  public:
    std::pair<std::pair<int, int>, std::pair<int, int>> computerMove(char color, Board &board) override;
    ~L3();
};

#endif