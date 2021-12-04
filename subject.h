#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include <vector>
#include <memory>

class Observer;

// TODO: IMPLEMENT RAII FOR THE OBSERVER DESIGN PATTERN (FOR ALL THE FILES)
class Subject {
    // std::vector<Observer*> observers;
    std::vector<std::shared_ptr<Observer>> observers;

    public:
        void attach(std::shared_ptr<Observer> o);
        void detach(std::shared_ptr<Observer> o);
        void empty();
        /* void attach(Observer* o);
        void detach(Observer* o); */
        
        virtual char getState(int row, int col) const = 0;
        virtual ~Subject() = default;
    
    protected:
    void notifyObservers();
};

#endif
