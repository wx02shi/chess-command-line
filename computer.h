#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include "player.h"
#include "board.h"
#include "game.h"

#include <utility>
#include <memory>

// Forward declaration
class Difficulty;

class Computer : public Player {
    int level;

    std::shared_ptr<Difficulty> difficultyOption;

    public:
      Computer(char color, int level, std::shared_ptr<Difficulty> difficulty = nullptr);
      void set_difficulty(std::shared_ptr<Difficulty> difficulty);
      std::pair<std::pair<int, int>, std::pair<int, int>> autoMove(Board &board, Game &game) override;
      ~Computer();
};

#endif

