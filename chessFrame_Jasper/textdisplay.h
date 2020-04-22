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
    int getSize();
    std::vector<std::vector<char>> getTheDisplay();
    friend class GraphicsDisplay;
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif

