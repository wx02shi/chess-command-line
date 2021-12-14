#ifndef __GRAPHICSOBSERVER_H__
#define __GRAPHICSOBSERVER_H__

#include "observer.h"
#include "game.h"
#include "window.h"

#include <memory>

class GraphicsObserver : public Observer {
  std::shared_ptr<Game> subject;
  std::shared_ptr<Xwindow> window;

  const int TILESIZE = 16;

  public:
    GraphicsObserver(std::shared_ptr<Game> g);
    void notify() override;
    ~GraphicsObserver();
};

#endif

