#ifndef _PLAYER_
#define _PLAYER_

#include <memory>
#include <vector>
#include <utility>

#include "board.h"

class Player {
    char type;
    protected:
    char color;
    
    //std::vector<Piece*> remaining();
    
    public:
        Player(char color, char type);
        char getColor();
        char getType();
        virtual std::pair<std::pair<int, int>, std::pair<int, int>> autoMove(Board &board) = 0;
        //void movePiece(std::vector<std::pair<int, int>> start, std::vector<std::pair<int, int>> end);
        ~Player();
};

#endif
