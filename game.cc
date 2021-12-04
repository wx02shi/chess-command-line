#include <utility>
#include <memory>
#include <iostream>
#include "game.h"
#include "board.h"
#include "human.h"

using namespace std;

Game::Game() {
    board = make_shared<Board>();
}

pair<int, int> Game::translatePos(string pos) {
    int col = pos[0] - 'a';
    int row = (pos[1] - '1');
    return make_pair(col, row);
}

double Game::getFinalScore() {
    return -1;
}

void Game::whiteWins() {
    wScore++;
    reset();
}

void Game::blackWins() {
    bScore++;
    reset();
}

void Game::tie() {
    wScore += 0.5;
    bScore += 0.5;
    reset();
}

void Game::start() {
    started = true;
}

bool Game::isStarted() {
    return started;
}

void Game::reset() {
    board = make_shared<Board>();
}

void Game::render() {
    notifyObservers();
}

shared_ptr<Board> Game::getBoard() {
    return board;
}

shared_ptr<Player> Game::getWhite() {
    return white;
}

shared_ptr<Player> Game::getBlack() {
    return black;
}

void Game::setWhite(shared_ptr<Player> p) {
   
    shared_ptr<Player> temp = make_shared<Player>('w');
    
    // white = temp;
    white = make_shared<Human>('w');
    
}

void Game::setBlack(shared_ptr<Player> p) {
    black = p;
}

/* have to implement:
    bool Game::isInCheck() {}
    bool Game::isInCheckmate() {}
    bool Game::isStalemate() {}
*/

char Game::getState(int row, int col) const {
    auto thePiece = board->getPiece(make_pair(col, row));
    if (thePiece != nullptr) {
        char c = thePiece->getType();
        return c;
    }
    return 0;
}

void Game::movePiece(pair<int, int> s, pair<int, int> end) {
    start();
    return;
}

//output Score:
void Game::printResults(){
    cout << "Final Score:" << endl;    
    cout << "White: " << wScore << endl;
    cout << "Black: " << bScore << endl;
}
