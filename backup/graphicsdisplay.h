#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include "subject.h"
#include "observer.h"
#include "cell.h"
#include "window.h"
class Xwindow;

class GraphicsDisplay : public Observer {
    Xwindow xw;
    const int size;
    const int GAP = 5;
    const int XWSIZE = 500;
public:
    GraphicsDisplay(int n);
    void notify(Subject &whoNotified) override;
    int getLength() const;
    int mapToX(size_t col) const;
    int mapToY(size_t row) const;
    int mapColour(Colour colour) const;
};

#endif
