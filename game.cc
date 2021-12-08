#include <utility>
#include <memory>
#include <iostream>
#include "game.h"
#include "board.h"
#include "human.h"

#include "isCheckVisitor.h"
#include "isStalemateVisitor.h"

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
    cout << "White Wins!" << endl;
    reset();
}

void Game::blackWins() {
    bScore++;
    cout << "Black Wins!" << endl;
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


bool Game::isInCheck() {
    /** NOTE: this can possibly be done with a BoardIterator,
     * looping and calling iterator++()
     * it would be beneficial for the other two functions as well
     */

    IsCheckVisitor checkVisitor{*board.get()};

    bool isCheck = false;
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            auto pos = make_pair(i,j);
            auto piece = board->getPiece(pos);
            piece->accept(checkVisitor, pos);
            inCheck = checkVisitor.getCheck(); 
            if (inCheck == 'b') {
                cout << "Black is in check." << endl;
                isCheck = true;
                break;
            } else if (inCheck == 'w') {
                cout << "White is in check." << endl;
                isCheck = true;
                break;
            }
        }
        if (isCheck) { break;}
    }
    
    return isCheck;
}

bool Game::isStalemate() {
    IsStalemateVisitor stalemateVisitor{*board.get()};

    bool isStalemate = true;
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            auto pos = make_pair(i,j);
            auto piece = board->getPiece(pos);
            piece->accept(stalemateVisitor, pos);
            bool stalemateResult = stalemateVisitor.getStalemate();
            // there is no "stalemate" for that piece
            // then for the player, there exists some legal move
            if (!stalemateResult) { 
                isStalemate = false;
                break;
            }
        }
        if (!isStalemate) { break; }
    }

    if (isStalemate) {
        cout << "Stalemate!" << endl; 
        tie();
        
    }
    return isStalemate;
}


bool Game::isInCheckmate() {
    if (inCheck != 0) {
        vector<pair<int, int>> opponentThreat;
        pair<int, int> checkedKing;
        for (int i = 0; i <= 7; i++) {
            for (int j = 0; j <= 7; j++) {
                auto position = make_pair(i,j);
                auto piece = board->getPiece(position);
                if ((piece->getType() == 'k' || piece->getType() == 'K') &&
                    piece->getColor() == inCheck) {
                    checkedKing = position;
                } else if (piece->getType() != 0) {
                    auto validMoves = piece->getValidMoves(position, *board.get());
                    opponentThreat.insert(opponentThreat.end(), validMoves.begin(), validMoves.end());
                }
            }
        }

        auto kingMoves = board->getPiece(checkedKing)->getValidMoves(checkedKing, *board.get());
        for (auto km : kingMoves) {
            // cout << "KING MOVE TILE: " << km.first << ' ' << km.second << endl;
            bool threatened = false;

            for (auto threat : opponentThreat) {
                //cout << "THREATENED TILE: " << threat.first << ' ' << threat.second << endl;
                if (km.first == threat.first && km.second == threat.second) {
                    threatened = true;
                    break;
                }
            }
            if (!threatened) {
                return false;
            }
        }
        cout << "Checkmate! ";
        if (inCheck == 'w') {
            blackWins();
        } else if (inCheck == 'b') {
            whiteWins();
        }
        return true;
    }
    return false;
}


char Game::getState(int row, int col) const {
    auto thePiece = board->getPiece(make_pair(col, row));
    /* if (thePiece != nullptr) {
        char c = thePiece->getType();
        return c;
    }
    return 0; */
    return thePiece->getType();
}

void Game::movePiece(pair<int, int> s, pair<int, int> end) {
    start();
    auto piece = board->getPiece(s);
    board->movePieceTo(piece, s, end);
    return;
}

//output Score:
void Game::printResults(){
    cout << "Final Score:" << endl;    
    cout << "White: " << wScore << endl;
    cout << "Black: " << bScore << endl;
}
