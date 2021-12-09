#include "graphicsObserver.h"
#include "window.h"

#include <utility>
#include <memory>
#include <string>

using namespace std;

GraphicsObserver::GraphicsObserver(shared_ptr<Game> g) : subject{g} {
  
  window = make_shared<Xwindow>();
  subject->attach(make_shared<GraphicsObserver>((*this)));
}

GraphicsObserver::~GraphicsObserver() {}

void GraphicsObserver::notify() {
    // TODO: axes and board only need to be drawn once, consider moving
    // to constructor
    for (int i = 8; i >= 1; i--) {
        string msg = to_string(9-i);
        window->drawString(5, (i + 1) * TILESIZE - 4, msg);
        
        // display the grid:
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
    for (int j = 0; j <= 7; j++) {
        char temp = j + 97;
        string msg{temp};
        window->drawString((j + 1) * TILESIZE + 5, 10 * TILESIZE, msg);
    }

    // print pieces
}
