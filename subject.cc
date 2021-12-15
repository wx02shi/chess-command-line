#include "subject.h"
#include "observer.h"

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

void Subject::attach(shared_ptr<Observer> o) {
    observers.push_back(o);
}

void Subject::empty() {
    observers.erase(observers.begin(), observers.end());
}

void Subject::detach(shared_ptr<Observer> o) {
    for (auto it = observers.begin(); it != observers.end();) {
        if (*it == o) it = observers.erase(it);
        else ++it;
    }
}

void Subject::notifyObservers(){
    for (auto ob : observers) ob->notify();
}
