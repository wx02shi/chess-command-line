#ifndef __TEXTOBSERVER_H__
#define __TEXTOBSERVER_H__

#include "observer.h"
#include "game.h"

#include <iostream>
#include <memory>

class TextObserver: public Observer {
    std::shared_ptr<Game> subject;

    std::ostream &out = std::cout;

    public:
        TextObserver(std::shared_ptr<Game> g);
        void notify() override;
        ~TextObserver();

};

#endif

