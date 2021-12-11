#include "l1.h"
#include "board.h"

#include <utility>
#include <random>
#include <iostream>

using namespace std;

pair<pair<int, int>, pair<int, int>> L1::computerMove(char color, Board &board) {
    // find all pieces which belong to this bot
    vector<pair<int, int>> myPieces;
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            auto position = make_pair(i,j);
            // cout << "POSITION: " << board.getPiece(position)->getColor() << endl;
            if (board.getPiece(position)->getColor() == color) {
                myPieces.push_back(position);
            }
        }
    }

    // finds range between 0 to 15, maybe instead, it's 1 to size of myPieces
    // test to ensure the range is correct
    int rngPiece = rand() % (myPieces.size() - 0);

    // choose a random valid move for this piece to make
    auto startingPos = myPieces[rngPiece];
    auto piece = board.getPiece(startingPos);
    auto validMoves = piece->getValidMoves(startingPos, board);
    vector<pair<int, int>> moves;
    for (auto it: validMoves) {
        if (board.getPiece(it)->getColor() != color) {
            moves.push_back(it);
        }
    }
    if (moves.size() == 0) {
        return make_pair(startingPos, startingPos);
    }

    // cout << "PIECE: " << piece->getType() << " MOVE SIZE: " << moves.size() << endl;

    
    int rngMove = rand() % ( moves.size() - 0 );

    return make_pair(startingPos, moves[rngMove]);
}

L1::~L1() {}