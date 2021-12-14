#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include <vector>
#include <memory>

class Observer;

class Subject {
    std::vector<std::shared_ptr<Observer>> observers;

    public:
        void attach(std::shared_ptr<Observer> o);
        void detach(std::shared_ptr<Observer> o);
        void empty();
        
        virtual char getState(int row, int col) const = 0;
        virtual ~Subject() = default;
    
    protected:
    void notifyObservers();
};

#endif

