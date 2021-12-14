#include "graphicsObserver.h"
#include "window.h"

#include <utility>
#include <memory>
#include <string>

using namespace std;

GraphicsObserver::GraphicsObserver(shared_ptr<Game> g) : subject{g} {
    window = make_shared<Xwindow>();
    subject->attach(make_shared<GraphicsObserver>((*this)));

    // Disply the board and axes once to save computation
    for (int i = 8; i >= 1; i--) {
        string msg = to_string(9 - i);
        window->drawString(5, (i + 1) * TILESIZE - 4, msg);
    }
    for (int j = 0; j <= 7; j++) {
        char temp = j + 97;
        string msg{temp};
        window->drawString((j + 1) * TILESIZE + 5, 10 * TILESIZE, msg);
    }
}

GraphicsObserver::~GraphicsObserver() {}

void GraphicsObserver::notify() {
    // display the grid:
    for (int i = 8; i >= 1; i--) {
        if (i % 2 == 0) {
            for (int j = 0; j <= 7; j++) {
                if (j % 2 == 0) {
                    window->fillRectangle((1+j) * TILESIZE, (i) * TILESIZE, TILESIZE, TILESIZE, Xwindow::White);
                } else {
                    window->fillRectangle((1+j) * TILESIZE, (i) * TILESIZE, TILESIZE, TILESIZE, Xwindow::Green);
                }
            }
        } else {
            for (int j = 0; j <= 7; j++) {
                if (j % 2 == 0) {
                    window->fillRectangle((1+j) * TILESIZE, (i) * TILESIZE, TILESIZE, TILESIZE, Xwindow::Green);
                } else {
                    window->fillRectangle((1+j) * TILESIZE, (i) * TILESIZE, TILESIZE, TILESIZE, Xwindow::White);
                }
            }
        }
    }
    
    // print pieces
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            char thePiece = subject->getState(i,j);
            string msg = "";
            if (thePiece != 0) { 
                msg.push_back(thePiece); 
                window->drawString((j + 1) * TILESIZE + 5, ((7 - i) +2) * TILESIZE - 4, msg);
            }
        }
    }
}

