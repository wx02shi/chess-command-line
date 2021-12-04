#include <iostream>
#include <memory>

#include "textObserver.h"

using namespace std;

TextObserver::TextObserver(shared_ptr<Game> g) : subject{g} {
    // THIS MIGHT NOT WORK (and detach)
    // cout << "TEXTOBS g COUNT " << g.use_count() << endl;
    // g is definitely gone
    subject->attach(make_shared<TextObserver>((*this)));
}

TextObserver::~TextObserver() {
    // TODO: maked_shared might not actually detach <- address later
    //cout << "This is from the DETACH in TEXTOBSERVER" << endl;
    //subject->detach(make_shared<TextObserver>((*this)));
    // subject = nullptr; // note: somehow decreased the subject count by 3 ???
    // cout << "TEXTOBS OBSERVERS VEC SIZE : " << observers.size() << endl;
    //cout << "TEXTOBS DESTRUCTOR SUBJECT COUNT " << subject.use_count() << endl;
    
}

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
        // TODO: need to put subject->getState(...) 
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

    //cout << "NOTIFY, SUBJECT SHARED_PTR COUNT " << subject.use_count() << endl;
}
