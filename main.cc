#include <memory>
#include <iostream>
#include <sstream>
#include <string>

#include "board.h"
#include "game.h"
#include "human.h"

#include "queen.h"
#include "king.h"
#include "bishop.h"
#include "pawn.h"
#include "knight.h"
#include "rook.h"

#include "observer.h"
#include "textObserver.h"


using namespace std;

int main() {
    string command;
    char turn = 'w';
    shared_ptr<Game> game;

    //Game g{board}; //canvas
    vector<shared_ptr<Observer>> observers; //shared ptr?
    // shared_ptr<TextObserver> textObserver; //shared ptr?


    while (cin >> command) {
        if (command == "game") {
            auto tempGame = make_shared<Game>();
            bool invalidPlayer = false;

            string wPlayer;
            string bPlayer;
            // Probably not the most efficient way to write code...
            cin >> wPlayer;

            if (wPlayer == "human") {
                tempGame->setWhite(make_shared<Player>('w'));
            } 
            /* else if (wPlayer == "computer1") { game->getWhite() = make_shared<Computer>(1); }
            else if (wPlayer == "computer2") { game->getWhite() = make_shared<Computer>(2); }
            else if (wPlayer == "computer3") { game->getWhite() = make_shared<Computer>(3); }
            else if (wPlayer == "computer4") { game->getWhite() = make_shared<Computer>(4); }
             */else { invalidPlayer = true; }

            cin >> bPlayer;
            if (bPlayer == "human") {
                tempGame->setBlack(make_shared<Player>('b'));
            } 
            /* else if (bPlayer == "computer1") { game->getBlack() = make_shared<Computer>(1); }
            else if (bPlayer == "computer2") { game->getBlack() = make_shared<Computer>(2); }
            else if (bPlayer == "computer3") { game->getBlack() = make_shared<Computer>(3); }
            else if (bPlayer == "computer4") { game->getBlack() = make_shared<Computer>(4); }
             */else { invalidPlayer = true; }

            if (!invalidPlayer) { 
                game = tempGame;
                tempGame = nullptr;
                // display game
                observers.emplace_back(make_shared<TextObserver>(game));
                // cout << "CREATE OBSERVER GAME COUNT: " << game.use_count() << endl;
                // cout << "OBSERVERS SIZE: " << observers.size() << endl;
                game->render();
            }
            // else {
                // print error msg
                // TODO: add proper exception handling, not a boolean
            // }
        }
        else if (command == "resign") {
            if (turn == 'w') { game->blackWins(); }
            else { game->whiteWins(); }
        }
        else if (command == "move") {
            string startS;
            string endS;
            pair<int, int> start;
            pair<int, int> end;
            
            cin >> startS;
            if (startS.length() == 2) {
                start = Game::translatePos(startS);
            }

            cin >> endS;
            if (endS.length() == 2) {
                end = Game::translatePos(endS);
            }
            game->movePiece(start, end);
            game->render();

            // TODO: modify isInCheck to better suit the Observers
            game->isInCheck();
        }
        else if (command == "setup") {
            game->getBoard()->clear();
            char setupTurn = 'w';

            if (!game->isStarted()) {
                auto b = game->getBoard();
                string command2;
                while (cin >> command2) {
                    if (command2 == "done") { break; }
                    else if (command2 == "+") {
                        char piece;
                        string pos;
                        cin >> piece;
                        cin >> pos;

                        if (pos.length() == 2) {
                            switch(piece) {
                                case 'Q':
                                    b->setPiece(make_shared<Queen>(setupTurn), Game::translatePos(pos));
                                    break;
                                case 'K':
                                    b->setPiece(make_shared<King>(setupTurn), Game::translatePos(pos));
                                    break;
                            }
                            game->render();
                        }
                    }
                    else if (command2 == "-") {
                        string pos;
                        cin >> pos;
                        if (pos.length() == 2) {
                            b->setPiece(nullptr, Game::translatePos(pos));
                            game->render();
                        }
                    }
                    else if (command2 == "=") {
                        string colour;
                        cin >> colour;
                        if (colour == "white") { setupTurn = 'w'; }
                        else { setupTurn = 'b'; }
                    }
                }
            }

            /** CHECK FOR:
             * exactly one king on both colours
             * no pawns on the first or last row
             * neither king is check
             * otherwise cannot leave setup
             */
        }
        
        else if (command == "getValidMoves") {
            auto b = game->getBoard();
            auto pos = make_pair(3,7);
            auto vec = b->getPiece(pos)->getValidMoves(pos, *b.get());
            for (auto it : vec) {
                cout << it.first << ' ' << it.second << endl;
            }
        }
        
        else {
            // print error msg
        }
    }
    // cout << "TEXTOBS COUNT OUTSIDE LOOP " << observers[0].use_count() << endl;
    game->empty();
    //cout << "DISPLAY GAME COUNT OUTSIDE LOOP " << game.use_count() << endl;
    observers.erase(observers.begin(), observers.end());
    //cout << "OBSERVERS SIZE OUTSIDE: " << observers.size() << endl;
    //cout << "DISPLAY GAME COUNT AFTER OBSERVER ERASE " << game.use_count() << endl; 

    // game white-player black-player
    // can be human or computer[1-4]

    // resign

    // move start end (e.g. move e2 e4)

    // move start end piece (e.g. move e7 e8 Q)

    // setup
    // + piece pos
    // - pos
    // = colour
    // done
}
