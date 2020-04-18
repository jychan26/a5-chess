#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "info.h"
#include "observer.h"

class Subject {
    std::vector<Observer *> observers;
public:
    void attach(Observer *o) {
        observers.emplace_back(o);
    }
    void notifyObservers() {
        for (auto &ob : observers) ob->notify(*this);
    }
    virtual Info getInfo() const = 0;
};
#endif

