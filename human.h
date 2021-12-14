#ifndef __HUMAN__
#define __HUMAN__

#include "player.h"
#include "board.h"

class Human : public Player {
    public:
      Human(char color);
      std::pair<std::pair<int, int>, std::pair<int, int>> autoMove(Board &board, Game &game) override;
      ~Human();
};

#endif

