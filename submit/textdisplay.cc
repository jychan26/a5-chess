#include "textdisplay.h"
#include "colour.h"
#include "position.h"
#include "info.h"
#include "subject.h"
#include <string>
using namespace std;

TextDisplay::TextDisplay() {
    for (int r = 0; r < size; ++r) {
        vector<char> temp;
        for (int c = 0; c < size; ++c) {
            if ((r + c) % 2 == 0) {
                temp.emplace_back('_');
            } else {
                temp.emplace_back(' ');
            }
        }
        theDisplay.emplace_back(temp);
    }
}

void TextDisplay::notify(Subject &whoNotified) {
    Info i = whoNotified.getInfo();
    Position pos = i.pos;
    Colour cellColour = i.cellColour;
    Piece *piece = i.piece;
    if (!piece) {
        if (cellColour == Colour::White) {
            theDisplay[pos.row - 1][pos.col - 'a'] = ' ';
        } else if (cellColour == Colour::Black) {
            theDisplay[pos.row - 1][pos.col - 'a'] = '_';
        }
    } else {
        char name = piece->getPiece();
        theDisplay[pos.row - 1][pos.col - 'a'] = name;
    }
}

int TextDisplay::getSize() { return size; }

std::vector<std::vector<char>> TextDisplay::getTheDisplay() { return theDisplay; }

ostream &operator<<(ostream &out, const TextDisplay &td) {
    for (int i = td.size - 1; i >= 0; --i) {
        out << i + 1 << ' ';
        for (int j = 0; j < td.size; ++j) {
            out << td.theDisplay[i][j];
        }
        out << endl;
    }
    out << endl;
    out << "  abcdefgh" << endl;
    return out;
}

        
