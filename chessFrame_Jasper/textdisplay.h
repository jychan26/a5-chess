#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <vector>
#include "observer.h"
#include "subject.h"
#include <iostream>

class TextDisplay : public Observer {
    std::vector<std::vector<char>> theDisplay;
    const int size = 8;
public:
    TextDisplay();
    void notify(Subject &whoNotified) override;
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif

