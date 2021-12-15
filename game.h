#ifndef __GAME_H__
#define __GAME_H__

#include <memory>
#include <utility>
#include <string>
#include "board.h"
#include "player.h"
#include "subject.h"

class Player;
class Human;

class Game: public Subject {
    std::shared_ptr<Player> white = nullptr;
    std::shared_ptr<Player> black = nullptr;
    std::shared_ptr<Board> board;
    double wScore = 0;
    double bScore = 0;
    bool started = false;
    char turn = 'w';
    char gState = 0;
    /**
     * 0: nothing
     * w: white in check
     * b: black in check
     * W: white is checkmated
     * B: black is checkmated
     * s: stalemate
     */

    public:
        Game();
        static std::pair<int, int> translatePos(std::string pos);
        void whiteWins();
        void blackWins();
        void tie();
        void reset();
        void start();
        void render();
        bool isStarted();
        std::shared_ptr<Player> getWhite();
        std::shared_ptr<Player> getBlack();
        void setWhite(std::shared_ptr<Player> p);
        void setBlack(std::shared_ptr<Player> p);
        std::shared_ptr<Board> getBoard();
        char isInCheck();
        char isInCheckmate();
        bool isStalemate();
        void updateGameState();
        char getGameState();
        char getState(int row, int col) const override;
        bool movePiece(std::pair<int, int> s, std::pair<int, int> end);
        void undo();
        void nextTurn();
        char getTurn();
        void printResults();
};

#endif
