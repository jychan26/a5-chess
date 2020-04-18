#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Subject;
class Cell;

class Observer {
public:
    virtual void notify(Subject &whoFrom) = 0; // pass the Subject that called the notify method
    virtual ~Observer() = default;
};
#endif

