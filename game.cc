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
    // cout << "White Wins!" << endl;
    reset();
}

void Game::blackWins() {
    bScore++;
    // cout << "Black Wins!" << endl;
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
    turn = 'w';
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
    // white = temp;
    white = p;
    
}

void Game::setBlack(shared_ptr<Player> p) {
    black = p;
}

/**
 * 0: no state
 * w: white is in check
 * b: black is in check
 * W: white loses by checkmate
 * B: black loses by checkmate
 * s: stalemate
 */
void Game::updateGameState() {
    char isCheck = isInCheck();
    char isCheckmate = isInCheckmate();
    bool isStale = isStalemate();

    if (isCheck != 0) { gState = isCheck; }
    if (isCheckmate != 0) { gState = isCheckmate; }
    if (isStale) { gState = 's'; }
}

char Game::getGameState() {
    return gState;
}

char Game::isInCheck() {
    IsCheckVisitor checkVisitor{*board.get()};

    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            auto pos = make_pair(i,j);
            auto piece = board->getPiece(pos);
            piece->accept(checkVisitor, pos);
            gState = checkVisitor.getCheck(); 
            if (gState == turn) {
                gState = turn;
                return gState;
            }
            if (gState == 'b') {
                // cout << "Black is in check." << endl;
                gState = 'b';
            } else if (gState == 'w') {
                // cout << "White is in check." << endl;
                gState = 'w';
            }
        }
    }
    return gState;
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

    /* if (isStalemate) {
        cout << "Stalemate!" << endl; 
        tie();
    } */

    return isStalemate;
}


char Game::isInCheckmate() {
    if (gState == 'w' || gState == 'b') {
        vector<pair<int, int>> opponentThreat;
        pair<int, int> checkedKing;
        for (int i = 0; i <= 7; i++) {
            for (int j = 0; j <= 7; j++) {
                auto position = make_pair(i,j);
                auto piece = board->getPiece(position);
                if ((piece->getType() == 'k' || piece->getType() == 'K') &&
                    piece->getColor() == gState) {
                    checkedKing = position;
                } else if (piece->getType() != 0) {
                    auto validMoves = piece->getValidMoves(position, *board.get());
                    opponentThreat.insert(opponentThreat.end(), validMoves.begin(), validMoves.end());
                }
            }
        }

        auto kingMoves = board->getPiece(checkedKing)->getValidMoves(checkedKing, *board.get());
        /* for (auto km : kingMoves) {
            // cout << "KING MOVE TILE: " << km.first << ' ' << km.second << endl;
            bool threatened = true;

            auto piece = board->getPiece(km);
            if (piece->getColor() != board->getPiece(checkedKing)->getColor()) {
                for (auto threat : opponentThreat) {
                    // cout << "THREATENED TILE: " << threat.first << ' ' << threat.second << endl;
                    if (km.first != threat.first || km.second != threat.second) {
                        cout << km.first << ", " << km.second << endl;
                        cout << threat.first << ", " << threat.second << endl;
                        threatened = false;
                        break;
                    }
                }
            }
            
            if (!threatened) {
                return 0;
            }
        } */

        bool allFound = true;
        for (auto km : kingMoves) {
            auto piece = board->getPiece(km);

            if (piece->getColor() != board->getPiece(checkedKing)->getColor()) {
                bool thisFound = false;
                for (auto threat : opponentThreat) {
                    if (km == threat) {
                        thisFound = true;
                        cout << km.first << ", " << km.second << endl;
                        cout << threat.first << ", " << threat.second << endl;
                        break;
                    }
                    
                }
                if (thisFound) {
                    continue;
                } else {
                    allFound = false;
                    break;
                }
            }
        }
        /* cout << "Checkmate! ";
        if (inCheck == 'w') {
            blackWins();
        } else if (inCheck == 'b') {
            whiteWins();
        } */
        if (allFound) {
            return (gState - 32);
        } else {
            return 0;
        }
        
    }
    return 0;
}

void Game::undo() {
    board->undo();
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

bool Game::movePiece(pair<int, int> s, pair<int, int> end) {
    start();
    auto piece = board->getPiece(s);
    bool result = board->movePieceTo(piece, s, end);
    return result;
}

//output Score:
void Game::printResults(){
    cout << "Final Score:" << endl;    
    cout << "White: " << wScore << endl;
    cout << "Black: " << bScore << endl;
}

void Game::nextTurn() {
    if (turn == 'w') {
        turn = 'b';
    } else {
        turn = 'w';
    }
}

char Game::getTurn() {
    return turn;
}