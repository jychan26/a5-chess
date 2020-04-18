#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Subject;
class Cell;

class Observer {
public:
    virtual void notify(Subject &whoFrom) = 0;
    virtual ~Observer() = default;
};
#endif

