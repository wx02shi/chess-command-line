#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include <random>

#include "board.h"
#include "game.h"
#include "human.h"

#include "queen.h"
#include "king.h"
#include "bishop.h"
#include "pawn.h"
#include "knight.h"
#include "rook.h"
#include "empty.h"

#include "computer.h"
#include "l1.h"
#include "l2.h"

#include "observer.h"
#include "textObserver.h"
#include "graphicsObserver.h"
#include <time.h>

using namespace std;



int main() {
    // Set seed for actually random RNG moves
    // srand(time(NULL));
    srand(2021);
    
    string command;
    shared_ptr<Game> game;

    vector<shared_ptr<Observer>> observers;

    // Bot pawn promotion
    int whitePromotableIdx = 0;
    int blackPromotableIdx = 0;
    vector<char> promotablePieces = {'Q', 'R', 'B', 'N'};


    while (cin >> command) {
        if (command == "game") {
            if (game != nullptr) {
                game->empty();
            }
            
            auto tempGame = make_shared<Game>();
            bool invalidPlayer = false;

            string wPlayer;
            string bPlayer;
            cin >> wPlayer;
            if (wPlayer == "human") {
                tempGame->setWhite(make_shared<Human>('w'));
            } 
            else if (wPlayer == "computer1") { 
                tempGame->setWhite(make_shared<Computer>('w', 1, make_shared<L1>()));
            }
            else if (wPlayer == "computer2") { 
                tempGame->setWhite(make_shared<Computer>('w', 2, make_shared<L2>())); 
            }
            else { invalidPlayer = true; }

            cin >> bPlayer;
            if (bPlayer == "human") {
                tempGame->setBlack(make_shared<Human>('b'));
            } 
            else if (bPlayer == "computer1") {
                tempGame->setBlack(make_shared<Computer>('b', 1, make_shared<L1>())); 
            }
            else if (bPlayer == "computer2") { 
                tempGame->setBlack(make_shared<Computer>('b', 2, make_shared<L2>())); 
            }
            else { invalidPlayer = true; }

            if (!invalidPlayer) { 
                game = tempGame;
                tempGame = nullptr;
                // display game
                observers.emplace_back(make_shared<TextObserver>(game));
                observers.emplace_back(make_shared<GraphicsObserver>(game));

                game->render();
            }
        }
        else if (command == "resign") {
            if (game->getTurn() == 'w') { game->blackWins(); }
            else { game->whiteWins(); }
        }
        else if (command == "move") {
            char turn = game->getTurn();
            if (turn == 'w' && game->getWhite()->getType() == 'c') {
                pair<pair<int, int>, pair<int, int>> move;
                while (true) {
                    move = game->getWhite()->autoMove(*game->getBoard().get(), *game.get());
                    if (move.first != move.second) {
                        game->movePiece(move.first, move.second);

                        // Pawn promotion
                        auto thePiece = game->getBoard()->getPiece(move.second);
                        if (thePiece->getType() == 'P'){
                            if (move.second.second == 7) {
                                if (whitePromotableIdx == 0) {
                                    game->getBoard()->setPiece(make_shared<Queen>(turn), move.second);
                                } else if (whitePromotableIdx == 1) {
                                    game->getBoard()->setPiece(make_shared<Rook>(turn), move.second);
                                } else if (whitePromotableIdx == 2) {
                                    game->getBoard()->setPiece(make_shared<Bishop>(turn), move.second);
                                } else if (whitePromotableIdx == 3) {
                                    game->getBoard()->setPiece(make_shared<Knight>(turn), move.second);
                                }

                                whitePromotableIdx++;
                            }

                            if (whitePromotableIdx == 4) {
                                whitePromotableIdx = 0;
                            }
                        } 

                        // Undo the move if the bot put itself into check
                        game->updateGameState();
                        char gState = game->getGameState();
                        
                        if (gState == turn || gState == turn - 32) {
                            game->undo();
                            cout << "Cannot move to cause a self-check." << endl;
                        } else {
                            game->render();
                            if (gState == 'W') {
                                game->blackWins();
                            } else if (gState == 'B') {
                                game->whiteWins();
                            } else if (gState == 's') {
                                game->tie();
                            }
                            game->nextTurn();
                            break;
                        }
                    }
                }
            } else if (turn == 'b' && game->getBlack()->getType() == 'c') {
                pair<pair<int, int>, pair<int, int>> move;
                while (true) {
                    move = game->getBlack()->autoMove(*game->getBoard().get(), *game.get());
                    if (move.first != move.second) {
                        game->movePiece(move.first, move.second);
                        
                        // Pawn promotion
                        auto thePiece = game->getBoard()->getPiece(move.second);
                        if (thePiece->getType() == 'p'){
                            if (move.second.second == 0) {
                                if (blackPromotableIdx == 0) {
                                    game->getBoard()->setPiece(make_shared<Queen>(turn), move.second);
                                } else if (blackPromotableIdx == 1) {
                                    game->getBoard()->setPiece(make_shared<Rook>(turn), move.second);
                                } else if (blackPromotableIdx == 2) {
                                    game->getBoard()->setPiece(make_shared<Bishop>(turn), move.second);
                                } else if (blackPromotableIdx == 3) {
                                    game->getBoard()->setPiece(make_shared<Knight>(turn), move.second);
                                }

                                blackPromotableIdx++;
                            }

                            if (blackPromotableIdx == 4) {
                                blackPromotableIdx = 0;
                            }
                        } 
    
                        // Undo the move if the bot put itself into check
                        game->updateGameState();
                        char gState = game->getGameState();
                        
                        if (gState == turn || gState == turn - 32) {
                            game->undo();
                            cout << "Cannot move to cause a self-check." << endl;
                        } else {
                            game->render();
                            if (gState == 'W') {
                                game->blackWins();
                            } else if (gState == 'B') {
                                game->whiteWins();
                            } else if (gState == 's') {
                                game->tie();
                            }
                            game->nextTurn();
                            break;
                        }
                    }
                }
            } else {
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

                auto playerPiece = game->getBoard()->getPiece(start);
                if (playerPiece->getColor() == turn) { //Move/turn guard
                    bool validMove = game->movePiece(start, end);
                    if (validMove) {
                        // You can't promote to a King, and ideally you wouldn't promote 
                        // to another pawn, it follows that there's only 4 pieces to promote
                        char toPromote;
                        auto thePiece = game->getBoard()->getPiece(end);
                        if (thePiece->getType() == 'p') {
                            if (end.second == 0) {
                                cout << "What to promote? ";
                                cin >> toPromote;
                                cout << endl;
                                if (toPromote == 'Q') {
                                    game->getBoard()->setPiece(make_shared<Queen>(turn), end);
                                } else if (toPromote == 'R') {
                                    game->getBoard()->setPiece(make_shared<Rook>(turn), end);
                                } else if (toPromote == 'B') {
                                    game->getBoard()->setPiece(make_shared<Bishop>(turn), end);
                                } else if (toPromote == 'N') {
                                    game->getBoard()->setPiece(make_shared<Knight>(turn), end);
                                }
                            }
                        } else if (thePiece->getType() == 'P'){
                            if (end.second == 7){
                                cout << "What to promote? ";
                                cin >> toPromote;
                                if (toPromote == 'Q'){
                                    game->getBoard()->setPiece(make_shared<Queen>(turn), end);
                                }
                                if (toPromote == 'R'){
                                    game->getBoard()->setPiece(make_shared<Rook>(turn), end);
                                }
                                if (toPromote == 'B'){
                                    game->getBoard()->setPiece(make_shared<Bishop>(turn), end);
                                }
                                if (toPromote == 'N'){
                                    game->getBoard()->setPiece(make_shared<Knight>(turn), end);
                                }
                            }
                        }
                        
                        game->updateGameState();
                        char gState = game->getGameState();

                        if (gState == turn || gState == turn - 32) {
                            game->undo();
                            
                            cout << "Cannot move to cause a self-check." << endl;
                        } else {
                            game->render();
                            if (gState == 'W') {
                                game->blackWins();
                            } else if (gState == 'B') {
                                game->whiteWins();
                            } else if (gState == 's') {
                                game->tie();
                            }
                            game->nextTurn();
                        }
                    } else {
                        cout << "Invalid move" << endl;
                    }
                } else {
                    cout << "Cannot move the opponent's piece" << endl;
                }
            }
        }
        else if (command == "setup") {
            game->getBoard()->clear();
            char setupTurn = 'w';

            if (!game->isStarted()) {
                auto b = game->getBoard();
                string command2;
                while (cin >> command2) {
                    if (command2 == "done") { 
                        // Check for a white king and a black king,
                        // no pawns on the first and last row
                        // neither king is in check
                        bool valid = true;
                        int wKingCount = 0, bKingCount = 0;
                        for (int i = 0; i <= 7; i++) {
                            for (int j = 0; j <= 7; j++) {
                                auto position = make_pair(i,j);
                                auto piece = b->getPiece(position);
                                if (j == 0 || j == 7) { // check for pawns on first and last row
                                    if (piece->getType() == 'p' ||
                                        piece->getType() == 'P') {
                                        if (valid) {
                                            // only print this once
                                            cout << "Invalid setup, pawns can't be placed on first and last rows" << endl;
                                        }
                                        valid = false;
                                    }
                                }

                                if (piece->getType() == 'k' ||
                                    piece->getType() == 'K' ) {
                                    if (piece->getColor() == 'w') {
                                        wKingCount++;
                                    } else {
                                        bKingCount++;
                                    }
                                }
                            }
                        }

                        if (wKingCount != 1 || bKingCount != 1) {
                            cout << "Invalid setup, missing/too many kings" << endl;
                            valid = false;
                        }

                        // Look for checks
                        game->updateGameState();
                        char gState = game->getGameState();
                        if (gState == 'w' || gState == 'b') { 
                            cout << "Invalid setup, king is in check" << endl;
                            valid = false; 
                        }

                        if (valid) { 
                            cout << "Setup completed!" << endl;
                            break; 
                        }
                    }
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
                                case 'R':
                                    b->setPiece(make_shared<Rook>(setupTurn), Game::translatePos(pos));
                                    break;
                                case 'N':
                                    b->setPiece(make_shared<Knight>(setupTurn), Game::translatePos(pos));
                                    break;
                                case 'B':
                                    b->setPiece(make_shared<Bishop>(setupTurn), Game::translatePos(pos));
                                    break;
                                case 'P':
                                    b->setPiece(make_shared<Pawn>(setupTurn), Game::translatePos(pos));
                                    break;
                            }
                            game->render();
                        }
                    }
                    else if (command2 == "-") {
                        string pos;
                        cin >> pos;
                        if (pos.length() == 2) {
                            b->setPiece(make_shared<Empty>(), Game::translatePos(pos));
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
        }
        
        else if (command == "getValidMoves") {
            auto b = game->getBoard();
            auto pos = make_pair(3,7);
            auto vec = b->getPiece(pos)->getValidMoves(pos, *b.get());
            for (auto it : vec) {
                cout << it.first << ' ' << it.second << endl;
            }
        }
    }

    game->printResults();
    game->empty();
    observers.erase(observers.begin(), observers.end());
}
