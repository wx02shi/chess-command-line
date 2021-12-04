#ifndef _PLAYER_
#define _PLAYER_

#include <memory>
#include <vector>
#include <utility>
//
class Player {
    char color;
    //std::vector<Piece*> remaining();
    
    public:
        Player(char color);
        char getColor();
        //void movePiece(std::vector<std::pair<int, int>> start, std::vector<std::pair<int, int>> end);
        ~Player();
};

#endif
