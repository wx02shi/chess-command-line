#include <iostream>
#include <memory>

#include "textObserver.h"

using namespace std;

TextObserver::TextObserver(shared_ptr<Game> g) : subject{g} {
    subject->attach(make_shared<TextObserver>((*this)));
}

TextObserver::~TextObserver() {}

void TextObserver::notify() {
    /*
        White piece = uppercase
        Black piece = lowercase
        White square = blank
        Black square = underscore
    */

    // Print 8x8 board
    for (int i = 8; i >= 1; i--) {
        // Print row number on the right
        out << i << " ";

        // Print row tiles
        if (i % 2 == 0) {
            // Print white tile first, then alternate
            for (int j = 0; j <= 7; j++) {
                char thePiece = subject->getState(i-1,j);
                if (thePiece != 0) {
                    out << thePiece;
                } else {
                    if (j % 2 == 0) out << " ";
                    else out << "_";
                }
            }
        } else {
            for (int j = 0; j <= 7; j++) {
                char thePiece = subject->getState(i-1,j);
                if (thePiece != 0) {
                    out << thePiece;
                } else {
                    if (j % 2 == 0) out << "_";
                    else out << " ";
                }
            }
        }

        // End current row, start new row
        if (i != 1) out << endl;
    }

    // Print empty line after board
    out << "\n" << endl;
    
    // Print 2 spaces
    out << "  ";
    for (int i = 97; i < 105; i++) {
        char col = i;
        out << col;
    }
    out << "" << endl;

    // Print gameState
    char gState = subject->getGameState();
    if (gState == 'w') {
        cout << "White is in check." << endl;
    } else if (gState == 'b') {
        cout << "Black is in check." << endl;
    } else if (gState == 'W') {
        cout << "Checkmate! Black wins!" << endl;
    } else if (gState == 'B') {
        cout << "Checkmate! White wins!" << endl;
    } else if (gState == 's') {
        cout << "Stalemate!" << endl;
    }
}

