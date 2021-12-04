#include "subject.h"
#include "observer.h"

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

/* void Subject::attachTextObserver(shared_ptr<Observer> o) {
    textObserver = o;
} */

void Subject::attach(shared_ptr<Observer> o) {
    observers.push_back(o);
    // cout << "ATTACH OBS VEC SIZE: " << observers.size() << endl;
    // cout << "ATTACH OBS o SIZE: " << observers[0].use_count() << endl;
}
/* void Subject::attach(Observer o) {
    observers.emplace_back(o);
} */

/* void Subject::detach(shared_ptr<Observer> o) {
    // WE MAY OR MAY NOT NEED DETACH <- MUST COME BACK TO FIGURE THIS OUT!!
    // 8:28pm 12/03/21 atm it does nothing
    for (auto it = observers.begin(); it != observers.end();) {
        if (*it == o) *it = nullptr;
        else ++it;
    } 
} */

void Subject::empty() {
    // cout << "observers size " << observers.size() << endl;
    observers.erase(observers.begin(), observers.end());
    // cout << "observers size after " << observers.size() << endl;
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

/* Subject::~Subject() {
    empty();
} */
