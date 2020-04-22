#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include "subject.h"
#include "observer.h"
#include "cell.h"
#include "window.h"
#include "errormessage.h"
#include "textdisplay.h"
#include <string>

class GraphicsDisplay : public Observer {
    Xwindow *xw;
    TextDisplay *td;
    const int BOARDSIZE = 8;
    const int GAP = 50;
    const int PIECE_PLACEMENT = 75;
public:
    GraphicsDisplay(TextDisplay * td);
    ~GraphicsDisplay();

    void notify(Subject &whoNotified) override;
    void displayErrorMessage(ErrorMessage &e);
    void clearErrorMessage() const;
    void displayMessage(std::string s, int line_num);
    friend std::ostream &operator<<(std::ostream &out, const GraphicsDisplay &gd);
};

#endif
