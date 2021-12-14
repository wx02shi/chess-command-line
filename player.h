#ifndef _PLAYER_
#define _PLAYER_

#include <memory>
#include <vector>
#include <utility>

#include "board.h"
#include "game.h"

// Forward Declaration
class Game;

class Player {
    char type;

    protected:
    	char color;
    
    public:
        Player(char color, char type);
        char getColor();
        char getType();
        virtual std::pair<std::pair<int, int>, std::pair<int, int>> autoMove(Board &board, Game &game) = 0;
        ~Player();
};

#endif

