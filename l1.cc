#include "l1.h"
#include "board.h"
#include "game.h"

#include <utility>
#include <random>
#include <iostream>

using namespace std;

pair<pair<int, int>, pair<int, int>> L1::computerMove(char color, Board &board, Game &game) {    
    // find all pieces which belong to this bot
    vector<pair<int, int>> myPieces;
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            auto position = make_pair(i,j);
            if (board.getPiece(position)->getColor() == color) {
                myPieces.push_back(position);
            }
        }
    }

    vector<pair<pair<int, int>, pair<int, int>>> allValidMoves;
    pair<int, int> startingPos;
    int move;

    for (auto myPiece : myPieces) {
        auto piece = board.getPiece(myPiece);
        auto validMoves = piece->getValidMoves(myPiece, board);
        for (auto it: validMoves) {
            if (board.getPiece(it)->getColor() != color) {
                allValidMoves.push_back(make_pair(myPiece, it));
            }
        }
    }

    if (allValidMoves.size() == 0) {
        return make_pair(startingPos, startingPos);
    }

    while (true) {
        int rngMove = rand() % ( allValidMoves.size() - 0 );
        auto potentialMove = allValidMoves[rngMove];
        auto pieceToMove = board.getPiece(potentialMove.first);
        auto potentialCapture = board.getPiece(potentialMove.second);
        board.movePieceTo(board.getPiece(potentialMove.first), potentialMove.first, potentialMove.second);
        game.updateGameState();

        char gState = game.getGameState();
        if (gState == color || gState == color - 32) {
            // ignore cases where moving causes a self-check
            allValidMoves.erase(allValidMoves.begin() + rngMove);
            
        } else if ((pieceToMove->getType() == 'p' || pieceToMove->getType() == 'P') &&
                    potentialMove.first.first != potentialMove.second.first && 
                    (potentialCapture->getColor() == 0 || potentialCapture->getColor() == color)) {
            /** Ignore cases where pawns move diagonally without capturing an opponent piece */
            allValidMoves.erase(allValidMoves.begin() + rngMove);
        } else {
            move = rngMove;
            board.undo();
            break;
        }
        board.undo();
    }

    return allValidMoves[move];
}

L1::~L1() {}
